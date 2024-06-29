#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "SHA512.h"

#ifdef ENABLE_ALIASES
#define ENC Encryption
#define CHARSET Encryption::CharacterSet
#endif

namespace Encryption
{
    enum
    {
        TEXT,
        HEX
    };

    const std::string CHARSET_FILE = "charset.txt";
    const bool DEBUG = false;

    const int CUTOFF_CONST = 3; // arbitrary value (not tested if necessary or optimal)

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

    int encryptCharacter(CharacterSet charset, char character, unsigned long long int key, int position);

    unsigned long long int genPseudouniqueInteger(std::string text); // pretty much the most important function in this file (the pseudo part)
    unsigned long long int convertKey(std::string key);

    std::string encrypt(CharacterSet charset, std::string text, std::string key);

}

#endif // ALGORITHM_H