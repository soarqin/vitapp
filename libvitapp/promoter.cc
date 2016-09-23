#include "promoter.hh"

#include "app.hh"

#include "../libpromoter/promoterutil.h"

namespace vitapp {

promoter::promoter() {
    app::get()->load(app::module::promoter);
}

promoter::~promoter() {
}

void promoter::start(const char *path) {
    scePromoterUtilityInit();
    scePromoterUtilityPromotePkg(const_cast<char*>(path), 0);
}

void promoter::stop() {
    scePromoterUtilityExit();
}

bool promoter::running() {
    int state = 0;
    int res = scePromoterUtilityGetState(&state);
    if (res < 0) {
        result_ = -1;
        scePromoterUtilityExit();
        return false;
    }
    if (!state) {
        res = scePromoterUtilityGetResult(&result_);
        if (res < 0)
            result_ = -1;
        scePromoterUtilityExit();
        return false;
    }
    return true;
}

}
