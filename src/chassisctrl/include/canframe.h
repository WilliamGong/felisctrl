#pragma once

const unsigned char MASK_TYPE = 0x80;
const unsigned char MASK_RTR = 0x40;
const unsigned char MASK_LENGTH = 0x0f;

enum type {
    standard = 0,
    extended = 1
};
enum rtrType {
    dataframe = 0,
    remoteframe = 1
};

class CanFrame {
    private:
        unsigned char head;
        unsigned char id[4];
        unsigned char data[8];
    public:
        CanFrame(unsigned char *data);

        int getType();
        int getRTR();
        int getLength();
        void getId(unsigned char *res);
        void getData(unsigned char *res);
};
