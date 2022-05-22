#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

const int MAX_MATRIX_SIZE = 100;

struct Args
{
	std::string inputFileName1;
};

std::optional<Args> ParseArgs(int argc, char* argv[]);
std::optional<std::ifstream> OpenFile(std::string fileName);
std::vector<std::vector<int>> GetAdjacencyMatrix(std::ifstream& inputFile, int p, int q);
std::vector<std::vector<int>> TransformMatrix(std::vector<std::vector<int>>& inputMatrix);
std::vector<std::vector<int>> GetZeroEdges(const std::vector<std::vector<int>>& matrix);
bool DFS(int v, std::vector<std::vector<int>> zeroEdges,
	std::vector<char>& used, std::vector<int>& matchings);
void PrintMatrix(const std::vector<std::vector<int>>& matrix);
void PrintMatchings(const std::vector<int> vector);
int GetMinElemAboveZeroInVector(const std::vector<int>& vector);
void SubtractionMinElem(std::vector<int>& vector, int min);

