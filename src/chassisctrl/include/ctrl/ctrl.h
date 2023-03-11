/**
 * @file ctrl.h
 * @author William Gong (gtl119@live.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include <cstring>

const int LEN_ID_CTRL = 4;
const int LEN_DATA_CTRL = 8;

class Ctrl {
    public:
        virtual bool getData(unsigned char* res) = 0;
        virtual bool getId(unsigned char* res) {
            if(sizeof(res) < LEN_ID_CTRL) {
                return false;
            }

            memcpy(res, id_, LEN_ID_CTRL);
            return true;
        }

    protected:
        unsigned char id_[LEN_ID_CTRL];
};