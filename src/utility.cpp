#include "utility.h"

std::string toHex(char byte)
{
    std::string hex = "0123456789ABCDEF";
    std::string result;
    result += hex[(byte & 0xF0) >> 4];
    result += hex[byte & 0x0F];
    return result;
}

char fromHex(std::string hex)
{
    std::string hexChars = "0123456789ABCDEF";
    int result = 0;
    for (char c : hex)
    {
        result = result * 16 + hexChars.find(c);
    }
    return result;
}

