#include <iostream>
#include <future>

#include "./StateMachine/StateMachine.h"

typedef shared_ptr<StateMachine::State> StatePtr;
typedef shared_ptr<StateMachine::Transition> TransitionPtr;

const vector<StatePtr> states() {
    auto s1 = StatePtr(new StateMachine::State(1, "Start"));
    auto s2 = StatePtr(new StateMachine::State(2, "End"));

    return vector<StatePtr>{s1, s2};
}

const vector<TransitionPtr> transitions() {
    auto t1 = TransitionPtr(new StateMachine::Transition(1, "Complete", [](map<string, any>& args) -> const StateMachine::TransitionResult {
        return StateMachine::TransitionResult(true);
    }));

    return vector<TransitionPtr>{t1};
}

const StateMachine::StateMachine load() {
    auto futureStates = async(launch::async, states);
    auto futureTransitions = async(launch::async, transitions);

    auto states = futureStates.get();
    auto transitions = futureTransitions.get();

    transitions.front()->destination = states[1];

    states.front()->transitions.push_back(transitions.front());

   return StateMachine::StateMachine(1, "Main", map<string, any>(), states.front());
}

int main(int argc, char *argv[]) {
    auto sm = load();

    cout << sm.state->name << endl;

    sm.next(sm.state->transitions.front());

    cout << sm.state->name << endl;
}
