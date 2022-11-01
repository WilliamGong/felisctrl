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
        neutral = 0x0,
        forward = 0x1,
        back = 0x2
};

enum Mode {
    poweroff = 0x00,
    standby = 0x10,
    remoteCtrl = 0x30,
    wireCtrl = 0x40,
    emergency = 0x50
};

enum GearSwitch {
    remote = 0x0,
    wire = 0x1,
    offline = 0x2
};