// ------------------------------------------------ graphl.h -------------------------------------------------------
// Jun Zhen CSS343 Section A
// Creation Date: 7/29/19
// Date of Last Modification: 7/29/19
// --------------------------------------------------------------------------------------------------------------------
// Description - Header files for graphL.h
// -------------------------------------------------------------------------------------------------------------------- 

#ifndef _GRAPHL_H_
#define _GRAPHL_H_
#include "nodedata.h"
#include <iostream>
#include "iomanip"
using namespace std;

//Max values for edges and vertices
int const MAXNODES_L = 100;

class GraphL {
public:
	//Constructor and Destructor
	GraphL();
	~GraphL();

	//Main Functions
	void buildGraph(ifstream&);
	void insertEdge(const int src, const int dest);
	void removeEdges();
	void displayGraph();
	void dfsHelper(const int searchNode);

	//Helper function
	void depthFirstSearch();

private:
	//Data fields
	struct EdgeNode;
	struct GraphNode {
		EdgeNode* edgeHead;
		NodeData* data;
		bool visited;
	};
	struct EdgeNode {
		int adjGraphNode;
		EdgeNode* nextEdge;
	};
	GraphNode adjList[MAXNODES_L];
	int size;

};

#endif