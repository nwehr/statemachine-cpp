#include <iostream>
#include <future>

#include "./StateMachine/StateMachine.h"

using namespace StateMachine;

const vector<StatePtr> states() {
    auto s1 = StatePtr(new State(1, "Start"));
    auto s2 = StatePtr(new State(2, "End"));

    return vector<StatePtr>{s1, s2};
}

const vector<TransitionPtr> transitions() {
    auto t1 = TransitionPtr(new Transition(1, "Complete", [](Args& args) -> const TransitionResult {
        return TransitionResult(true);
    }));

    return vector<TransitionPtr>{t1};
}

const ::StateMachine::StateMachine load() {
    // simulate loading states and transitions concurrently from a database
    auto futureStates = async(launch::async, states);
    auto futureTransitions = async(launch::async, transitions);

    // block until our concurrent fetching tasks are complete
    auto states = futureStates.get();
    auto transitions = futureTransitions.get();

    transitions[0]->destination = states[1];

    states[0]->transitions.push_back(transitions[0]);

   return ::StateMachine::StateMachine(1, "Main", Args(), states.front());
}

int main(int argc, char *argv[]) {
    auto stateMachine = load();

    cout << stateMachine.state->name << endl;

    stateMachine.next(stateMachine.state->transitions.front());

    cout << stateMachine.state->name << endl;
}
