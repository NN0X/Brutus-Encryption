#define ENABLE_ALIASES

#include "brutus.h"
#include "algorithm.h"
#include <iostream>

void dictionaryAttack()
{
    std::ifstream dict("dict.txt");
    if (!dict.is_open())
    {
        std::cerr << "Failed to open dictionary\n";
        exit(1);
    }
    std::vector<std::string> words;
    std::string word;
    while (std::getline(dict, word))
    {
        words.push_back(word);
    }
    dict.close();

    std::cout << "Loaded " << words.size() << " words\n";
    std::cout << "Press enter to begin the test...\n";
    std::cin.get();

    CHARSET charset(ENC::TEXT);
    std::vector<std::string> encryptedWords = {};
    std::string message = "Hello, World!";
    int duplicates = 0;
    for (size_t i = 0; i < words.size(); i++)
    {
        std::string encrypted = encrypt(charset, message, words[i]);
        size_t index = std::find(encryptedWords.begin(), encryptedWords.end(), encrypted) - encryptedWords.begin();
        if (index == encryptedWords.size())
        {
            encryptedWords.push_back(encrypted);
        }
        else
        {
            duplicates++;
            std::cout << "Duplicate: " << words[i] << " at index: " << index << "\n";
        }

        std::cout << "Progress: " << (i + 1) << "/" << words.size() << "\r";
    }

    std::cout << "Encrypted words: " << encryptedWords.size() << "\n";
    std::cout << "Duplicates: " << duplicates << "\n";
}


int main(int argc, char *argv[])
{
    if (argc == 2 && std::string(argv[1]) == "test")
    {
        dictionaryAttack();
        return 0;
    }
    if (argc < 3 || argc > 4)
    {
        std::cout << "Usage: " << argv[0] << " <text> <key>\n";
        std::cout << "Usage: " << argv[0] << " <file> <key> <output>\n";
        return 1;
    }

    if (argc == 3)
    {
        std::cout << Brutus::text(argv[1], argv[2]) << "\n";
    }
    else if (argc == 4)
    {
        Brutus::file(argv[1], argv[2], argv[3]);
        std::cout << "Data written to " << argv[3] << "\n";
    }

    return 0;
}
