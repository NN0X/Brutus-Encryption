#ifndef BRUTUS_H
#define BRUTUS_H

#include <iostream>

namespace Brutus
{
	std::string text(std::string text, std::string key);
	std::string file(std::string inputPath, std::string key);
	std::string file(std::string inputPath, std::string key, std::string outputPath);

	namespace Utility
	{
		std::string toHex(char *bytes, int size);
		std::string fromHex(std::string hex);
		std::string hashSHA512(std::string input);
	}

	namespace Internal
	{
		int encryptCharacter(char character, unsigned long long int key, int position);
		unsigned long long int genPseudouniqueInteger(std::string text);
		unsigned long long int convertKey(std::string key);
		std::string encrypt(std::string text, std::string key);
	}
}

#endif // BRUTUS_H
