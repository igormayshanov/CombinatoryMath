/* 1. Если у вершины несколько ребер и одно из них мост, то эта вершина - точка сочленения
	2. Корневая вершина является точкой сочленения только в случае, когда у нее более одного сына в дереве обхода в глубину
	3. Если у вершины один сын в DFS, то она не явл. точкой сочленения, если имеется обратное ребро от потомка к предку это вершины
*/


#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <stack>
#include <set>

#include "OpenFile.h"
#include "ParseArgs.h"

using namespace std;

struct Edge
{
	int v;
	int to;
};

std::vector<std::vector<int>> FillAdjacencyMatrix(std::ifstream& inputFile);
void printMatrix(std::vector<std::vector<int>> vec);

void DFS(int root, 
	std::vector<std::vector<int>> const& adjacencyMatrix, 
	std::vector<int>& timeIn, 
	std::vector<int>& timeOut, 
	std::vector<Edge>& backEdge, 
	std::vector<int>& children);
int main(int argc, char *argv[])
{
	auto inputFileName = ParseArgs(argc, argv);
	if (!inputFileName)
	{
		cout << "Invalid argument count\n";
		cout << "Usage: <Exe fileName> <inputFileName>\n";
		return 1;
	}
	auto inputFile = OpenFile(*inputFileName);
	if (!inputFile)
	{
		cout << "Filed to open '" << *inputFileName << "' for reading\n";
		return 1;
	}
	std::vector<std::vector<int>> adjacencyMatrix = FillAdjacencyMatrix(*inputFile);
	printMatrix(adjacencyMatrix);

	vector<int> timeIn(adjacencyMatrix[0].size(), 0);
	vector<int> timeOut(adjacencyMatrix[0].size(), 0);
	vector<int> children(adjacencyMatrix[0].size(), 0);
	set<int> joinPoints; 

	vector<Edge> backEdge;
	int root = 1;
	DFS(root, adjacencyMatrix, timeIn, timeOut, backEdge, children);

	for (int vertex = 1; vertex < adjacencyMatrix[0].size(); ++vertex)
	{
		bool isBridge = false;
		bool isNotBridge = false;
		for (int j = 1; j < adjacencyMatrix[0].size(); ++j)
		{
			if (adjacencyMatrix[vertex][j] && timeIn[j] > timeIn[vertex] 
				&& timeOut[j] < timeOut[vertex])
			{
				for (auto& i : backEdge)
				{
					if ((timeIn[i.v] >= timeIn[j] &&
						timeOut[i.v] <= timeOut[j]) &&
						(timeIn[i.to] < timeIn[vertex] &&
							timeOut[i.to] > timeOut[vertex]))
					{
						isNotBridge = true;
					}
					else
					{
						isBridge = true;
					}
				}
				switch (children[vertex])
				{
				case 0:
					continue;
					break;
				case 1:
					if (!isNotBridge && isBridge && vertex != root)
						joinPoints.insert(vertex);
					break;
				default:
					if (isBridge)
						joinPoints.insert(vertex);
					break;
				}
			}
		}
		if (vertex == root && children[vertex] <= 1)
			continue;		
	}
	cout << "\nPrint children: " << "\n";
	copy(children.begin(), children.end(), ostream_iterator<int>(cout, " "));
	cout << "\n";
	copy(timeIn.begin(), timeIn.end(), ostream_iterator<int>(cout, " "));
	cout << "\n";
	copy(timeOut.begin(), timeOut.end(), ostream_iterator<int>(cout, " "));
	cout << "\n Print back edges\n";
	for (auto& i : backEdge)
	{
		cout << i.v << ", " << i.to << "\n";
	}

	cout << "Print join points\n";
	for (auto& i : joinPoints)
	{
		cout << i << " ";
	}
	cout << "\n";
}

void DFS(int root, 
	std::vector<std::vector<int>> const& adjacencyMatrix, 
	std::vector<int>& timeIn, 
	std::vector<int>& timeOut, 
	std::vector<Edge>& backEdge,
	std::vector<int>& children)
{
	vector<bool> visited(adjacencyMatrix[0].size(), 0);
	int timer = 0;
	int vertex;
	int parent = 0;
	stack<int> stack;
	stack.push(root);
	visited[root] = true;
	bool isVertexHasEdge = true;
	while (!stack.empty())
	{
		vertex = stack.top();
		visited[vertex] = true;
		if (isVertexHasEdge)
		{
			timeIn[vertex] = ++timer;
		}
		for (int i = 1; i < adjacencyMatrix[0].size(); ++i)
		{
			if (adjacencyMatrix[vertex][i])
			{
				if (!visited[i])
				{
					children[vertex] += 1;
					parent = stack.top();
					stack.push(i);
					isVertexHasEdge = true;
					break;
				}
				if (visited[i] && timeIn[vertex] - timeIn[i] > 1 && i != parent && !timeOut[parent])
				{
					Edge edge;
					edge.v = vertex;
					edge.to = i;
					backEdge.push_back(edge);
				}
			}
			isVertexHasEdge = false;
		}
		if (!isVertexHasEdge)
		{
			parent = stack.top();
			timeOut[vertex] = ++timer;
			stack.pop();
		}
	}
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