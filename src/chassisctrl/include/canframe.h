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
    DATA= 0,
    REMOTE = 1
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
    private:
        unsigned char head_;
        unsigned char id_[4];
        unsigned char data_[8];
};
