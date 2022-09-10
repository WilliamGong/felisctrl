#include "canframe.h"

#include <cstring>

CanFrame::CanFrame(unsigned char* data) {
    this->head = data[0];
    int lenData = sizeof(data);
    memcpy(this->id, data+sizeof(char), 4*sizeof(char));
    memcpy(this->data, data+5*sizeof(char), getLength());
}

int CanFrame::getType() {
    int type = this->head & MASK_TYPE;
    type >> 7;
    return type;
}

int CanFrame::getRTR() {
    int rtr = this->head & MASK_RTR;
    rtr >> 6;
    return rtr;
}

int CanFrame::getLength() {
    int len = this->head & MASK_LENGTH;
    return len;
}

void CanFrame::getId(unsigned char *res) {
    memcpy(res, this->id, 4);
}

void CanFrame::getData(unsigned char *res) {
    memcpy(res, this->data, 8);
}