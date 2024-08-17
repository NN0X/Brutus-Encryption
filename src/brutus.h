#ifndef BRUTUS_H
#define BRUTUS_H

#include <iostream>

namespace Brutus
{
	std::string text(std::string text, std::string key);
	std::string file(std::string inputPath, std::string key);
	std::string file(std::string inputPath, std::string key, std::string outputPath);
}

#endif // BRUTUS_H
