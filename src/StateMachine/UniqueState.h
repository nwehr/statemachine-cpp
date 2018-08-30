#pragma once

#include "./Unique.h"
#include "./State.h"

namespace StateMachine {
    ////////////////////////////////////////////
    // UniqueState
    ////////////////////////////////////////////
    class UniqueState : public Unique, public State {
    public:
        UniqueState(unsigned int id, const string& name, const vector<shared_ptr<Transition>>& transitions = {})
        : Unique(id, name)
        , State(transitions)
        {}

        virtual ~UniqueState() {}
    };
}