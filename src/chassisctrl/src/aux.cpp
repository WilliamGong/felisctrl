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