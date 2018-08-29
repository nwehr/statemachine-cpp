#pragma once

#include <memory>
#include <vector>

#include "./Unique.h"
#include "./Transition.h"

using namespace std;

namespace StateMachine {
    class Transition;

    ////////////////////////////////////////////
    // State
    ////////////////////////////////////////////
    class State : public Unique {
    public:
        vector<shared_ptr<Transition>> transitions;

        State(const unsigned int id, const string& name, const vector<shared_ptr<Transition>>& transitions = {});
    };
}

StateMachine::State::State(const unsigned int id, const string& name, const vector<shared_ptr<Transition>>& transitions)
: StateMachine::Unique(id, name)
, transitions(transitions)
{}
