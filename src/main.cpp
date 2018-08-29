#include <iostream>
#include <memory>
#include <functional>
#include <experimental/any>
#include <future>

#include <vector>
#include <map>

using namespace std;
using namespace std::experimental;

class State;
class Transition;

////////////////////////////////////////////
// Unique
////////////////////////////////////////////
class Unique {
public:
    const unsigned int id;
    const string name;

    Unique(const unsigned int id, const string& name) 
    : id(id)
    , name(name)
    {}
};

////////////////////////////////////////////
// State
////////////////////////////////////////////
class State : public Unique {
public:
    vector<shared_ptr<Transition>> transitions;

    State(const unsigned int id, const string& name, const vector<shared_ptr<Transition>>& transitions = {})
    : Unique(id, name)
    , transitions(transitions)
    {}
};

////////////////////////////////////////////
// TransitionResult
////////////////////////////////////////////
struct TransitionResult {
    const bool ok;
    const string msg;

    TransitionResult(const bool ok, const string& msg = "")
    : ok(ok) 
    , msg(msg)
    {}
};

////////////////////////////////////////////
// HandlerT
////////////////////////////////////////////
typedef std::function<const TransitionResult (map<string, any>&)> HandlerT;

////////////////////////////////////////////
// Transition
////////////////////////////////////////////
class Transition : public Unique {
public:
    HandlerT handler;
    shared_ptr<State> destination;
    
    Transition(const unsigned int id, const string& name, const HandlerT& handler, const shared_ptr<State>& destination = nullptr)
    : Unique(id, name)
    , handler(handler)
    , destination(destination) 
    {}
};

////////////////////////////////////////////
// StateMachine
////////////////////////////////////////////
class StateMachine : public Unique {
public:
    map<string, any> args;
    shared_ptr<State> state;

    StateMachine(const unsigned int id, const string& name, const map<string, any>& args, const shared_ptr<State>& state = nullptr)
    : Unique(id, name)
    , args(args)
    , state(state)
    {}

    void next(shared_ptr<Transition> transition) {
        auto result = transition->handler(args);

        if(!result.ok){
            cout << "Ooops!" << endl;
        } else {
            state = transition->destination;
        }
    }
};

const vector<shared_ptr<State>> states() {
    auto s1 = shared_ptr<State>(new State(1, "Start"));
    auto s2 = shared_ptr<State>(new State(2, "End"));

    return vector<shared_ptr<State>>{s1, s2};
}

const vector<shared_ptr<Transition>> transitions() {
    auto t1 = shared_ptr<Transition>(new Transition(1, "Complete", [](map<string, any>& args) -> const TransitionResult {
        return TransitionResult(true);
    }));

    return vector<shared_ptr<Transition>>{t1};
}

const StateMachine load() {
    auto futureStates = async(launch::async, states);
    auto futureTransitions = async(launch::async, transitions);

    auto states = futureStates.get();
    auto transitions = futureTransitions.get();

    transitions.front()->destination = states[1];

    states.front()->transitions.push_back(transitions.front());

   return StateMachine(1, "Main", map<string, any>(), states.front());
}

int main(int argc, char *argv[]) {
    auto sm = load();

    cout << sm.state->name << endl;

    sm.next(sm.state->transitions.front());

    cout << sm.state->name << endl;
}
