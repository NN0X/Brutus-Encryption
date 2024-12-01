#include "../src/brutus.h"

#include <iostream>

int main()
{
	int a = Brutus::Internal::encryptCharacter('a', 0, 0);
	std::cout << a << std::endl;
	return 0;
}
