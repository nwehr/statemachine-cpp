#pragma once

#include <memory>
#include <vector>

#include "./Unique.h"
#include "./Transition.h"

using namespace std;

namespace StateMachine {
    class Transition;

    typedef shared_ptr<Transition> TransitionPtr;

    ////////////////////////////////////////////
    // State
    ////////////////////////////////////////////
    class State : public Unique {
    public:
        vector<TransitionPtr> transitions;

        State(const unsigned int id, const string& name, const vector<TransitionPtr>& transitions = {});
    };
}

StateMachine::State::State(const unsigned int id, const string& name, const vector<TransitionPtr>& transitions)
: StateMachine::Unique(id, name)
, transitions(transitions)
{}
