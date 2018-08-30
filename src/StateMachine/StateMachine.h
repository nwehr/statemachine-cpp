#pragma once

#include "./State.h"
#include "./Transition.h"

using namespace std;
using namespace std::experimental;

namespace StateMachine {
    ////////////////////////////////////////////
    // StateMachine
    ////////////////////////////////////////////
    class StateMachine {
    public:
        Args args;
        shared_ptr<State> state;

        StateMachine(const Args& args, const shared_ptr<State>& state = nullptr)
        : args(args)
        , state(state)
        {}

        void next(shared_ptr<Transition> transition) {
            auto result = transition->handler(args);

            if(!result.ok){
                cout << "Ooops!" << endl;
            } else {
                state = transition->destination;
            }
        }
    };
}

#include "./UniqueState.h"
#include "./UniqueStateMachine.h"
#include "./UniqueTransition.h"
