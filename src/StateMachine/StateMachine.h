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
        StatePtr state;

        StateMachine(const Args& args, const StatePtr& state = nullptr)
        : args(args)
        , state(state)
        {}

        virtual ~StateMachine() {}

        void next(const TransitionPtr& transition) {
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
