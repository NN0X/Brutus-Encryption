#include "algorithm.h"

Encryption::CharacterSet::CharacterSet()
    : charactersPrintable(""), characters(), size(0)
{
    load();
}

void Encryption::CharacterSet::load()
{
    std::ifstream file("chars.txt");
    if (!file.is_open())
    {
        std::cerr << "Failed to load character set";
        return;
    }

    size = 0;
    std::string line;
    while (std::getline(file, line))
    {
        for (size_t i = 0; i < line.size(); i++)
        {
            charactersPrintable += line;
            if (find(characters.begin(), characters.end(), line[i]) != characters.end())
            {
                continue;
            }
            characters.push_back(line[i]);
            size++;
        }
    }

    file.close();

    sort();
}

void Encryption::CharacterSet::sort()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (characters[j] > characters[j + 1])
            {
                int temp = characters[j];
                characters[j] = characters[j + 1];
                characters[j + 1] = temp;
            }
        }
    }
}

void Encryption::CharacterSet::print()
{
    std::cout << charactersPrintable << "\n";
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

int Encryption::encryptCharacter(CHARSET charset, char character, int key, int position)
{
    int characterNum = charset[character];
    int encryptionNum = key * (position + key);
    std::string encryptionStr = std::to_string(encryptionNum);
    std::reverse(encryptionStr.begin(), encryptionStr.end());
    std::string encryptionStrCutoff = encryptionStr.substr(0, encryptionStr.size() - OFFSET_CONST);
    int encryptionSign = 0;
    for (size_t i = 0; i < encryptionStrCutoff.size(); i++)
    {
        encryptionSign += encryptionStrCutoff[i];
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

int Encryption::convertKey(std::string key)
{
    SHA512 sha512;
    std::string keyHash = sha512.hash(key);

    int keyNum = 0;
    for (size_t i = 0; i < keyHash.size(); i++)
    {
        keyNum += keyHash[i] * pow(10, i);
    }

    if (keyNum < 0)
    {
        return keyNum * -1;
    }
    else
    {
        return keyNum;
    }
}

std::string Encryption::encrypt(CHARSET charset, std::string text, std::string key)
{
    std::string encryptedText = "";
    for (size_t i = 0; i < text.size(); i++)
    {
        encryptedText += charset[encryptCharacter(charset, text[i], convertKey(key), i)];
    }

    return encryptedText;
}
