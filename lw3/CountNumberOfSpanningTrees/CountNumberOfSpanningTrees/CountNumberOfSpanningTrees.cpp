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
vector<vector <float>> GetKirchhoffMatrix(vector<vector <int>> adjacencyMatrix);
vector<vector <float>> GetMatrixForAlgebraicAddition(const vector<vector <float>>& matrix);
void BringingMatrixToTriangularForm(vector<vector <float>>& matrix);
int GetDeterminant(const vector<vector <float>>& matrix);
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
	
	cout << "Print input matrix\n";
	PrintMatrix(inputMatrix);

	cout << "Print Kirchhoff matrix\n";
	PrintMatrix(kirchhoffMatrix);

	auto algebraicAdditionalMatrix = GetMatrixForAlgebraicAddition(kirchhoffMatrix);
	BringingMatrixToTriangularForm(algebraicAdditionalMatrix);
	int numOfSpanningTrees = GetDeterminant(algebraicAdditionalMatrix);
	cout << "Number of spanning trees = " << numOfSpanningTrees << "\n";

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

vector<vector <float>> GetMatrixForAlgebraicAddition(const vector<vector <float>>& matrix)
{
	vector<vector <float>> resultMatrix(matrix.size() - 1, vector<float>(matrix.size() -1, 0));
	for (int i = 0; i < matrix.size() - 1; i++)
	{
		for (int j = 0; j < matrix.size() - 1; j++)
			resultMatrix[i][j] = matrix[i][j];
	}
	return resultMatrix;
}

void BringingMatrixToTriangularForm(vector<vector <float>>& matrix)
{
	for (int col = 0; col < matrix.size() - 1; col++)
	{
		for (int row = col + 1; row < matrix.size(); row++)
		{
			if (matrix[col][col] != 0)
			{
				float k = matrix[row][col] / matrix[col][col];
				for (int i = 0; i < matrix.size(); i++)
				{
					matrix[row][i] = round((matrix[row][i] - k * matrix[col][i]) * 100) / 100;
				}
			}
		}
	}
}

int GetDeterminant(const vector<vector <float>>& matrix)
{
	float determinant = 1;
	for (int i = 0; i < matrix.size(); i++)
	{
		determinant *= matrix[i][i];
	}
	return determinant;
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