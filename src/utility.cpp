#include "utility.h"
#include <string>

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

std::string fromHexString(std::string hex)
{
    std::string result;
    for (size_t i = 0; i < hex.size(); i += 2)
    {
        result += fromHex(hex.substr(i, 2));
    }
    return result;
}

std::string toHexString(char* bytes, int size)
{
    std::string result;
    for (int i = 0; i < size; i++)
    {
        result += toHex(bytes[i]);
    }
    return result;
}

