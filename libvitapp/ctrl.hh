#pragma once

#include "singleton.hh"

namespace vitapp {

class ctrl: public singleton<ctrl> {
public:
    enum class mode {
        digital = 0,
        analog = 1,
        analog_wide = 2,
    };
    enum button: uint32_t {
        select        = 0x000001,
        start         = 0x000008,
        up            = 0x000010,
        right         = 0x000020,
        down          = 0x000040,
        left          = 0x000080,
        ltrigger      = 0x000100,
        rtrigger      = 0x000200,
        triangle      = 0x001000,
        circle        = 0x002000,
        cross         = 0x004000,
        square        = 0x008000,
        any           = 0x010000,
        lanalog_up    = 0x0020000,
        lanalog_right = 0x0040000,
        lanalog_down  = 0x0080000,
        lanalog_left  = 0x0100000,
        ranalog_up    = 0x0200000,
        ranalog_right = 0x0400000,
        ranalog_down  = 0x0800000,
        ranalog_left  = 0x1000000,
    };

protected:
    ctrl();

public:
    virtual ~ctrl() override;

    mode get_mode();
    void set_mode(mode);

    inline uint8_t get_analog_threshold() { return analog_threshold_; }
    inline void set_analog_threshold(uint8_t h);

    void capture_buttons();
    inline int get_buttons() { return buttons_; }

private:
    uint32_t buttons_ = 0;
    const uint8_t analog_center_ = 128;
    uint8_t analog_threshold_ = 64;
    uint8_t analog_range_[2] = {64, 64};
};

}
