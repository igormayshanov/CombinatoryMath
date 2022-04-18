#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <stack>
#include <set>

struct Edge
{
	int v;
	int to;
};

std::vector<std::vector<int>> FillAdjacencyMatrix(std::ifstream& inputFile);

void DFS(int root,
	std::vector<std::vector<int>> const& adjacencyMatrix,
	std::vector<int>& timeIn,
	std::vector<int>& timeOut,
	std::vector<Edge>& backEdge,
	std::vector<int>& children);

void FindJoinPointsInGraph(std::vector<std::vector<int>> const& adjacencyMatrix, 
	std::vector<int> const& timeIn,
	std::vector<int> const& timeOut,
	std::vector<Edge> const& backEdge,
	std::vector<int> const& children,
	int root, 
	std::set<int>& joinPoints);

void printMatrix(std::vector<std::vector<int>> vec);
