#include "ctrl.hh"

#include <psp2/ctrl.h>

namespace vitapp {

ctrl::ctrl() {
}

ctrl::~ctrl() {
}

ctrl::mode ctrl::get_mode() {
    int m;
    sceCtrlGetSamplingMode(&m);
    return static_cast<ctrl::mode>(m);
}

void ctrl::set_mode(ctrl::mode m) {
    sceCtrlSetSamplingMode(static_cast<int>(m));
}

void ctrl::capture_buttons() {
    SceCtrlData data;
    if (sceCtrlPeekBufferPositive(0, &data, 1) <= 0) return;
    buttons_ = data.buttons;
    if (data.ly <= analog_range_[0]) {
        data.buttons |= lanalog_up;
    } else if (data.ly >= analog_range_[1]) {
        data.buttons |= lanalog_down;
    }

    if (data.lx <= analog_range_[0]) {
        data.buttons |= lanalog_left;
    } else if (data.lx >= analog_range_[1]) {
        data.buttons |= lanalog_right;
    }

    if (data.ry <= analog_range_[0]) {
        data.buttons |= ranalog_up;
    } else if (data.ry >= analog_range_[1]) {
        data.buttons |= ranalog_down;
    }

    if (data.rx <= analog_range_[0]) {
        data.buttons |= ranalog_left;
    } else if (data.rx >= analog_range_[1]) {
        data.buttons |= ranalog_down;
    }
}

void ctrl::set_analog_threshold(uint8_t h) {
    if (h > 126) return;
    analog_threshold_ = h;
    analog_range_[0] = analog_center_ - analog_threshold_;
    analog_range_[1] = analog_center_ + analog_threshold_;
}

}
