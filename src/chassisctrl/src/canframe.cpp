#include "canframe.h"

#include <cstring>
#include <iostream>

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

    this->head_ = 0x88;
    memset(this->id_, 0, sizeof(this->id_));
    memset(this->data_, 0, sizeof(this->data_));
}

CanFrame::CanFrame(unsigned char* frame) {
    /**
     * @brief 
     * This constructor is used to create a CanFrame object from original CAN frame data
     * 
     */

    this->head_ = frame[0];
    if(this->getType() == STANDARD) {
        memcpy(this->id_, frame+1, LEN_ID_STANDARD);
        memcpy(this->data_, frame+1+LEN_ID_STANDARD, LEN_FRAME_DATA);

    }else if(this->getType() == EXTENDED) {
        memcpy(this->id_, frame+1, LEN_ID_EXTENED);
        memcpy(this->data_, frame+1+LEN_ID_EXTENED, LEN_FRAME_DATA);
    }
}

FrameType CanFrame::getType() {
    unsigned char type = this->head_ & MASK_TYPE;
    type >>= 7;
    return (FrameType)type;
}

RTRType CanFrame::getRTR() {
    unsigned char rtr = this->head_ & MASK_RTR;
    rtr >>= 6;
    return (RTRType)rtr;
}

int CanFrame::getLength() {
    int len = this->head_ & MASK_LENGTH;
    return len;
}

bool CanFrame::getId(unsigned char *res) {
    if((sizeof(res) < LEN_ID_STANDARD && this->getType() == STANDARD) || (sizeof(res) < LEN_ID_EXTENED && this->getType() == EXTENDED)) {
        return false;
    }
    if(this->getType() == STANDARD) {
        memcpy(res, this->id_, LEN_ID_STANDARD);
    }else if(this->getType() == EXTENDED) {
        memcpy(res, this->id_, LEN_ID_EXTENED);
    }
    return true;
}

bool CanFrame::getData(unsigned char *res) {
    if(sizeof(res) < LEN_FRAME_DATA || this->getRTR() == REMOTE_FRAME) {
        return false;
    }
    memcpy(res, this->data_, LEN_FRAME_DATA);
    return true;
}

bool CanFrame::getFrame(unsigned char *res, int len) {
    //std::cout << "len: " << len << std::endl;
    if(res == NULL) {
        return false;
    }
    res[0] = this->head_;
    if(this->getType() == STANDARD) {
        if(len < LEN_STANDARD) {
            return false;
        }
        memcpy(res+1, this->id_, LEN_ID_STANDARD);
        memcpy(res+1+LEN_ID_STANDARD, this->data_, LEN_FRAME_DATA);
    }else if(this->getType() == EXTENDED) {
        if(len < LEN_EXTENED) {
            return false;
        }
        memcpy(res+1, this->id_, LEN_ID_EXTENED);
        memcpy(res+1+LEN_ID_EXTENED, this->data_, LEN_FRAME_DATA);
    }
    return true;
}

void CanFrame::setType(FrameType type) {
    if(type == STANDARD) {
        this->head_ = this->head_ & MASK_TYPE;
    }else if(type == EXTENDED) {
        this->head_ = this->head_ | MASK_TYPE;
    }
}

bool CanFrame::setId(unsigned char *id) {
    int len = sizeof(id);
    //std::cout << "len: " << len << std::endl;
    if(this->getType() == STANDARD && len >= LEN_ID_STANDARD) {
        memcpy(this->id_, id, LEN_ID_STANDARD);
        return true;
    }else if(this->getType() == EXTENDED && len >= LEN_ID_EXTENED) {
        memcpy(this->id_, id, LEN_ID_EXTENED);
        return true;
    }else {
        return false;
    }
}

bool CanFrame::setData(unsigned char *data) {
    if(sizeof(data) > LEN_FRAME_DATA) {
        std::cout << "Warning: data recived is too large, only set " << LEN_FRAME_DATA << "bytes front. " << std::endl;
        memcpy(this->data_, data, LEN_FRAME_DATA);
    }else {
        memcpy(this->data_, data, sizeof(data));
    }
    return true;
}