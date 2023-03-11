/**
 * @file configctrl.h
 * @author William Gong (gtl119@live.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include "ctrl.h"

enum ConfigItem {
    STEERING_ASSEMBLY = 0x01
};

enum ConfigCmd {
    SET_ZERO = 0x01     // set current angle to zero
};

class ConfigCtrl : public Ctrl {
    public:
        ConfigCtrl();

        void setConfigItem(ConfigItem val) {config_item_ = val;}
        void setConfigCmd(ConfigCmd val) {config_cmd_ = val;}
        bool getData(unsigned char* res);

    private:
        ConfigItem config_item_;
        ConfigCmd config_cmd_;
};