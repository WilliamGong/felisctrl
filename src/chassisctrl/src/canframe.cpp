#include "canframe.h"

#include <cstring>

CanFrame::CanFrame() {
    /**
     * @brief
     * This default constructor is used to create a empty CanFrame object with default parameters below:  
     * frame structure: extended (FF = 1)
     * frame type: data frame (RTR = 0)
     * data length: 8byte
     * frame ID: 0
     * frame Data: 0
     * 
     */

    this->head = 0x88;
    memset(this->id, 0, sizeof(this->head));
    memset(this->data, 0, sizeof(this->data));
}

CanFrame::CanFrame(unsigned char* frame) {
    /**
     * @brief 
     * This constructor is used to create a CanFrame object from original CAN frame data
     * 
     */

    this->head = frame[0];
    int lenData = sizeof(frame);
    if(this->getType() == STANDARD) {
        memcpy(this->id, frame+1, LEN_ID_STANDARD);
        memcpy(this->data, frame+1+LEN_ID_STANDARD, LEN_DATA);

    }else if(this->getType() == EXTENDED) {
        memcpy(this->id, frame+1, LEN_ID_EXTENED);
        memcpy(this->data, frame+1+LEN_ID_EXTENED, LEN_DATA);
    }
}

FrameType CanFrame::getType() {
    int type = this->head & MASK_TYPE;
    type >> 7;
    return (FrameType)type;
}

RTRType CanFrame::getRTR() {
    int rtr = this->head & MASK_RTR;
    rtr >> 6;
    return (RTRType)rtr;
}

int CanFrame::getLength() {
    int len = this->head & MASK_LENGTH;
    return len;
}

bool CanFrame::getId(unsigned char *res) {
    if((sizeof(res) < LEN_ID_STANDARD && this->getType() == STANDARD) || (sizeof(res) < LEN_ID_EXTENED && this->getType() == EXTENDED)) {
        return false;
    }
    if(this->getType() == STANDARD) {
        memcpy(res, this->id, LEN_ID_STANDARD);
    }else if(this->getType() == EXTENDED) {
        memcpy(res, this->id, LEN_ID_EXTENED);
    }
    return true;
}

bool CanFrame::getData(unsigned char *res) {
    if(sizeof(res) < LEN_DATA || this->getRTR() == REMOTE) {
        return false;
    }
    memcpy(res, this->data, LEN_DATA);
    return true;
}

bool CanFrame::getFrame(unsigned char *res) {
    if(res == nullptr) {
        return false;
    }
    res[0] = this->head;
    if(this->getType() == STANDARD) {
        if(sizeof(res) < LEN_STANDARD) {
            return false;
        }
        memcpy(res+1, this->id, LEN_ID_STANDARD);
        memcpy(res+1+LEN_ID_STANDARD, this->data, LEN_DATA);
    }else if(this->getType() == EXTENDED) {
        if(sizeof(res) < LEN_EXTENED) {
            return false;
        }
        memcpy(res+1, this->id, LEN_ID_EXTENED);
        memcpy(res+1+LEN_ID_EXTENED, this->data, LEN_DATA);
    }
    return true;
}