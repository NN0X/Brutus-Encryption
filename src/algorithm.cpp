﻿#include "algorithm.h"

Encryption::CharacterSet::CharacterSet(int mode)
    : characters(), size(0)
{
    if (mode == TEXT)
    {
        load();
    }
    else if (mode == HEX)
    {
        characters = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                      'A', 'B', 'C', 'D', 'E', 'F'};
        size = characters.size();
    }
    else
    {
        std::cerr << "Invalid character set mode\n";
    }
}

void Encryption::CharacterSet::load()
{
    std::ifstream file("charset.txt");
    if (!file.is_open())
    {
        std::cerr << "Failed to load character set";
        exit(1);
    }

    file.seekg(0, std::ios::end);
    size = file.tellg();
    file.seekg(0, std::ios::beg);
    characters.resize(size);

    file.read(&characters[0], size);

    file.close();

    sort();
}

void Encryption::CharacterSet::sort()
{
    std::sort(characters.begin(), characters.end());
}

void Encryption::CharacterSet::print()
{
    for (char character : characters)
    {
        std::cout << character;
    }
    std::cout << "\n";
}

char Encryption::CharacterSet::operator[](int index)
{
    return characters[index];
}

int Encryption::CharacterSet::operator[](char character)
{

    int pivot = size / 2;
    int left = 0;
    int right = size - 1;

    while (left <= right)
    {
        if (characters[pivot] == character)
        {
            return pivot;
        }
        else if (characters[pivot] < character)
        {
            left = pivot + 1;
        }
        else
        {
            right = pivot - 1;
        }
        pivot = (left + right) / 2;
    }

    return -1;
}

int Encryption::encryptCharacter(CHARSET charset, char character, unsigned long long int key, int position)
{
    int characterNum = charset[character];
    unsigned long long int encryptionNum = key * (position + key);
    std::string encryptionStr = std::to_string(encryptionNum);
    std::reverse(encryptionStr.begin(), encryptionStr.end());
    std::string encryptionStrCutoff = encryptionStr.substr(0, encryptionStr.size() - CUTOFF_CONST);
    int encryptionSign = 0;
    for (size_t i = 0; i < encryptionStr.size(); i++)
    {
        encryptionSign += encryptionStr[i];
    }

    int offset;
    if (encryptionSign >= charset.size)
    {
        offset = encryptionSign - int(floor(encryptionSign / charset.size) * charset.size);
    }
    else
    {
        offset = encryptionSign;
    }

    if (offset - characterNum < 0)
    {
        return offset - characterNum + charset.size;
    }
    else
    {
        return offset - characterNum;
    }
}

unsigned long long int Encryption::stringToInt(std::string text)
{
    unsigned long long int num = 0;
    const double E = 2.71828182845904523536;
    for (size_t i = 0; i < text.size(); i++)
    {
        num += text[i] * (unsigned long long int)(pow(E, i) * sin(i) * cos(i));
    }

    return num;
}

unsigned long long int Encryption::convertKey(std::string key)
{
    SHA512 sha512;
    std::string keyHash = sha512.hash(key);

    unsigned long long int keyNum = stringToInt(keyHash);

    return keyNum;
}

std::string Encryption::encrypt(CHARSET charset, std::string text, std::string key)
{
    unsigned long long int keyNum = convertKey(key);
    std::string encryptedText = "";
    for (size_t i = 0; i < text.size(); i++)
    {
        if (std::find(charset.characters.begin(), charset.characters.end(), text[i]) == charset.characters.end())
        {
            std::cerr << "'" << text[i] << "' not found in charset\n";
            continue;
        }
        encryptedText += charset[encryptCharacter(charset, text[i], keyNum, i)];
    }

    return encryptedText;
}
