#pragma once

#include <memory>
#include <vector>

#include "./Transition.h"

using namespace std;

namespace StateMachine {
    class Transition;

    ////////////////////////////////////////////
    // State
    ////////////////////////////////////////////
    class State {
    public:
        vector<shared_ptr<Transition>> transitions;

        State(const vector<shared_ptr<Transition>>& transitions = {})
        : transitions(transitions)
        {}

        virtual ~State() {}
    };
}
