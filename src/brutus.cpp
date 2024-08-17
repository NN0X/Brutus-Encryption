#define ENABLE_ALIASES

#include "brutus.h"
#include "algorithm.h"
#include "utility.h"

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
