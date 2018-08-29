#pragma once

#include "./State.h"
#include "./Transition.h"

using namespace std;
using namespace std::experimental;

namespace StateMachine {
    ////////////////////////////////////////////
    // StateMachine
    ////////////////////////////////////////////
    class StateMachine : public Unique {
    public:
        map<string, any> args;
        shared_ptr<State> state;

        StateMachine(const unsigned int id, const string& name, const map<string, any>& args, const shared_ptr<State>& state = nullptr);

        void next(shared_ptr<Transition> transition);
    };
}

StateMachine::StateMachine::StateMachine(const unsigned int id, const string& name, const map<string, any>& args, const shared_ptr<State>& state)
: StateMachine::Unique(id, name)
, args(args)
, state(state)
{}

void StateMachine::StateMachine::next(shared_ptr<Transition> transition) {
    auto result = transition->handler(args);

    if(!result.ok){
        cout << "Ooops!" << endl;
    } else {
        state = transition->destination;
    }
}
