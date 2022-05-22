#pragma once
#include <stdint.h>

// TODO: 将所有从底盘到工控机的数据进行封装

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

struct StatusInfo {
    /**
     * From frame with id: 0x18F014D1
     * 
     */

    Mode currentMode;
    unsigned short fault;

    uint8_t countStatus1;   //range: [0, 15]

    /**
     * From frame with id: 0x18F015D1
     * 
     */

    Gear remote;

    Gear realtime;

    // range: [0, 100] percent
    uint8_t remoteAccelerator;
    uint8_t realtimeAccelerator;

    short angle;    //range: [-100, 100] to [-35, 35] angle
    uint8_t countStatus2;  //range: [0, 15]

    /**
     * From frame with id: 0x18F016D1
     * 
     */

    uint8_t pressure;    //range: [0-11] to [0, 5.5] mpa

    uint8_t brake;     //off: 0, on: 1, other: error

    GearSwitch remoteMode;

    uint8_t emergencyStatus;   //off: 0, on: 1, other: error

    bool remoteStatus;      //off: false, on: true

    uint8_t countStatus3;    //range: [0, 15]
};

struct mileageInfo {
    /**
     * From frame with id: 0x18F01AD1
     * 
     */

    short speed;   // range: [-1000, 1000]km/h negative means back

    unsigned short accumulatedMileage;      // range: [0, 0xFFFF]km mileage from last start

    unsigned int allMileage;    //range: [0, FFFFFF]km

    unsigned short count;   //range: [0, 15]
};