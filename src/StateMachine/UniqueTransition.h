#pragma once

#include "./Unique.h"
#include "./Transition.h"

namespace StateMachine {
    ////////////////////////////////////////////
    // Transition
    ////////////////////////////////////////////
    class UniqueTransition : public Unique, public Transition {
    public:
        UniqueTransition(unsigned int id, const string& name, const Handler& handler, const StatePtr& destination = nullptr)
        : Unique(id, name)
        , Transition(handler, destination)
        {}

        virtual ~UniqueTransition() {}
    };
}