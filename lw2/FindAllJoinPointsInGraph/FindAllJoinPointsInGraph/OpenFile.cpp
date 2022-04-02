#include "OpenFile.h"
#include <fstream>

std::optional<std::ifstream> OpenFile(std::string fileName)
{
	std::ifstream input;
	input.open(fileName);
	if (!input.is_open())
	{
		return std::nullopt;
	}
	else
	{
		return input;
	}
}