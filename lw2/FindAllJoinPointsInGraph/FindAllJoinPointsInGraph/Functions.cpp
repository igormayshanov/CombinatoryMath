#include "Functions.h"
#include "OpenFile.h"
#include "ParseArgs.h"

using namespace std;

std::vector<std::vector<int>> FillAdjacencyMatrix(std::ifstream& inputFile)
{
	int numOfVertices;
	int numOfEdges;
	inputFile >> numOfVertices >> numOfEdges;
	std::vector<std::vector<int>> adjacencyMatrix(numOfVertices + 1, vector<int>(numOfVertices + 1, 0));
	int vertex1, vertex2;
	while (inputFile >> vertex1 >> vertex2)
	{
		adjacencyMatrix[vertex1][vertex2] = 1;
		adjacencyMatrix[vertex2][vertex1] = 1;
	}
	return adjacencyMatrix;
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

void FindJoinPointsInGraph(std::vector<std::vector<int>> const& adjacencyMatrix,
	std::vector<int> const& timeIn,
	std::vector<int> const& timeOut,
	std::vector<Edge> const& backEdge,
	std::vector<int> const& children,
	int root,
	std::set<int>& joinPoints)
{
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
}

void printMatrix(std::vector<std::vector<int>> const& vec)
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

void PrintSet(std::set<int> const& inputSet)
{
	for (auto& i : inputSet)
	{
		cout << i << " ";
	}
	cout << "\n";
}