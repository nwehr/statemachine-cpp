#pragma once

#include <memory>
#include <vector>

#include "./Transition.h"

using namespace std;

namespace StateMachine {
    class Transition;

    typedef shared_ptr<Transition> TransitionPtr;

    ////////////////////////////////////////////
    // State
    ////////////////////////////////////////////
    class State {
    public:
        vector<TransitionPtr> transitions;

        State(const vector<TransitionPtr>& transitions = {})
        : transitions(transitions)
        {}

        virtual ~State() {}
    };
}
