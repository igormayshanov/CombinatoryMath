#include "ParseArgs.h"

std::optional<std::string> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		return std::nullopt;
	}
	std::string inputFileName = argv[1];
	return inputFileName;
}
