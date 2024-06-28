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
    enum
    {
        TEXT,
        HEX
    };

    const int CUTOFF_CONST = 3;

    struct CharacterSet
    {
        std::vector<char> characters;
        int size;

        CharacterSet(int mode);

        void load();
        void sort();
        void print();

        char operator[](int index);
        int operator[](char character);
    };

    int encryptCharacter(CHARSET charset, char character, unsigned long long int key, int position);

    unsigned long long int stringToInt(std::string text);
    unsigned long long int convertKey(std::string key);
    std::string encrypt(CHARSET charset, std::string text, std::string key);

}

#endif // ALGORITHM_H