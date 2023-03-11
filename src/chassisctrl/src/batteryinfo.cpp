/**
 * @file batteryinfo.cpp
 * @author William Gong (gtl119@live.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "info/batteryinfo.h"
#include "aux.h"

const unsigned int FRAME_ID_1 = 0x18f020d1;
const unsigned int FRAME_ID_2 = 0x18f021d1;

bool BatteryInfo::setData(const unsigned char *id, const unsigned char *data) {
    if(charToUInt(id, LEN_ID_INFO) == FRAME_ID_1) {

        level_ = data[1];

        voltage_high_ = data[2];
        voltage_high_ <<= 8;
        voltage_high_ |= data[3];

        current_ = data[4];
        current_ <<= 8;
        current_ |= data[5];

    }else if(charToUInt(id, LEN_ID_INFO) == FRAME_ID_2) {

        voltage_low_ = data[2];
        voltage_low_ <<= 8;
        voltage_low_ = data[3];

    }else {
        return false;
    }

    return true;
}

bool BatteryInfo::setData(const unsigned int id, const unsigned char *data) {
    if(id == FRAME_ID_1) {

        level_ = data[1];

        voltage_high_ = data[2];
        voltage_high_ <<= 8;
        voltage_high_ |= data[3];

        current_ = data[4];
        current_ <<= 8;
        current_ |= data[5];

    }else if(id == FRAME_ID_2) {

        voltage_low_ = data[2];
        voltage_low_ <<= 8;
        voltage_low_ = data[3];

    }else {
        return false;
    }

    return true;
}