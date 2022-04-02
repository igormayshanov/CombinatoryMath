#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <stack>

#include "OpenFile.h"
#include "ParseArgs.h"

using namespace std;

struct Node
{
	int value; 
	bool visited = false;
};

std::vector<std::vector<int>> FillAdjacencyMatrix(std::ifstream& inputFile);
void printMatrix(std::vector<std::vector<int>> vec);

int main(int argc, char *argv[])
{
	auto inputFileName = ParseArgs(argc, argv);
	if (!inputFileName)
	{
		cout << "Invalid argument count\n";
		cout << "Usage: ObsceneWordsFilter.exe <inputFileName>\n";
		return 1;
	}
	auto inputFile = OpenFile(*inputFileName);
	if (!inputFile)
	{
		cout << "Filed to open '" << *inputFileName << "' for reading\n";
		return 1;
	}
	int numOfVertices;
	int numOfEdges;
	std::vector<std::vector<int>> adjacencyMatrix = FillAdjacencyMatrix(*inputFile);
	printMatrix(adjacencyMatrix);

	//----------------------------------------------
	vector<bool> visited(adjacencyMatrix[0].size(), 0);
	vector<int> timeIn(adjacencyMatrix[0].size(), 0);
	vector<int> timeOut(adjacencyMatrix[0].size(), 0);
	int timer = 0;

	int vertex;
	int root = 1;
	stack<int> stack;
	stack.push(root);
	visited[root] = true;
	timeIn[root] = ++timer;
	bool isHasEdge;
	while (!stack.empty())
	{
		isHasEdge = false;
		vertex = stack.top();
		cout << vertex << " ";
		for (int i = 1; i < adjacencyMatrix[0].size(); ++i)
		{
			if (adjacencyMatrix[vertex][i] == 1 && !visited[i])
			{
				stack.push(i);
				timeIn[i] = ++timer;
				visited[i] = true;
				isHasEdge = true;
			}
		}
		if (!isHasEdge)
		{
			stack.pop();
			timeOut[vertex] = ++timer;
		}
	}
	cout << "\n";
	copy(timeIn.begin(), timeIn.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	copy(timeOut.begin(), timeOut.end(), ostream_iterator<int>(cout, " "));
}

std::vector<std::vector<int>> FillAdjacencyMatrix(std::ifstream& inputFile)
{
	int numOfVertices;
	int numOfEdges;
	inputFile >> numOfVertices >> numOfEdges;
	std::vector<std::vector<int>> adjacencyMatrix(numOfVertices+1, vector<int>(numOfVertices + 1, 0));
	std::string stringFromFile;
	int vertex1, vertex2;
	while (inputFile >> vertex1 >> vertex2)
	{
		adjacencyMatrix[vertex1][vertex2] = 1;
		adjacencyMatrix[vertex2][vertex1] = 1;
	}
	return adjacencyMatrix;
}

void DFS()
{
}

void printMatrix(std::vector<std::vector<int>> vec)
{
	for (auto& i : vec)
	{
		for (auto& j : i)
		{
			std::cout << j << " ";
		}
		std::cout << "\n";
	}
}