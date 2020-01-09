#include "bintree.h"
#include <fstream>
#include <iostream>
using namespace std;

const int ARRAYSIZE = 100;

//global function prototypes
void buildTree(BinTree&, ifstream&);      
void initArray(NodeData* []);   

int main()
{
	ifstream infile("inputdata.txt");
	if (!infile) {
		cout << "File could not be opened." << endl;
		return 1;
	}
	NodeData notND("not");
	NodeData andND("and");
	NodeData sssND("sss");
	NodeData tttND("ttt");
	NodeData osdoND("osdo");
	NodeData sdaND("sda");
	NodeData eeeND("eee");
	NodeData mghND("mgh");
	NodeData tND("t");

	cout << "Testing for Node constructor: " << osdoND << endl;

	BinTree T, T2, dup;
	NodeData* ndArray[ARRAYSIZE];
	initArray(ndArray);
	cout << "Initial data:" << endl << "  ";
	buildTree(T, infile);              // builds and displays initial data
	cout << endl;
	BinTree first(T);                  // test copy constructor
	dup = dup = T;                     // test operator=, self-assignment
	while (!infile.eof()) {
		cout << "----------------------- Testing for Inorder Output -----------------------" << endl;
		cout << "Tree Inorder:" << endl << T;             // operator<< does endl
		T.displaySideways();

		cout << "----------------------- Testing for Retrieve -----------------------" << endl;
		NodeData* p;                    // pointer of retrieved object
		bool found;                     // whether or not object was found in tree
		found = T.retrieve(andND, p);
		cout << "Retrieve --> and:  " << (found ? "found" : "not found") << endl;
		found = T.retrieve(notND, p);
		cout << "Retrieve --> not:  " << (found ? "found" : "not found") << endl;
		found = T.retrieve(sssND, p);
		cout << "Retrieve --> sss:  " << (found ? "found" : "not found") << endl;

		cout << "----------------------- Testing for getHeight -----------------------" << endl;
		cout << "Height    --> and:  " << T.getHeight(andND) << endl;
		cout << "Height    --> not:  " << T.getHeight(notND) << endl;
		cout << "Height    --> sss:  " << T.getHeight(sssND) << endl;
		cout << "Height    --> osodo:  " << T.getHeight(osdoND) << endl;
		cout << "Height    --> eee:  " << T.getHeight(eeeND) << endl;
		cout << "Height    --> t:  " << T.getHeight(tND) << endl;

		cout << "----------------------- Testing for Comparable operator -----------------------" << endl;
		T2 = T;
		cout << "T == T2?     " << (T == T2 ? "equal" : "not equal") << endl;
		cout << "T != first?  " << (T != first ? "not equal" : "equal") << endl;
		cout << "T == dup?    " << (T == dup ? "equal" : "not equal") << endl;
		dup = T;

		cout << "----------------------- Testing for BST to ARR and ARR to BST -----------------------" << endl;
		T.bstreeToArray(ndArray);
		T.arrayToBSTree(ndArray);
		T.displaySideways();

		T.makeEmpty();                  // empty out the tree
		initArray(ndArray);             // empty out the array

		cout << "---------------------------------------------------------------"<< endl;
		cout << "Initial data:" << endl << "  ";
		buildTree(T, infile);
		cout << endl;
	}

	return 0;
}

void buildTree(BinTree& T, ifstream& infile) {
	string s;

	for (;;) {
		infile >> s;
		cout << s << ' ';
		if (s == "$$") break;                // at end of one line
		if (infile.eof()) break;             // no more lines of data
		NodeData* ptr = new NodeData(s);     // NodeData constructor takes string
		// would do a setData if there were more than a string

		bool success = T.insert(ptr);
		if (!success)
			delete ptr;                       // duplicate case, not inserted 
	}
}

//------------------------------- initArray ----------------------------------
// initialize the array of NodeData* to NULL pointers

void initArray(NodeData* ndArray[]) {
	for (int i = 0; i < ARRAYSIZE; i++)
		ndArray[i] = NULL;
}