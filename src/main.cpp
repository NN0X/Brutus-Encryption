#include "algorithm.h"

int main(int argc, char *argv[])
{
    CHARSET charset;

    if (argc < 3)
    {
        std::cout << "Usage: " << argv[0] << " <text> <key>\n";
        return 1;
    }

    std::string text = argv[1];
    std::string key = argv[2];

    std::string encrypted = encrypt(charset, text, key);

    std::cout << encrypted << "\n";

    return 0;
}