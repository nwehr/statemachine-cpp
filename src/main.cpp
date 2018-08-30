#include <iostream>
#include <future>

#include "./StateMachine/StateMachine.h"

using namespace StateMachine;

const vector<shared_ptr<UniqueState>> states() {
    shared_ptr<UniqueState> s1(new UniqueState(1, "Start"));
    shared_ptr<UniqueState> s2(new UniqueState(2, "End"));

    return vector<shared_ptr<UniqueState>>{s1, s2};
}

const vector<shared_ptr<UniqueTransition>> transitions() {
    auto handler = [](Args& args) -> const TransitionResult {
        return TransitionResult(true);
    };

    shared_ptr<UniqueTransition> t1(new UniqueTransition(1, "Complete", handler));

    return vector<shared_ptr<UniqueTransition>>{t1};
}

const UniqueStateMachine load() {
    // simulate loading states and transitions concurrently from a database
    auto futureStates = async(launch::async, states);
    auto futureTransitions = async(launch::async, transitions);

    // block until our concurrent fetching tasks are complete
    auto states = futureStates.get();
    auto transitions = futureTransitions.get();

    transitions[0]->destination = states[1];

    states[0]->transitions.push_back(transitions[0]);

   return UniqueStateMachine(1, "Main", Args(), states.front());
}

int main(int argc, char* argv[]) {
    auto stateMachine = load();

    cout << static_cast<UniqueState*>(stateMachine.state.get())->name << endl;

    stateMachine.next(stateMachine.state->transitions.front()); 

    cout << static_cast<UniqueState*>(stateMachine.state.get())->name << endl;
}
