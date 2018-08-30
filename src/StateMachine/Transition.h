#pragma once

#include <functional>
#include <memory>
#include <map>
#include <experimental/any>

#include "./Transition.h"

using namespace std;
using namespace std::experimental;

namespace StateMachine {
    class State;

    struct TransitionResult {
        const bool ok;
        const string msg;

        TransitionResult(const bool ok, const string& msg = "")
        : ok(ok) 
        , msg(msg)
        {}
    };

    typedef map<string, any> Args;
    typedef std::function<const TransitionResult (Args&)> Handler;
    typedef shared_ptr<State> StatePtr;

    ////////////////////////////////////////////
    // Transition
    ////////////////////////////////////////////
    class Transition {
    public:
        Handler handler;
        StatePtr destination;
        
        Transition(const Handler& handler, const StatePtr& destination = nullptr)
        : handler(handler)
        , destination(destination) 
        {}

        virtual ~Transition() {}
    };
}
