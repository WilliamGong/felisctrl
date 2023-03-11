/**
 * @file ccsctrl.h
 * @author William Gong (gtl119@live.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include "ctrl.h"

#include <stdint.h>

class CcsCtrl : public Ctrl {
    public:
        CcsCtrl();

        void setIsEnable(bool val) {is_enable = uint8_t(val);}
        void setTargetSpeed(short val);
        bool getData(unsigned char *res);
    private:
        uint8_t is_enable = 0;
        short target_speed_;
};
