/**
 * @file canframe.h
 * @author William Gong (gtl119@live.com)
 * @brief 
 * CanFrame class is a wrapper of CAN frame, support standard and extended, remote and data type. 
 * @version 0.1
 * @date 2022-11-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

const int LEN_STANDARD = 11;
const int LEN_EXTENED = 13;
const int LEN_ID_STANDARD = 2;
const int LEN_ID_EXTENED = 4;
const int LEN_DATA = 8;

const unsigned char MASK_TYPE = 0x80;
const unsigned char MASK_RTR = 0x40;
const unsigned char MASK_LENGTH = 0x0f;

enum FrameType {
    STANDARD,
    EXTENDED
};

enum RTRType {
    DATA_FRAME = 0,
    REMOTE_FRAME = 1
};

class CanFrame {
    public:
        CanFrame(unsigned char *frame);
        CanFrame();

        FrameType getType();
        RTRType getRTR();
        int getLength();
        bool getId(unsigned char *res);
        bool getData(unsigned char *res);
        bool getFrame(unsigned char *res);
        
        void setType(FrameType type);
        bool setId(unsigned char *id);
        bool setData(unsigned char *data);

    private:
        unsigned char head_;
        unsigned char id_[4];
        unsigned char data_[8];
};
