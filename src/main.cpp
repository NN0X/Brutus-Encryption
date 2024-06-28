#include "algorithm.h"
#include <iostream>

void mode0(std::string text, std::string key)
{
    CHARSET charset(ENC::TEXT);
    std::string encrypted = encrypt(charset, text, key);
    std::cout << encrypted << "\n";
}

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

void mode1(std::string path, std::string key, std::string outputPath)
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

    std::cout << "Data written to " << outputPath << "\n";
}

int main(int argc, char *argv[])
{
    if (argc < 3 || argc > 4)
    {
        std::cout << "Usage: " << argv[0] << " <text> <key>\n";
        std::cout << "Usage: " << argv[0] << " <file> <key> <output>\n";
        return 1;
    }

    if (argc == 3)
    {
        mode0(argv[1], argv[2]);
    }
    else if (argc == 4)
    {
        mode1(argv[1], argv[2], argv[3]);
    }

    return 0;
}