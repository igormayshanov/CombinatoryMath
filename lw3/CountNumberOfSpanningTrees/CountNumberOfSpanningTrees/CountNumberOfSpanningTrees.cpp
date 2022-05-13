#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

const int MAX_MATRIX_SIZE = 100;
//
//typedef float Matrix3x3[MATRIX_SIZE][MATRIX_SIZE];
//
//struct WrappedMatrix3x3
//{
//	Matrix3x3 items;
//};

struct Args
{
	std::string inputFileName1;
};

std::optional<Args> ParseArgs(int argc, char* argv[]);
std::optional<std::ifstream> OpenFile(std::string fileName);
std::vector<std::vector<int>> GetAdjacencyMatrix(std::ifstream& inputFile);
vector<vector <float>> GetKirchhoffMatrix(vector<vector <int>> adjacencyMatrix);
int GetNumberOfSpanningTrees(vector<vector <float>>& matrix);
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
	auto kirchhoffMatrix = GetKirchhoffMatrix(inputMatrix);

	PrintMatrix(inputMatrix);
	PrintMatrix(kirchhoffMatrix);
	vector<vector<float>> test = {
		{1, 2, 3, 4},
		{2, 3, 2, 3},
		{1, 4, 1, 2},
		{4, 5, 0, 1},
	};

	int numOfSpanningTrees = GetNumberOfSpanningTrees(kirchhoffMatrix);

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
	inputFile >> numOfVertices;
	cout << numOfVertices << "\n";
	std::vector<std::vector<int>> adjacencyMatrix(numOfVertices, vector<int>(numOfVertices, 0));
	for (int i = 0; i < numOfVertices; i++)
	{
		for (int j = 0; j < numOfVertices; j++)
		{
			inputFile >> adjacencyMatrix[i][j];
		}
	}
	return adjacencyMatrix;
}
vector<vector <float>> GetKirchhoffMatrix(vector<vector <int>> adjacencyMatrix)
{
	vector<vector<float>> kirchhoffMatrix(adjacencyMatrix.size(), vector<float>(adjacencyMatrix.size(), 0));
	int adjacent = 1;
	for (int i = 0; i < adjacencyMatrix.size(); i++)
	{
		for (int j = 0; j < adjacencyMatrix.size(); j++)
		{
			if (adjacencyMatrix[i][j] == adjacent)
			{
				kirchhoffMatrix[i][j] = -1;
				++kirchhoffMatrix[i][i];
			}
		}
	}
	return kirchhoffMatrix;
}

int GetNumberOfSpanningTrees(vector<vector <float>>& matrix)
{
	for (int col = 0; col < matrix.size()-1; col++)
	{
		for (int row = col+1; row < matrix.size(); row++)
		{
			if (matrix[col][col] != 0)
			{
				float k = matrix[row][col] / matrix[col][col];
				cout << "column = " << col << ", row = " << row << ", koef = " << k << "\n";
				for (int i = 0; i < matrix.size(); i++)
				{
					matrix[row][i] = floor((matrix[row][i] - k * matrix[col][i])*100)/100;
					cout << row << ", " << i << ", " << matrix[row][i] 
						<< ", " << k * matrix[col][i] << "\n";
				}
			}
		}
	}
	PrintMatrix(matrix);
	return 0;
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