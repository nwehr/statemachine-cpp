#include <iostream>
#include <future>

#include "./StateMachine/StateMachine.h"

const vector<shared_ptr<StateMachine::State>> states() {
    auto s1 = shared_ptr<StateMachine::State>(new StateMachine::State(1, "Start"));
    auto s2 = shared_ptr<StateMachine::State>(new StateMachine::State(2, "End"));

    return vector<shared_ptr<StateMachine::State>>{s1, s2};
}

const vector<shared_ptr<StateMachine::Transition>> transitions() {
    auto t1 = shared_ptr<StateMachine::Transition>(new StateMachine::Transition(1, "Complete", [](map<string, any>& args) -> const StateMachine::TransitionResult {
        return StateMachine::TransitionResult(true);
    }));

    return vector<shared_ptr<StateMachine::Transition>>{t1};
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
