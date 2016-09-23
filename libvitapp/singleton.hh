#pragma once

#include "os.hh"

namespace vitapp {

class singleton_base {
public:
    virtual ~singleton_base() = 0;
};

template<typename T>
class singleton: public singleton_base {
public:
    static inline T &get() {
        static T single;
        return single;
    }
};

}
