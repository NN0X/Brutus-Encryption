#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>

std::string toHex(char byte);
char fromHex(std::string hex);
std::string fromHexString(std::string hex);
std::string toHexString(char* bytes, int size);

#endif
