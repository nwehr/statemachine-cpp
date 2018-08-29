#include <iostream>
#include <future>

#include "./StateMachine/StateMachine.h"

const vector<StateMachine::StatePtr> states() {
    auto s1 = StateMachine::StatePtr(new StateMachine::State(1, "Start"));
    auto s2 = StateMachine::StatePtr(new StateMachine::State(2, "End"));

    return vector<StateMachine::StatePtr>{s1, s2};
}

const vector<StateMachine::TransitionPtr> transitions() {
    auto t1 = StateMachine::TransitionPtr(new StateMachine::Transition(1, "Complete", [](StateMachine::Args& args) -> const StateMachine::TransitionResult {
        return StateMachine::TransitionResult(true);
    }));

    return vector<StateMachine::TransitionPtr>{t1};
}

const StateMachine::StateMachine load() {
    auto futureStates = async(launch::async, states);
    auto futureTransitions = async(launch::async, transitions);

    auto states = futureStates.get();
    auto transitions = futureTransitions.get();

    transitions.front()->destination = states[1];

    states.front()->transitions.push_back(transitions.front());

   return StateMachine::StateMachine(1, "Main", StateMachine::Args(), states.front());
}

int main(int argc, char *argv[]) {
    auto sm = load();

    cout << sm.state->name << endl;

    sm.next(sm.state->transitions.front());

    cout << sm.state->name << endl;
}
