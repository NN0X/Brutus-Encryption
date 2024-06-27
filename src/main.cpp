#include "algorithm.h"
#include <sstream>
#include <iostream>

void mode0(std::string text, std::string key)
{
    CHARSET charset;
    std::string encrypted = encrypt(charset, text, key);
    std::cout << encrypted << "\n";
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "Usage: " << argv[0] << " <text> <key>\n";
        return 1;
    }
    mode0(argv[1], argv[2]);

    return 0;
}