#pragma once

namespace vitapp {

class promoter {
private:
    promoter();

public:
    ~promoter();

    static inline promoter &get() {
        static promoter single;
        return single;
    }

    void start(const char *path);
    void stop();
    bool running();
    inline int result() { return result_; }

private:
    int result_ = 0;
};

}
