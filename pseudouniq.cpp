#include <iostream>
#include <cmath>
#include <vector>

#define E 2.71828182845904523536

double influence(double x, double max, double nearZ)
{
	return -max * (1 - pow(E, -8 * x / nearZ)) + max;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		return 1;
	}
	std::string text = argv[1];
	std::vector<long long int> elements(text.size());

	long long int num = 0;

	for (size_t i = 0; i < text.size(); i++)
	{
		size_t j = i + 10;
		elements[i] = text[i] * ((long long int)(pow(E, j) * sin(j + j * E) * cos(j + (j + 10) * E) * influence(j, pow(E, 10), text.size()) + pow(E, E / j) * sin(j + j * E) * cos(j + (j + 5) * E)));
		num += elements[i];
	}

	std::cout << (unsigned long long int)num << " ";
	for (size_t i = 0; i < elements.size(); i++)
	{
		std::cout << elements[i] << " ";
	}

	return 0;
}
