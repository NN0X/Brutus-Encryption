#include <iostream>
#include <climits>

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		return 1;
	}

	unsigned long long int x = std::stoull(argv[1]);
	unsigned long long int y = std::stoull(argv[2]);

	std::cout << x + y;
	return 0;
}
