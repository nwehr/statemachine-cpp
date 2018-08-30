#pragma once

#include <string>

using namespace std;

namespace StateMachine {
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
}
