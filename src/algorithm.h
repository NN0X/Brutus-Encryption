#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "SHA512.h"

#define ENC Encryption
#define CHARSET Encryption::CharacterSet

namespace Encryption
{
    const int OFFSET_CONST = 18;

    struct CharacterSet
    {
        std::vector<char> characters;
        int size;

        CharacterSet();

        void load();
        void sort();
        void print();

        char operator[](int index);
        int operator[](char character);
    };

    int encryptCharacter(CHARSET charset, char character, int key, int position);

    int stringToInt(std::string text);
    int convertKey(std::string key);
    std::string encrypt(CHARSET charset, std::string text, std::string key);

}

#endif // ALGORITHM_H