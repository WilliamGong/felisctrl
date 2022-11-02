/**
 * @file motionctrl.h
 * @author William Gong (gtl119@live.com)
 * @brief 
 * MotionCtrl is the class used for process the control data send to chassis. 
 * @version 0.1
 * @date 2022-11-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "basetype.h"

#include <stdint.h>


enum ModeCtrl {
    /**
     * @brief 
     * Just used for control info, DO NOT use to other cases. 
     * 
     */
    REMOTE_ = 0x0,
    WIRE_ = 0x1
};

class MotionCtrl {
    public:
        //MotionCtrl();
        //~MotionCtrl();

        void setCtrlMode(ModeCtrl val) {this->control_mode_ = val;}
        void setGear(Gear val) {this->gear_ = val;}
        void setBrake(Brake val) {this->brake_ = val;}
        void setAccelerator(uint8_t val);
        void setAngle(short val);
        void setPressure(uint8_t val);

        bool getData(unsigned char* res);

    private:
        ModeCtrl control_mode_ = REMOTE_;
        Gear gear_ = NEUTRAL;
        Brake brake_ = ON;
        uint8_t accelerator_ = 0; // range: [0, 100]
        short angle_ = 0; // range: [-100, 100]
        uint8_t pressure_ = 0; // range: [0, 10]
};