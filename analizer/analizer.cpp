#include "../src/brutus.h"

#include <iostream>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <word> <key>" << std::endl;
		return 1;
	}

	std::string word = argv[1];
	std::string key = argv[2];
	unsigned long long int keyInt = Brutus::Internal::convertKey(key);
	std::cout << keyInt << "\n";
	
	for (size_t i = 0; i < word.size(); i++)
	{
		std::cout << Brutus::Internal::encryptCharacter(word[i], keyInt, i) << " ";
	}

	return 0;
}
