#include "aux.h"

#include <cstring>

unsigned int charToUInt(const char *str) {
    unsigned int res = 0;
    for(int i = 0; i < strlen(str); i++) {
        res = (res | str[i]) << 8;
    }
    return res;
}