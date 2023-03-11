/**
 * @file configctrl.cpp
 * @author William Gong (gtl119@live.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ctrl/configctrl.h"

ConfigCtrl::ConfigCtrl() {
    id_[0] = 0x0c;
    id_[1] = 0x02;
    id_[2] = 0xd1;
    id_[3] = 0xd0;
}

bool ConfigCtrl::getData(unsigned char *res) {
    if(sizeof(res) < LEN_DATA_CTRL) {
        return false;
    }

    unsigned char data[LEN_DATA_CTRL] = {0};

    data[0] = (unsigned char)config_item_;
    data[1] = (unsigned char)config_cmd_;

    memcpy(res, data, LEN_DATA_CTRL);
    return true;
}