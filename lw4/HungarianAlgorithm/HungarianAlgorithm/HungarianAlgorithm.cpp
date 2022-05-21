#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

const int MAX_MATRIX_SIZE = 100;

struct Args
{
	std::string inputFileName1;
};

std::optional<Args> ParseArgs(int argc, char* argv[]);
std::optional<std::ifstream> OpenFile(std::string fileName);
std::vector<std::vector<int>> GetAdjacencyMatrix(std::ifstream& inputFile);
std::vector<std::vector<int>> TransformMatrix(std::vector<std::vector<int>>& inputMatrix);
std::vector<int> CheckPair(const std::vector<std::vector<int>>& matrix);
void PrintMatrix(const vector<vector<int>>& matrix);
void PrintMatrix(const vector<vector<float>>& matrix);

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: CountNumberOfSpanningTrees.exe <input file name>\n";
		return 1;
	}
	auto inputFile1 = OpenFile(args->inputFileName1);
	if (!inputFile1)
	{
		std::cout << "Failed to open '" << args->inputFileName1 << "' for reading\n";
		return 1;
	}

	auto inputMatrix = GetAdjacencyMatrix(*inputFile1);

	cout << "Print input matrix\n";
	PrintMatrix(inputMatrix);
	auto matrix = TransformMatrix(inputMatrix);
	cout << "Print output matrix\n";
	PrintMatrix(matrix);

	auto pair = CheckPair(matrix);

	copy(pair.begin(), pair.end(), ostream_iterator<int>(cout, " "));

	return 0;
}

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

std::vector<std::vector<int>> GetAdjacencyMatrix(std::ifstream& inputFile)
{
	int numOfVertices;
	int tempNum;
	inputFile >> numOfVertices;
	std::vector<std::vector<int>> adjacencyMatrix(numOfVertices, vector<int>(numOfVertices, 0));
	for (int i = 0; i < numOfVertices; i++)
	{
		for (int j = 0; j < numOfVertices; j++)
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
		for (int row = 0; row < matrix.size(); row++)
		{
			min = matrix[row][col] < min ? matrix[row][col] : min;
		}

		if (min == 0) continue;

		for (int row = 0; row < matrix.size(); row++)
		{
			matrix[row][col] == INT_MAX ? matrix[row][col] = INT_MAX : matrix[row][col] -= min;
		}
	}
	return matrix;
}

std::vector<int> CheckPair(const std::vector<std::vector<int>>& matrix)
{
	int existRowPos = 0;
	int existColumnPos = 0;
	bool exist = false;
	std::vector<int> work(matrix.size(), -1);
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.size(); j++)
		{
			if (matrix[i][j] == 0)
			{
				for (int k = 0; k < work.size(); k++)
				{
					if (work[k] == j)
					{
						existRowPos = k;
						existColumnPos = j;
						exist = true;
						break;
					}
				}
				if (!exist)
				{
					work[i] = j;
				}
				exist = false;
			}
			continue;
		}
	}
	cout << "conflict pos = " << existRowPos << ", " << existColumnPos << "\n";
	return work;
}



void PrintMatrix(const vector<vector<int>>& matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.size(); j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void PrintMatrix(const vector<vector<float>>& matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.size(); j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}