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
		std::string toHex(char byte);
		char fromHex(std::string hex);

		std::string hashSHA512(std::string text);
	}
}

#endif // BRUTUS_H
