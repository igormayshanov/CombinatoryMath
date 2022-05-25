#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "functions.h"

using namespace std;

std::vector<std::vector<int>> GetZeroEdges(const std::vector<std::vector<int>>& matrix);
bool DFS(int v, std::vector<std::vector<int>> zeroEdges,
	std::vector<char>& used, std::vector<int>& matchings);


int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: <exe file name> <input file name>\n";
		return 1;
	}
	auto inputFile1 = OpenFile(args->inputFileName1);
	if (!inputFile1)
	{
		std::cout << "Failed to open '" << args->inputFileName1 << "' for reading\n";
		return 1;
	}
	int p;
	int q;
	*inputFile1 >> p >> q;
	auto inputMatrix = GetAdjacencyMatrix(*inputFile1, p, q);

	cout << "Print input matrix\n";
	PrintMatrix(inputMatrix);
	auto matrix = TransformMatrix(inputMatrix);
	cout << "Print transform matrix\n";
	PrintMatrix(matrix);

	auto zeroEdges = GetZeroEdges(matrix);

	PrintMatrix(zeroEdges);

	std::vector<int> matchings(matrix.size(), -1);
	std::vector<char> used;

	for (int v = 0; v < zeroEdges.size(); ++v) {
		used.assign(zeroEdges.size(), false);
		DFS(v, zeroEdges, used, matchings);
	}
	bool isMaxMatching = true;
	
	for (int i = 0; i < matchings.size(); ++i)
	{
		if (matchings[i] == -1)
		{
			isMaxMatching = false;
		}
	}

	if (isMaxMatching)
	{
		cout << "Yes\n";
	}
	else
	{
		cout << "No\n";
		PrintMatchings(matchings);
	}
	return 0;
}