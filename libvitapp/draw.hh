#pragma once

#include "singleton.hh"

namespace vitapp {

class draw: public singleton<draw> {
protected:
    draw();

public:
    virtual ~draw() override;



private:
};

}
