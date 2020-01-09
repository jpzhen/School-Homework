#ifndef BINTREE_H
#define BINTREE_H
#include<iostream>
#include"nodedata.h"
#include<algorithm>
#include<string>
#include<sstream>
using namespace std;


class BinTree {				// you add class/method comments and assumptions
	friend ostream& operator<<(ostream& out, const BinTree& tree);
public:

	//Constructor and Destructors
	BinTree();								
	BinTree(const BinTree& tree);			
	~BinTree();			

	//Main functons
	bool isEmpty() const;					
	void makeEmpty();						
	BinTree& operator=(const BinTree& otherTree);
	bool operator==(const BinTree& otherTree) const;
	bool operator!=(const BinTree& otherTree) const;
	bool insert(NodeData* newNode);
	bool retrieve(const NodeData& value, NodeData*& holder);
	int getHeight(const NodeData& value) const;
	void bstreeToArray(NodeData* arr []);
	void arrayToBSTree(NodeData* arr []);
	void displaySideways() const;	

private:

	//Data Fields
	struct Node {
		NodeData* data;						// pointer to data object
		Node* left;							// left subtree pointer
		Node* right;						// right subtree pointer
		Node(NodeData* nd = NULL, Node* l = NULL, Node* r = NULL)
		{
			data = nd;
			left = l;
			right = r;
		}
	};
	Node* root;							

    //Utility/helper functions
	int countArraySize(NodeData* arr[]);
	void arrayToBSTreeHelper(Node* node, int begin, int end, NodeData* arr[]);
	int bstreeToArrayHelper(Node* node, NodeData* arr[]);
	bool findNode(NodeData& value, Node* node, Node*& holder) const;
	bool compareTree(Node* node1, Node* node2) const;
	bool copyTree(const Node* node);
	void makeEmptyHelper(Node* node);
	int getHeightHelper(Node*& node) const;
	bool retrieveHelper(Node*& node, const NodeData& value, NodeData*& holder); 
	bool insertHelper(Node*& node, NodeData* newData);
	void inorderHelper(Node* node) const;
	void sideways(Node* current, int level) const;		
};
#endif 