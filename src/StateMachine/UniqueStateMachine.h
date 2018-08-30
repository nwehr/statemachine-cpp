#pragma once

#include "./Unique.h"
#include "./StateMachine.h"

namespace StateMachine {
    ////////////////////////////////////////////
    // StateMachine
    ////////////////////////////////////////////
    class UniqueStateMachine : public Unique, public StateMachine {
    public:
        UniqueStateMachine(const unsigned int id, const string& name, const Args& args, const shared_ptr<State>& state = nullptr)
        : Unique(id, name)
        , StateMachine(args, state)
        {}

        virtual ~UniqueStateMachine() {}
    };
}