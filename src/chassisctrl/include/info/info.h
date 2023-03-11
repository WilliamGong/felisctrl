/**
 * @file info.h
 * @author William Gong (gtl119@live.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

const int LEN_ID_INFO = 4;
const int LEN_DATA_INFO = 8;

class Info {
    public:
        virtual bool setData(const unsigned char *id, const unsigned char *data) = 0;
        virtual bool setData(const unsigned int id, const unsigned char *data) = 0;
};