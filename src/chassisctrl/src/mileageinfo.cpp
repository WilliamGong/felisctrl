/**
 * @file mileageinfo.cpp
 * @author William Gong (gtl119@live.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "info/mileageinfo.h"
#include "aux.h"

const unsigned int FRAME_ID = 0x18f01ad1;

bool MileageInfo::setData(const unsigned char *id, const unsigned char *data) {
    if(charToUInt(id, LEN_ID_INFO) != FRAME_ID) {
        return false;
    }

    speed_ = data[0];
    speed_ <<= 8;
    speed_ |= data[1];

    trip_ = data[2];
    trip_ <<= 8;
    trip_ |= data[3];

    odo_ = data[4];
    odo_ <<= 8;
    odo_ |= data[5];
    odo_ <<= 8;
    odo_ |= data[6];

    return true;
}

bool MileageInfo::setData(const unsigned int id, const unsigned char *data) {
    if(id != FRAME_ID) {
        return false;
    }

    speed_ = data[0];
    speed_ <<= 8;
    speed_ |= data[1];

    trip_ = data[2];
    trip_ <<= 8;
    trip_ |= data[3];

    odo_ = data[4];
    odo_ <<= 8;
    odo_ |= data[5];
    odo_ <<= 8;
    odo_ |= data[6];

    return true;
}