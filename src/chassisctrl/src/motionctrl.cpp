/**
 * @file motionctrl.cpp
 * @author William Gong (gtl119@live.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "motionctrl.h"

#include <cstring>

void MotionCtrl::setAccelerator(uint8_t val) {
    if(val > 100) {
        this->accelerator_ = 100;
    }else if(val < 0) {
        this->accelerator_ = 0;
    }else {
        this->accelerator_ = val;
    }
}

void MotionCtrl::setAngle(short val) {
    if(val > 100) {
        this->angle_ = 100;
    }else if(val < -100) {
        this->angle_ = -100;
    }else {
        this->angle_ = val;
    }
}

void MotionCtrl::setPressure(uint8_t val) {
    if(val > 10) {
        this->pressure_ = 10;
    }else if(val < 0) {
        this->pressure_ = 0;
    }else {
        this->pressure_ = val;
    }
}

bool MotionCtrl::getData(unsigned char* res) {
    if(sizeof(res) < 8) {
        return false;
    }

    unsigned char data[8] = {0};

    data[0] = (unsigned char)this->control_mode_;

    unsigned char data_1 = 0;
    data_1 |= (unsigned char)this->brake_;
    data_1 <<= 4;
    data_1 |= (unsigned char)this->gear_;
    data[1] = data_1;

    data[2] = this->accelerator_;

    data[3] = (unsigned char)this->angle_ >> 8;
    data[4] = (unsigned char)this->angle_;

    data[6] = (unsigned char)this->pressure_;

    memcpy(res, data, LEN_DATA);
}