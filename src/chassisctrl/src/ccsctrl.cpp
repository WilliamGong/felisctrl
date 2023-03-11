/**
 * @file ccsctrl.cpp
 * @author William Gong (gtl119@live.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ctrl/ccsctrl.h"

CcsCtrl::CcsCtrl() {
    id_[0] = 0x0c;
    id_[1] = 0x07;
    id_[2] = 0xd1;
    id_[3] = 0xd0;
}

void CcsCtrl::setTargetSpeed(short val) {
    if(val < 0) {
        target_speed_ = 0;
    }else if(val > 100) {
        target_speed_ = 100;
    }else {
        target_speed_ = val;
    }
}

bool CcsCtrl::getData(unsigned char *res) {
    if(sizeof(res) < LEN_DATA_CTRL) {
        return false;
    }

    unsigned char data[LEN_DATA_CTRL] = {0};
    data[0] = is_enable;
    data[1] = (unsigned char)target_speed_ >> 8;
    data[2] = (unsigned char)target_speed_;

    memcpy(res, data, LEN_DATA_CTRL);
    return true;
}