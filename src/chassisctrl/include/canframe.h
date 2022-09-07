#pragma once

const char MASK_TYPE = 0x80;
const char MASK_RTR = 0x40;
const char MASK_LENGTH = 0x0f;

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
        char id[4];
        char data[8];
    public:
        CanFrame(char *data);

        int getType();
        int getRTR();
        int getLength();
        void getId(char *res);
        void getData(char *res);
};
