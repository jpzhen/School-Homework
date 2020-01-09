// ------------------------------------------------ graphl.cpp -------------------------------------------------------
// Jun Zhen CSS343 Section A
// Creation Date: 7/29/19
// Date of Last Modification: 7/29/19
// --------------------------------------------------------------------------------------------------------------------
// Description - Detail implementation for graphl.cpp
// -------------------------------------------------------------------------------------------------------------------- 



#include "graphl.h"
// --------------------------GraphL------------------------------
// Description: Default constructor for Adjacent List based graph
// Precondition: none
// Postcondition: none
// -----------------------------------------------------------------------
GraphL::GraphL()
{
	size = 0;
	for (int i = 0; i < MAXNODES_L; i++)
	{
		adjList[i].visited = false;
		adjList[i].edgeHead = NULL;
	}
}

// --------------------------GraphL------------------------------
// Description: Destructor to free up all memories
// Precondition: none
// Postcondition: All memories are freed
// -----------------------------------------------------------------------
GraphL::~GraphL() {
	removeEdges();
}

// --------------------------buildGraph------------------------------
// Description: Read and create a graph from the file
// Precondition: none
// Postcondition: none
// -----------------------------------------------------------------------
void GraphL::buildGraph(ifstream& input)
{
	int fromNode = 0;
	int toNode = 0;
	input >> size;
	string s;
	getline(input, s);
	if (size > 0)
	{
		for (int i = 1; i <= size; i++)
		{
			getline(input, s);
			adjList[i].data = new NodeData(s);
		}
		while (!input.eof())
		{
			input >> fromNode >> toNode;
			if (fromNode == 0 || toNode == 0)
			{
				break;
			}
			insertEdge(fromNode, toNode);
		}
	}
}

// --------------------------insertEdge------------------------------
// Description: buildGraph Helper that insert new node into the linkedlist chain
// Precondition: none
// Postcondition: none
// -----------------------------------------------------------------------
void GraphL::insertEdge(const int fromNode, const int toNode) {
	if (fromNode > 0 && fromNode <= size && toNode > 0 && toNode <= size) {
		EdgeNode* node = new EdgeNode;
		node->adjGraphNode = toNode;
		node->nextEdge = adjList[fromNode].edgeHead;
		adjList[fromNode].edgeHead = node;
	}
}

// --------------------------removeEdge------------------------------
// Description:  Helper function that remove all nodes from all lists
// Precondition: Graph must contain elements/values
// Postcondition: All allocated memories are cleared
// -----------------------------------------------------------------------
void GraphL::removeEdges() {
	for (int i = 0; i <= size; i++)
	{
		adjList[i].visited = false;
		EdgeNode* deallocThis = adjList[i].edgeHead;
		while (deallocThis != NULL) {
			EdgeNode* saveNext = deallocThis->nextEdge;
			delete deallocThis;
			deallocThis = saveNext;
		}
		adjList[i].edgeHead = NULL;
	}
	size = 0;
}

// --------------------------displayGraph------------------------------
// Description: Display all the nodes and where they are connected
// Precondition: none
// Postcondition: none
// -----------------------------------------------------------------------
void GraphL::displayGraph()
{
	cout << "Graph:" << endl;
	for (int i = 1; i <= size; i++)
	{
		cout << "Node" << i << "                         "; cout << *adjList[i].data << endl;
		cout << endl;

		if (adjList[i].edgeHead == NULL)
		{
			cout << endl;
		}
		else
		{
			EdgeNode* current = adjList[i].edgeHead;
			while (current != NULL)
			{
				cout << "     " << "edge" << "        " << i << "        " << current->adjGraphNode << endl;
				current = current->nextEdge;
			}
		}
	}
}


// --------------------------dephtFirstSearch------------------------------
// Description: Algorithm to traversal all through the nodes and edges 
// Precondition: Adjacnet list must not be empty
// Postcondition: none
// -----------------------------------------------------------------------
void GraphL::depthFirstSearch()
{
	if (size != 0) 
	{
		cout << "Depth First Search: ";
		for (int i = 1; i <= size; i++)
		{
			if (!adjList[i].visited)
			{
				dfsHelper(i);
			}
		}
	}
	cout << endl;
}
// --------------------------dfsHelper------------------------------
// Description: Helper function for dfs 
// Precondition: must be only called by the depthFirstSearch function with given index
// Postcondition: none
// -----------------------------------------------------------------------
void GraphL::dfsHelper(const int index)
{
	cout << " " << index;
	adjList[index].visited = true;
	int n = 0;
	EdgeNode* current = adjList[index].edgeHead;
	while (current != NULL) 
	{
		n = current->adjGraphNode;
		if (!adjList[n].visited)
		{
			dfsHelper(n);
		}
		current = current->nextEdge;
	}
}