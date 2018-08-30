#pragma once

#include "./Unique.h"
#include "./StateMachine.h"

namespace StateMachine {
    ////////////////////////////////////////////
    // StateMachine
    ////////////////////////////////////////////
    template<class StateT, class TransitionT>
    class UniqueStateMachine : public Unique, public StateMachine<StateT, TransitionT> {
    public:
        UniqueStateMachine(const unsigned int id, const string& name, const Args& args, const shared_ptr<StateT>& state = nullptr)
        : Unique(id, name)
        , StateMachine<StateT, TransitionT>(args, state)
        {}
    };
}