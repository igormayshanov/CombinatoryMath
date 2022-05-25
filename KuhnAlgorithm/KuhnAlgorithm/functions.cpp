#include "functions.h"

using namespace std;

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		return std::nullopt;
	}
	Args args;
	args.inputFileName1 = argv[1];
	return args;
}

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

std::vector<std::vector<int>> GetAdjacencyMatrix(std::ifstream& inputFile, int p, int q)
{
	int tempNum;
	std::vector<std::vector<int>> adjacencyMatrix(p, vector<int>(q, 0));
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			inputFile >> tempNum;
			tempNum != 0 ? adjacencyMatrix[i][j] = tempNum : adjacencyMatrix[i][j] = INT_MAX;
		}
	}
	return adjacencyMatrix;
}

std::vector<std::vector<int>> TransformMatrix(std::vector<std::vector<int>>& inputMatrix)
{
	std::vector<std::vector<int>> matrix = inputMatrix;
	int min = INT_MAX;
	for (auto& row : matrix)
	{
		min = *std::min_element(row.begin(), row.end());
		for (auto& i : row)
		{
			i == INT_MAX ? i = INT_MAX : i -= min;
		}
	}
	for (int col = 0; col < matrix.size(); col++)
	{
		min = INT_MAX;
		for (int row = 0; row < matrix[col].size(); row++)
		{
			min = matrix[row][col] < min ? matrix[row][col] : min;
		}

		if (min == 0) continue;

		for (int row = 0; row < matrix[col].size(); row++)
		{
			matrix[row][col] == INT_MAX ? matrix[row][col] = INT_MAX : matrix[row][col] -= min;
		}
	}
	return matrix;
}

std::vector<std::vector<int>> GetZeroEdges(const std::vector<std::vector<int>>& matrix)
{
	std::vector<std::vector<int>> zeroEdges(matrix.size());
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.size(); j++)
		{
			if (matrix[i][j] == 0)
			{
				zeroEdges[i].push_back(j);
			}
		}
	}
	return zeroEdges;
}

bool DFS(int v, std::vector<std::vector<int>> zeroEdges,
	std::vector<char>& used, std::vector<int>& matchings)
{
	if (used[v])
		return false;
	used[v] = true;
	for (int i = 0; i < zeroEdges[v].size(); ++i)
	{
		int to = zeroEdges[v][i];
		if (matchings[to] == -1 || DFS(matchings[to], zeroEdges, used, matchings))
		{
			matchings[to] = v;
			return true;
		}
	}
	return false;
}


void PrintMatrix(const vector<vector<int>>& matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void PrintMatchings(const std::vector<int> vector)
{
	for (int i = 0; i < vector.size(); ++i)
	{
		std::cout << vector[i] + 1 << " - " << i + 1 << "\n";
	}
}


int GetMinElemAboveZeroInVector(const std::vector<int>& vector)
{
	int min = INT_MAX;
	for (auto& i : vector)
	{
		if (i != 0)
			min = min < i ? min : i;
	}
	return min;
}

void SubtractionMinElem(std::vector<int>& vector, int min)
{
	for (auto& i : vector)
	{
		if (i != 0)
		{
			i == INT_MAX ? i = INT_MAX : i -= min;
		}
	}
}