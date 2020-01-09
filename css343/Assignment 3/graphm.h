// ------------------------------------------------ graphm.h -------------------------------------------------------
// Jun Zhen CSS343 Section A
// Creation Date: 7/29/19
// Date of Last Modification: 7/29/19
// --------------------------------------------------------------------------------------------------------------------
// Description - Header files for graphM.h
// -------------------------------------------------------------------------------------------------------------------- 

#ifndef GRAPHM_H
#define GRAPHM_H
#include"nodedata.h"
#include <iostream>
#include <climits>
#include <string>
#include <iomanip>
using namespace std;

//Max values for edges and vertices
int const MAXNODES = 100;
int const MAX = 99999;

class GraphM {
public:
	//Default constructor
	GraphM();

	//Main Functions
	void buildGraph(ifstream& file);
	bool insertEdge(int fromNode, int toNode, int dist);
	bool removeEdge(int fromNode, int toNode);
	void findShortestPath();
	void displayAll() const;
	void display(const int fromNode, const int toNode) const;

private:
	//Data fields
	NodeData data[MAXNODES];              
	int C[MAXNODES][MAXNODES];           
	int size;                             
	struct TableType {
		bool visited;        
		int dist;              
		int path;              
	};

	//Helper Functions
	TableType T[MAXNODES][MAXNODES];     
	void getPath(const int fromNode, const int toNode) const;
	void getPathName(const int fromNode, const int toNode) const;
	void getPathNameHelper(const int fromNode, const int toNode) const;
	int minDistance(int source);
};
#endif