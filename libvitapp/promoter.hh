#pragma once

#include "singleton.hh"

namespace vitapp {

class promoter: public singleton<promoter> {
protected:
    promoter();

public:
    virtual ~promoter() override;

    void start(const char *path);
    void stop();
    bool running();
    inline int result() { return result_; }

private:
    int result_ = 0;
};

}
