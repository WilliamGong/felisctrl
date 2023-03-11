/**
 * @file statusinfo.h
 * @author William Gong (gtl119@live.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include "info.h"
#include "basetype.h"

#include <stdint.h>

class StatusInfo : public Info {
    public:
        bool setData(const unsigned char *id, const unsigned char *data);
        bool setData(const unsigned int id, const unsigned char *data);

        Mode getMode() {return mode_;}
        Error getError() {return error_;}
        Gear getRemoteGear() {return remote_gear_;}
        Gear getCurrentGear() {return current_gear_;}
        uint8_t getRemoteAcc() {return remote_accelerator_;}
        uint8_t getCurrentAcc() {return current_accelerator_;}
        short getAngle() {return angle_;}
        uint8_t getBrakePressure() {return brake_pressure_;}
        bool getIsParking() {return is_parking_;}
        GearSwitch getGearSwitch() {return gear_switch_;}
        bool getIsEmergency() {return is_emergency_;}
        bool getIsRemoteOn() {return is_remote_on_;}

    private:
        Mode mode_;
        Error error_;
        Gear remote_gear_;
        Gear current_gear_;
        uint8_t remote_accelerator_;
        uint8_t current_accelerator_;
        short angle_;
        uint8_t brake_pressure_;
        bool is_parking_;
        GearSwitch gear_switch_;
        bool is_emergency_;
        bool is_remote_on_;
};