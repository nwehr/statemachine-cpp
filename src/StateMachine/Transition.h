#pragma once

#include <functional>
#include <memory>
#include <map>
#include <experimental/any>

#include "./Unique.h"
#include "./Transition.h"

using namespace std;
using namespace std::experimental;

namespace StateMachine {
    class State;

    struct TransitionResult {
        const bool ok;
        const string msg;

        TransitionResult(const bool ok, const string& msg = "");
    };
    
    typedef shared_ptr<State> StatePtr;
    typedef map<string, any> Args;
    typedef std::function<const TransitionResult (Args&)> Handler;

    ////////////////////////////////////////////
    // Transition
    ////////////////////////////////////////////
    class Transition : public Unique {
    public:
        Handler handler;
        StatePtr destination;
        
        Transition(const unsigned int id, const string& name, const Handler& handler, const StatePtr& destination = nullptr);
    };
}

StateMachine::TransitionResult::TransitionResult(const bool ok, const string& msg)
: ok(ok) 
, msg(msg)
{}

StateMachine::Transition::Transition(const unsigned int id, const string& name, const Handler& handler, const StatePtr& destination)
: StateMachine::Unique(id, name)
, handler(handler)
, destination(destination) 
{}
