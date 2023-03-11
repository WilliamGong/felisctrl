/**
 * @file wheelspeedinfo.cpp
 * @author William Gong (gtl119@live.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "info/wheelspeedinfo.h"
#include "aux.h"

const unsigned int FRAME_ID = 0x18f01bd1;

bool WheelSpeedInfo::setData(const unsigned char *id, const unsigned char *data) {
    if(charToUInt(id, LEN_ID_INFO) != FRAME_ID) {
        return false;
    }

    for(int i = 0; i < 4; i++) {
        speed_left_rear_ <<= 8;
        speed_left_rear_ |= data[i];
        speed_right_rear_ <<= 8;
        speed_right_rear_ |= data[1+4];
    }

    return true;
}

bool WheelSpeedInfo::setData(const unsigned int id, const unsigned char *data) {
    if(id != FRAME_ID) {
        return false;
    }

    for(int i = 0; i < 4; i++) {
        speed_left_rear_ <<= 8;
        speed_left_rear_ |= data[i];
        speed_right_rear_ <<= 8;
        speed_right_rear_ |= data[1+4];
    }

    return true;
}