#pragma once

#include "./State.h"
#include "./Transition.h"

using namespace std;
using namespace std::experimental;

namespace StateMachine {
    ////////////////////////////////////////////
    // StateMachine
    ////////////////////////////////////////////
    template<class StateT, class TransitionT>
    class StateMachine {
    public:
        Args args;
        shared_ptr<StateT> state;

        StateMachine(const Args& args, const shared_ptr<StateT>& state = nullptr)
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
