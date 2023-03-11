#pragma once

#include "basetype.h"

unsigned int charToUInt(const unsigned char *str, int len);
unsigned long long charToULL(const unsigned char *str, int len);
bool uintToChar(unsigned int val, unsigned char *res, int len);
bool ullToChar(unsigned long long val, unsigned char *res, int len);

std::string getStr(Gear val);
std::string getStr(Mode val);
std::string getStr(GearSwitch val);
std::string getStr(bool val);