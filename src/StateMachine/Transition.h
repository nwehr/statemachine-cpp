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

    ////////////////////////////////////////////
    // Transition
    ////////////////////////////////////////////
    class Transition {
    public:
        Handler handler;
        shared_ptr<State> destination;
        
        Transition(const Handler& handler, const shared_ptr<State>& destination = nullptr)
        : handler(handler)
        , destination(destination) 
        {}

        virtual ~Transition() {}
    };
}
