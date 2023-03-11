/**
 * @file batteryinfo.h
 * @author William Gong (gtl119@live.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include "info.h"

#include <stdint.h>

class BatteryInfo : public Info {
    public:

        bool setData(const unsigned char *id, const unsigned char *data);
        bool setData(const unsigned int id, const unsigned char *data);

        uint8_t getLevel() {return level_;}
        unsigned short getVoltageHigh() {return voltage_high_;}
        short getCurrent() {return current_;}
        unsigned short getVoltageLow() {return voltage_low_;}

    private:
        uint8_t level_;
        unsigned short voltage_high_;
        short current_;
        unsigned short voltage_low_;
};