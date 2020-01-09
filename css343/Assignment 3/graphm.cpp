// ------------------------------------------------ graphm.cpp -------------------------------------------------------
// Jun Zhen CSS343 Section A
// Creation Date: 7/29/19
// Date of Last Modification: 7/29/19
// --------------------------------------------------------------------------------------------------------------------
// Description - Detail implementation for graphM.cpp
// -------------------------------------------------------------------------------------------------------------------- 


#include "graphm.h"
// --------------------------GraphM------------------------------
// Description: Default constructor for Adjacent Matrix based graph
// Precondition: none
// Postcondition: all value set to false and max value
// -----------------------------------------------------------------------
GraphM::GraphM() {
	size = 0;
	for (int i = 1; i < MAXNODES; i++)
	{
		for (int j = 1; j < MAXNODES; j++)
		{
			C[i][j] = MAX;
			T[i][j].dist = MAX;
			T[i][j].path = 0;
			T[i][j].visited = false;
		}
	}
}
// --------------------------buildGraph------------------------------
// Description: Read and create a graph from the file
// Precondition: none
// Postcondition: none
// -----------------------------------------------------------------------
void GraphM::buildGraph(ifstream& file)
{
	file >> size;
	string s;
	getline(file, s);
	for (int i = 1; i <= size; i++)
	{
		data[i].setData(file);
	}
	int fromNode, toNode, dist;
	while (file >> fromNode >> toNode >> dist)
	{
		if (fromNode == 0)
		{
			break;
		}
		C[fromNode][toNode] = dist;
	}
}



// --------------------------insertEdge------------------------------
// Description: Connect two vertex together
// Precondition: Our graph must contain those vertices
// Postcondition: The edge value is no longer max int
// -----------------------------------------------------------------------
bool GraphM::insertEdge(int fromNode, int toNode, int dist)
{
	if (fromNode <= size && toNode <= size)
	{
		this->T[fromNode][toNode].dist = dist;
		return true;
	}
	else
	{
		return false;
	}
}

// --------------------------removeEdge------------------------------
// Description: Remove the edge from two vertices
// Precondition: Our graph must contain those vertices
// Postcondition: The edge value between the two vertices are now max int
// -----------------------------------------------------------------------
bool GraphM::removeEdge(int fromNode, int toNode)
{
	if (fromNode <= size && toNode <= size)
	{
		this->T[fromNode][toNode].dist = MAX;
		return true;
	}
	else
	{
		return false;
	}
}

// --------------------------findShortestPath------------------------------
// Description: Using Dijkstra's algorithm to find the shortest path
// Precondition: Vertices must exist
// Postcondition: none
// -----------------------------------------------------------------------
void GraphM::findShortestPath()
{
	int v = 0;
	int cNode = 0;
	for (int source = 1; source <= size; source++)
	{
		T[source][source].dist = 0;
		for (int i = 1; i <= size; i++)
		{
			v = minDistance(source);
			T[source][v].visited = true;
			for (int w = 1; w <= size; w++)
				if (T[source][w].visited == false && C[v][w] != MAX && T[source][v].dist + C[v][w] < T[source][w].dist)
				{
					T[source][w].dist = T[source][v].dist + C[v][w];
					T[source][w].path = v;
				}
		}
	}
}

// --------------------------minDistance------------------------------
// Description: Shortest Path helper
// Precondition: none
// Postcondition: none
// -----------------------------------------------------------------------
int GraphM::minDistance(int source)
{
	int v = 0;
	int min = MAX;
	for (int i = 1; i <= size; i++)
		if (T[source][i].visited == false && T[source][i].dist <= min)
		{
			min = T[source][i].dist;
			v = i;
		}
	return v;
}

// --------------------------displayAll------------------------------
// Description: Display all the shortest distance from all nodes and the path
// Precondition: none
// Postcondition: none
// -------------------------------------------------------------------
void GraphM::displayAll() const
{
	cout << "|Description           |From Node   |To Node   |Dijikstra's" << "      |Path" << endl;
	for (int i = 1; i < size + 1; i++)
	{
		cout << data[i] << endl;
		for (int j = 1; j < size + 1; j++)
		{
			if (T[i][j].dist > 0 && T[i][j].dist < MAX)
			{
				cout << "                            " << i << "           " << j << "           " << T[i][j].dist << "             "; 
				getPath(i, j);
				cout << endl;
			}
			else 
			{
				cout << "                            " << i << "           " << j << "           " << "---" << endl;
			}
		}
	}
	cout << endl;
}
// --------------------------display------------------------------
// Description: Display the shortest distance between two given position
// Precondition: Vertices must exist 
// Postcondition: none
// -------------------------------------------------------------------
void GraphM::display(const int fromNode, const int toNode) const
{
	if (T[fromNode][toNode].dist != MAX)
	{
		cout << "   " << fromNode << "    " << toNode << "    ";
		cout << T[fromNode][toNode].dist << "        ";
		getPath(fromNode, toNode);
	}
	else
	{
		cout << "   " << fromNode << "    " << toNode << "    ---";
	}
	getPathName(fromNode, toNode);
	cout << endl;
}

// --------------------------getPath------------------------------
// Description: Get the path that it takes to travel the shortest distance
// Precondition: none
// Postcondition: none
// -----------------------------------------------------------------------
void GraphM::getPath(const int fromNode, const int toNode) const
{
	if (fromNode != toNode && T[fromNode][toNode].path != 0)
	{
		getPath(fromNode, T[fromNode][toNode].path);
	}
	cout << toNode << " ";
}

// --------------------------getPathName------------------------------
// Description: Similiar to getPath, but print out the list of the path
// Precondition: none
// Postcondition: none
// -----------------------------------------------------------------------
void GraphM::getPathName(const int fromNode, const int toNode) const
{
	if (T[fromNode][toNode].dist != MAX)
	{
		getPathNameHelper(fromNode, toNode);
		cout << data[toNode] << endl;
	}
}
void GraphM::getPathNameHelper(const int fromNode, const int toNode) const
{
	if (fromNode != toNode && T[fromNode][toNode].path != 0)
	{
		getPathNameHelper(fromNode, T[fromNode][toNode].path);
	}
	cout << data[T[fromNode][toNode].path] << endl;
}