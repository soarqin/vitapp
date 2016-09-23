#pragma once

#include "os.hh"

namespace vitapp {

class app {
public:
    enum class module {
        net,
        pgf,
        promoter,
        vita2d,
    };

protected:
    app(const std::initializer_list<module> &inits = {module::vita2d, module::pgf});

public:
    virtual ~app();

    template<typename T, typename... ARG>
    static T *create(const ARG &...args) {
        app_ = new T(args...);
        return app_;
    };

    static inline app *get() { return app_; }
    void load(module, bool check = true);
    void init_font(const char *name = nullptr);
    inline bool is_font_inited() { return font_ != nullptr; }
    inline int language() { return language_; }
    inline int enter_button() { return enter_button_; }

    void run();

    virtual bool frame() = 0;

private:
    void free_font();

private:
    static app *app_;
    std::set<module> inited_modules_;
    int language_;
    int enter_button_;
    void *font_;
};

}
