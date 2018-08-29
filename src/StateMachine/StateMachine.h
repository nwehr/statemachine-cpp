#pragma once

#include "./State.h"
#include "./Transition.h"

using namespace std;
using namespace std::experimental;

namespace StateMachine {
    ////////////////////////////////////////////
    // StateMachine
    ////////////////////////////////////////////
    class StateMachine : public Unique {
    public:
        Args args;
        StatePtr state;

        StateMachine(const unsigned int id, const string& name, const Args& args, const StatePtr& state = nullptr);

        void next(TransitionPtr transition);
    };
}

StateMachine::StateMachine::StateMachine(const unsigned int id, const string& name, const Args& args, const StatePtr& state)
: StateMachine::Unique(id, name)
, args(args)
, state(state)
{}

void StateMachine::StateMachine::next(TransitionPtr transition) {
    auto result = transition->handler(args);

    if(!result.ok){
        cout << "Ooops!" << endl;
    } else {
        state = transition->destination;
    }
}
