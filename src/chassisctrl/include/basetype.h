/**
 * @file basetype.h
 * @author William Gong (gtl119@live.com)
 * @brief 
 * The header provides basic data types of chassis data, including: 
 * Gear: stands for the gear of chassis, could be forward, neutral and back. 
 * Mode: stands for the operating mode of chassis
 * GearSwitch: stands for the status of the control mode, wire control or remote control
 * @version 0.1
 * @date 2022-11-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

enum Gear {
        NEUTRAL = 0x0,
        FORWARD = 0x1,
        BACK = 0x2
};

enum Mode {
    POWEROFF = 0x00,
    STANDBY = 0x10,
    REMOTE_CTRL = 0x30,
    WIRE_CTRL = 0x40,
    EMERGENCY = 0x50
};

enum GearSwitch {
    REMOTE = 0x0,
    WIRE = 0x1,
    OFFLINE = 0x2
};