#define ENABLE_ALIASES

#include "brutus.h"
#include "algorithm.h"
#include "utility.h"
#include "SHA512.h"

#include <iostream>

std::string Brutus::text(std::string text, std::string key)
{
    CHARSET charset(ENC::TEXT);
    std::string encrypted = encrypt(charset, text, key);
    return encrypted;
}

std::string Brutus::file(std::string path, std::string key)
{
    std::ifstream file(path, std::ios::binary);
    std::vector<char> data;
    file.seekg(0, std::ios::end);
    int size = file.tellg();
    data.resize(size);
    file.seekg(0, std::ios::beg);
    file.read(&data[0], size);
    file.close();

    std::string hex;
    for (char byte : data)
    {
        hex += toHex(byte);
    }

    CHARSET charset(ENC::HEX);
    std::string encrypted = encrypt(charset, hex, key);

    return encrypted;
}

std::string Brutus::file(std::string path, std::string key, std::string outputPath)
{
    std::ifstream file(path, std::ios::binary);
    std::vector<char> data;
    file.seekg(0, std::ios::end);
    int size = file.tellg();
    data.resize(size);
    file.seekg(0, std::ios::beg);
    file.read(&data[0], size);
    file.close();

    std::string hex;
    for (char byte : data)
    {
        hex += toHex(byte);
    }

    CHARSET charset(ENC::HEX);
    std::string encrypted = encrypt(charset, hex, key);

    std::ofstream output(outputPath, std::ios::binary);
    for (size_t i = 0; i < encrypted.size(); i += 2)
    {
        output << fromHex(encrypted.substr(i, 2));
    }
    output.close();

    return encrypted;
}

std::string Brutus::Utility::toHex(char* bytes, int size)
{
    return ::toHexString(bytes, size);
}

std::string Brutus::Utility::fromHex(std::string hex)
{
    return ::fromHexString(hex);
}

std::string Brutus::Utility::hashSHA512(std::string input)
{
    SHA512 sha512;
    return sha512.hash(input);

}

int Brutus::Internal::encryptCharacter(char character, unsigned long long int key, int position)
{
    return Encryption::encryptCharacter(CHARSET(ENC::TEXT), character, key, position);
}

unsigned long long int Brutus::Internal::genPseudouniqueInteger(std::string text)
{
    return Encryption::genPseudouniqueInteger(text);
}

unsigned long long int Brutus::Internal::convertKey(std::string key)
{
    return Encryption::convertKey(key);
}

std::string Brutus::Internal::encrypt(std::string text, std::string key)
{
    return Encryption::encrypt(CHARSET(ENC::TEXT), text, key);
}
