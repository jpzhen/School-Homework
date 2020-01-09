#include "bintree.h"

//------------------------- Defualt Constructor ---------------------------------
// Initialize Tree
// Preconditions: None
// Postconditions: None
BinTree::BinTree()
{
	root = NULL;
}

//------------------------- Copy Constructor ---------------------------------
// Initialize Tree and copy parameter's value
// Preconditions: Parameter tree must not be empty
// Postconditions: Same value as the parameter
BinTree::BinTree(const BinTree& tree)
{
	root = NULL;
	*this = tree;
}

//-------------------------  Destructor ---------------------------------
// Free up all allocated memories and remove tree
// Preconditions: Parameter tree must not be empty
// Postconditions: Tree must be empty
BinTree::~BinTree()
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		this->makeEmpty();
	}
}


//------------------------- isEmpty ---------------------------------
// Check if tree is empty or not
// Preconditions: None
// Postconditions: None
bool BinTree::isEmpty() const
{
	if (root == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//------------------------- findNode ---------------------------------
// Search the tree to find the value given by parameter
// Preconditions: Tree must not be empty
// Postconditions: Holder will point to the value in the tree
bool BinTree::findNode(NodeData& value, Node* node, Node*& holder) const
{
	if (node == NULL)
	{
		return false;
	}
	else if (*node->data == value)
	{
		holder = node;
		return true;
	}
	else
	{
		return findNode(value, node->left, holder) || findNode(value, node->right, holder);
	}
}

//------------------------- operator!= ---------------------------------
// Check two tree if there are equal or not
// Preconditions: None
// Postconditions: None
bool BinTree::operator!=(const BinTree& otherTree) const
{
	return !(*this == otherTree);
}

//------------------------- operator!= ---------------------------------
// Check two tree if there are equal or not
// Preconditions: None
// Postconditions: None
bool BinTree::operator==(const BinTree& otherTree) const
{
	if (this->isEmpty() || otherTree.isEmpty())
	{
		return false;
	}
	else if (this->isEmpty() || otherTree.isEmpty())
	{
		return true;
	}
	else
	{
		return compareTree(root, otherTree.root);
	}
}

//------------------------- compareTree ---------------------------------
// Check two tree if there are equal or not
// Preconditions: None
// Postconditions: None
bool BinTree::compareTree(Node* node1, Node* node2) const
{
	if ((node1 == NULL && node2 == NULL))
	{
		return true;
	}
	else if ((node1 != NULL && node2 == NULL) || (node1 == NULL && node2 != NULL))
	{
		return false;
	}
	else if (*node1->data == *node2->data)
	{
		return compareTree(node1->left, node2->left) && compareTree(node1->right, node2->right);
	}
	else
	{
		return false;
	}
}

//------------------------- operator= ---------------------------------
// Assigning operator, copy the values of parameter to itself
// Preconditions: Must not be the same tree
// Postconditions: None
BinTree& BinTree::operator=(const BinTree& otherTree)
{
	if (*this != otherTree)
	{
		this->makeEmpty();
		copyTree(otherTree.root);
	}
	return *this;
}
bool BinTree::copyTree(const Node* node)
{
	if (node)
	{
		this->insert(node->data);
		copyTree(node->left);
		copyTree(node->right);
		return true;
	}
	else
	{
		return false;
	}
}

//------------------------- makeEmpty ---------------------------------
// Empty out the whole tree and set root to null
// Preconditions: None
// Postconditions: None
void BinTree::makeEmpty()
{
	if (root != NULL)
	{
		makeEmptyHelper(root);
	}
}
void BinTree::makeEmptyHelper(Node* node)
{
	if (node == NULL)
	{
		return;
	}
	makeEmptyHelper(node->left);
	makeEmptyHelper(node->right);
	delete node;
	root = NULL;
}

//------------------------- arrayToBSTree ---------------------------------
// Store all the data in a array into an tree
// Preconditions: Tree must be empty and array must not be empty
// Postconditions: array must be empty
void BinTree::arrayToBSTree(NodeData* arr[])
{
	if (root == NULL)
	{
		int n = countArraySize(arr);
		arrayToBSTreeHelper(root, 0, n - 1, arr);
	}
	else
	{
		this->isEmpty();
		int n = countArraySize(arr);
		arrayToBSTreeHelper(root, 0, n - 1, arr);
	}
}
void BinTree::arrayToBSTreeHelper(Node* node, int begin, int end, NodeData* arr[])
{
	if (begin > end) {
		node = NULL;
	}
	else {
		int middle = (end + begin) / 2;
		insert(arr[middle]);
		arr[middle] = NULL;
		int firstEnd = middle - 1;
		int secondStart = middle + 1;
		arrayToBSTreeHelper(node, begin, firstEnd, arr);
		arrayToBSTreeHelper(node, secondStart, end, arr);
	}
}

//------------------------- countArraySize ---------------------------------
// Count how many elements in the array
// Preconditions: none
// Postconditions: none
int BinTree::countArraySize(NodeData* arr[])
{
	int count = 0;
	while (arr[count] != NULL)
	{
		count++;
	}
	return count;
}

//------------------------- bstreeToArray ---------------------------------
// Store all the data in a tree into an array with inorder traversal
// Preconditions: Array must be empty and Tree must not be empty
// Postconditions: Tree must be empty
void BinTree::bstreeToArray(NodeData* arr[])
{
	bstreeToArrayHelper(root, arr);
	makeEmpty();
}
int BinTree::bstreeToArrayHelper(Node* node, NodeData* arr[])
{
	if (node != NULL) {
		int before = bstreeToArrayHelper(node->left, arr);
		NodeData* tempIns;
		tempIns = node->data;
		node->data = NULL;
		*(arr + before) = tempIns;
		tempIns = NULL;
		int newAdd = before + 1;
		int after = bstreeToArrayHelper(node->right, arr + newAdd);
		return 1 + after + before;
	}
	return 0;
}

//------------------------- getHeight ---------------------------------
// Get the height of the a node
// Preconditions: tree must not be negative
// Postconditions: none
int BinTree::getHeight(const NodeData& value) const
{
	Node* current;
	NodeData v = value;
	if (this->findNode(v, root, current))
	{
		return getHeightHelper(current);
	}
	else
	{
		return 0;
	}
}
int BinTree::getHeightHelper(Node*& node) const
{
	if (node == NULL)
	{
		return 0;
	}
	else
	{
		return max(getHeightHelper(node->left), getHeightHelper(node->right)) + 1;
	}
}

//------------------------- retrieve ---------------------------------
// Find the corrsponding node value and link it with parameter
// Preconditions: tree must not be negative
// Postconditions: parameter ptr will point to the node 
bool BinTree::retrieve(const NodeData& value, NodeData*& holder)
{
	if (root != NULL)
	{
		return retrieveHelper(root, value, holder);
	}
	else
	{
		return false;
	}
}
bool BinTree::retrieveHelper(Node*& node, const NodeData& value, NodeData*& holder)
{
	if (*node->data == value)
	{
		holder = node->data;
		return true;
	}
	else if (*node->data > value && node->left != NULL)
	{
		return retrieveHelper(node->left, value, holder);
	}
	else if (*node->data < value && node->right != NULL)
	{
		return retrieveHelper(node->right, value, holder);
	}
	else
	{
		return false;
	}
}

//------------------------- insert ---------------------------------
// Insert the given value into the tree
// Preconditions: No duplicates
// Postconditions: value is inserted in the correct position
bool BinTree::insert(NodeData* newData)
{
	return insertHelper(root, newData);
}
bool BinTree::insertHelper(Node*& node, NodeData* newData)
{
	if (node == NULL)
	{
		node = new Node(newData);
		return true;
	}
	else if (*node->data > * newData)
	{
		return insertHelper(node->left, newData);
	}
	else if (*node->data < *newData)
	{
		return insertHelper(node->right, newData);
	}
	else
	{
		return false;
	}
}
//------------------------- operator<< ---------------------------------
// Print out the tree's value with inorder traversal
// Preconditions: No duplicates
// Postconditions: value is inserted in the correct position
ostream& operator<<(ostream& out, const BinTree& tree)
{
	tree.inorderHelper(tree.root);
	return out << endl;
}
void BinTree::inorderHelper(Node* node) const
{
	if (node == NULL)
	{
		return;
	}
	inorderHelper(node->left);
	cout << *node->data << " ";
	inorderHelper(node->right);
}

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const {
	sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}
