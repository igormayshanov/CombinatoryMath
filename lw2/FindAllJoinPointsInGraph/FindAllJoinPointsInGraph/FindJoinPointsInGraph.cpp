/* 1. Если у вершины несколько ребер и одно из них мост, то эта вершина - точка сочленения
	2. Корневая вершина является точкой сочленения только в случае, когда у нее более одного сына в дереве обхода в глубину
	3. Если у вершины один сын в DFS, то она не явл. точкой сочленения, если имеется обратное ребро от потомка к предку это вершины
*/

#include "OpenFile.h"
#include "ParseArgs.h"
#include "Functions.h"

using namespace std;

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

	vector<int> timeIn(adjacencyMatrix[0].size(), 0);
	vector<int> timeOut(adjacencyMatrix[0].size(), 0);
	vector<int> children(adjacencyMatrix[0].size(), 0);
	set<int> joinPoints; 

	vector<Edge> backEdge;
	int root = 1;
	DFS(root, adjacencyMatrix, timeIn, timeOut, backEdge, children);
	FindJoinPointsInGraph(adjacencyMatrix, timeIn, timeOut, backEdge, children, root, joinPoints);
	
	for (auto& i : joinPoints)
	{
		cout << i << " ";
	}
	cout << "\n";
}