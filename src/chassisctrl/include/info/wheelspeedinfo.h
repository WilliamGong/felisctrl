/**
 * @file wheelspeedinfo.h
 * @author William Gong (gtl119@live.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include "info.h"

class WheelSpeedInfo : public Info {
    public:

        bool setData(const unsigned char *id, const unsigned char *data);
        bool setData(const unsigned int id, const unsigned char *data);

        unsigned int getSpeedLeft() {return speed_left_rear_;}
        unsigned int getSpeedRight() {return speed_right_rear_;}

    private:
        unsigned int speed_left_rear_;
        unsigned int speed_right_rear_;
};