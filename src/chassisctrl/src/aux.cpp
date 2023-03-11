#include "aux.h"

#include <cstring>

unsigned int charToUInt(const unsigned char *str, int len) {
    unsigned int res = 0;
    for(int i = 0; i < len; i++) {
        res <<= 8;
        res |= str[i];
    }
    return res;
}

unsigned long long charToULL(const unsigned char *str, int len) {
    unsigned long long res = 0;
    for(int i = 0; i < len; i++) {
        res <<= 8;
        res |= str[i];
    }
    return res;
}

bool uintToChar(unsigned int val, unsigned char *res, int len) {
    if(len < 4) {
        return false;
    }

    for(int i = 3; i >= 0; i++) {
        res[i] = val;
        val >>= 8;
    }

    return true;
}

bool ullToChar(unsigned long long val, unsigned char *res, int len) {
    if(len < 8) {
        return false;
    }

    for(int i = 7; i >= 0; i++) {
        res[i] = val;
        val >>= 8;
    }

    return true;
}

std::string getStr(Gear val) {
    if(val == NEUTRAL) {
        return STR_GEAR_NEUTRAL;
    }else if(val == FORWARD) {
        return STR_GEAR_FORWARD;
    }else if(val == BACK) {
        return STR_GEAR_BACK;
    }
}

std::string getStr(Mode val) {
    if(val == POWEROFF) {
        return STR_MODE_POWEROFF;
    }else if(val == STANDBY) {
        return STR_MODE_STANDBY;
    }else if(val == REMOTE_CTRL) {
        return STR_MODE_REMOTE_CTRL;
    }else if(val == WIRE_CTRL) {
        return STR_MODE_WIRE_CTRL;
    }else if(val == EMERGENCY) {
        return STR_MODE_EMERGENCY;
    }
}

std::string getStr(GearSwitch val) {
    if(val == REMOTE) {
        return STR_GEARSWITCH_REMOTE;
    }else if(val == WIRE) {
        return STR_GEARSWITCH_WIRE;
    }else if(val == OFFLINE) {
        return STR_GEARSWITCH_OFFLINE;
    }
}

std::string getStr(bool val) {
    if(val) {
        return "on";
    }else {
        return "off";
    }
}