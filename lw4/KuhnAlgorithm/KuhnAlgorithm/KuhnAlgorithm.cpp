#include "functions.h"

using namespace std;

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

	auto edges = GetEdges(inputMatrix);

	PrintMatrix(edges);

	std::vector<int> matchings(p, -1);
	std::vector<char> used;

	for (int v = 0; v < edges.size(); ++v) {
		used.assign(edges.size(), false);
		DFS(v, edges, used, matchings);
	}
	bool isMaxMatching = true;

	for (int i = 0; i < matchings.size(); ++i)
	{
		if (matchings[i] == -1)
		{
			isMaxMatching = false;
		}
	}

	isMaxMatching ? cout << "Yes\n" : cout << "No\n";
	PrintMatchings(matchings);

	return 0;
}