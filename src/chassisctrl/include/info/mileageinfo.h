/**
 * @file mileageinfo.h
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

class MileageInfo : public Info {
    public:

        bool setData(const unsigned char *id, const unsigned char *data);
        bool setData(const unsigned int id, const unsigned char *data);

        short getSpeed() {return speed_;}
        unsigned short getTrip() {return trip_;}
        unsigned int getOdo() {return odo_;}

    private:
        short speed_;
        unsigned short trip_;
        unsigned int odo_;
};