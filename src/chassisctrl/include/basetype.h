/**
 * @file basetype.h
 * @author William Gong (gtl119@live.com)
 * @brief 
 * The header provides basic data types of chassis data, including: 
 * Gear: stands for the gear of chassis, could be forward, neutral and back. 
 * Mode: stands for the operating mode of chassis
 * GearSwitch: stands for the status of the control mode, wire control or remote control
 * Brake: stands for the brake of chassis, OFF means brake released, ON means brake enable. 
 * @version 0.1
 * @date 2022-11-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <string>

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

enum Error {
    NORMAL = 0x0000,
    ACTUATION_VOLTAGE_HIGH = 0x1001,
    ACTUATION_VOLTAGE_LOW = 0x1002,
    CTRL_VOLTAGE_HIGH = 0x1003,
    CTRL_VOLTAGE_LOW = 0x1004,
    ACTUATION_ERR = 0x2001,
    STEERING_ERR = 0x2101,
    BRAKE_ERR = 0x2201,
    PARKING_ERR = 0x2301,
    CONTROL_ERR = 0x2401
};

const std::string STR_GEAR_NEUTRAL = "neutral";
const std::string STR_GEAR_FORWARD = "forward";
const std::string STR_GEAR_BACK = "back";


const std::string STR_MODE_POWEROFF = "power off";
const std::string STR_MODE_STANDBY = "standby";
const std::string STR_MODE_REMOTE_CTRL = "remote control";
const std::string STR_MODE_WIRE_CTRL = "wire control";
const std::string STR_MODE_EMERGENCY = "emergency";

const std::string STR_GEARSWITCH_REMOTE = "remote";
const std::string STR_GEARSWITCH_WIRE = "wire";
const std::string STR_GEARSWITCH_OFFLINE = "offline";