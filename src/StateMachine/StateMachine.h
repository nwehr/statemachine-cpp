#pragma once

#include <string>
#include <memory>
#include <functional>
#include <experimental/any>

#include <vector>
#include <map>

using namespace std;
using namespace std::experimental;

namespace StateMachine {
    class State;
    class Transition;

    struct TransitionResult {
        const bool ok;
        const string msg;

        TransitionResult(const bool ok, const string& msg = "");
    };

    typedef std::function<const TransitionResult (map<string, any>&)> HandlerT;

    ////////////////////////////////////////////
    // Unique
    ////////////////////////////////////////////
    class Unique {
    public:
        const unsigned int id;
        const string name;

        Unique(const unsigned int id, const string& name);
    };

    ////////////////////////////////////////////
    // State
    ////////////////////////////////////////////
    class State : public Unique {
    public:
        vector<shared_ptr<Transition>> transitions;

        State(const unsigned int id, const string& name, const vector<shared_ptr<Transition>>& transitions = {});
    };
    
    ////////////////////////////////////////////
    // Transition
    ////////////////////////////////////////////
    class Transition : public Unique {
    public:
        HandlerT handler;
        shared_ptr<State> destination;
        
        Transition(const unsigned int id, const string& name, const HandlerT& handler, const shared_ptr<State>& destination = nullptr);
    };

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

StateMachine::TransitionResult::TransitionResult(const bool ok, const string& msg)
: ok(ok) 
, msg(msg)
{}

StateMachine::Unique::Unique(const unsigned int id, const string& name)
: id(id)
, name(name)
{}

StateMachine::State::State(const unsigned int id, const string& name, const vector<shared_ptr<Transition>>& transitions)
: StateMachine::Unique(id, name)
, transitions(transitions)
{}

StateMachine::Transition::Transition(const unsigned int id, const string& name, const HandlerT& handler, const shared_ptr<State>& destination)
: StateMachine::Unique(id, name)
, handler(handler)
, destination(destination) 
{}

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
