/**
 * @file driveinfo.h
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

class DriveInfo : public Info {
    public:

        bool setData(const unsigned char *id, const unsigned char *data);
        bool setData(const unsigned int id, const unsigned char *data);

        unsigned short getRev() {return rev_;}

    private:
        unsigned short rev_;
};