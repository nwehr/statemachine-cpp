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

    typedef std::function<const TransitionResult (map<string, any>&)> HandlerT;

    ////////////////////////////////////////////
    // Transition
    ////////////////////////////////////////////
    class Transition : public Unique {
    public:
        HandlerT handler;
        shared_ptr<State> destination;
        
        Transition(const unsigned int id, const string& name, const HandlerT& handler, const shared_ptr<State>& destination = nullptr);
    };
}

StateMachine::TransitionResult::TransitionResult(const bool ok, const string& msg)
: ok(ok) 
, msg(msg)
{}

StateMachine::Transition::Transition(const unsigned int id, const string& name, const HandlerT& handler, const shared_ptr<State>& destination)
: StateMachine::Unique(id, name)
, handler(handler)
, destination(destination) 
{}
