/**
 * @file driveinfo.cpp
 * @author William Gong (gtl119@live.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "info/driveinfo.h"
#include "aux.h"

const unsigned int FRAME_ID = 0x18f026d1;

bool DriveInfo::setData(const unsigned char *id, const unsigned char *data) {
    if(charToUInt(id, LEN_ID_INFO) != FRAME_ID) {
        return false;
    }

    rev_ = data[2];
    rev_ <<= 8;
    rev_ |= data[3];

    return true;
}

bool DriveInfo::setData(const unsigned int id, const unsigned char *data) {
    if(id != FRAME_ID) {
        return false;
    }

    rev_ = data[2];
    rev_ <<= 8;
    rev_ |= data[3];

    return true;
}