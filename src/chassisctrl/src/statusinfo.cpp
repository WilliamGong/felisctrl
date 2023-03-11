/**
 * @file statusinfo.cpp
 * @author William Gong (gtl119@live.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "info/statusinfo.h"
#include "aux.h"

const unsigned int FRAME_ID_1 = 0x18f014d1;
const unsigned int FRAME_ID_2 = 0x18f015d1;
const unsigned int FRAME_ID_3 = 0x18f016d1;

bool StatusInfo::setData(const unsigned char *id, const unsigned char *data) {
 if(charToUInt(id, LEN_ID_INFO) == FRAME_ID_1) {

    mode_ = (Mode)data[0];
    short err_code = data[2];
    err_code <<= 8;
    err_code |= data[3];
    error_ = (Error)err_code;

 }else if(charToUInt(id, LEN_ID_INFO) == FRAME_ID_2) {

    remote_gear_ = (Gear)data[0];
    current_gear_ = (Gear)(data[0] >> 4);
    remote_accelerator_ = data[1];
    current_accelerator_ = data[2];
    angle_ = data[3];
    angle_ <<= 8;
    angle_ |= data[4];

 }else if(charToUInt(id, LEN_ID_INFO) == FRAME_ID_3) {

    brake_pressure_ = data[1];
    is_parking_ = data[2] >> 4;
    gear_switch_ = (GearSwitch)(data[5] >> 2);
    is_emergency_ = data[5] >> 6;
    is_remote_on_ = data[7];
 }else {
    return false;
 }

 return true;
}

bool StatusInfo::setData(const unsigned int id, const unsigned char *data) {
 if(id == FRAME_ID_1) {

    mode_ = (Mode)data[0];
    short err_code = data[2];
    err_code <<= 8;
    err_code |= data[3];
    error_ = (Error)err_code;

 }else if(id == FRAME_ID_2) {

    remote_gear_ = (Gear)data[0];
    current_gear_ = (Gear)(data[0] >> 4);
    remote_accelerator_ = data[1];
    current_accelerator_ = data[2];
    angle_ = data[3];
    angle_ <<= 8;
    angle_ |= data[4];

 }else if(id == FRAME_ID_3) {

    brake_pressure_ = data[1];
    is_parking_ = data[2] >> 4;
    gear_switch_ = (GearSwitch)(data[5] >> 2);
    is_emergency_ = data[5] >> 6;
    is_remote_on_ = data[7];
 }else {
    return false;
 }

 return true;
}