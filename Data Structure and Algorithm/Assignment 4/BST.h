//
//  BST.h
//  FinalProject
//
//  Created by Jun zhen and kwontaeyoung on 8/15/19.
//  Copyright © 2019 Jun.Zhen&Tae.Y.Kwon. All rights reserved.
//
//
// -------------------------------------------------------------------------------------------------------
// Jun Zheng & Tae Young Kwon. Implementation Group#5.CSS 343A
//
// Date of Last Modification = 8/15/19
// --------------------------------------------------------------------------------------------------------------------
// Purpose - The purpose of this program is to practice & to implement designing program, class inheritence, HashTable,
//           and choosing data structures that are efficient in storing data- Movie information and customer information.
/*
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 Public Function
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 void insert(T& value)  - inserts the Node that contains movie data
 bool retrieve(const string director, const string movieName, T*& holder) - retrieves the Drama movie data
 bool retrieve(const string movieTitle, const int releaseYear, T*& holder) - retrieves the Comedy movie data
 bool retrieve(const string maFname, const string maLname, const int releaseMonth, const int releaseYear, T*& holder) - retrieves the Classic movie data
 bool isEmpty()         - checks if the BST is empty
 void deleteTree()      - deletes all the existing leaves and the root
 void display()         - displays all the leaves on the BST
 
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 Helper Function
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 void insertHelper(T& value, Node<T>*& node) - Helper function for insert()
 bool retrieveHelper(const string director, const string movieName, T*& holder, Node<T>* node) - Helper function for retrieve() 1
 bool retrieveHelper(const string movieTitle, const int releaseYear, T*& holder, Node<T>* node) - Helper function for retrieve() 2
 bool retrieveHelper(const string maFname, const string maLname, const int releaseMonth, const int releaseYear, T*& holder, Node<T>* node) - Helper function for retrieve() 3
 void displayHelper(Node<T>* current, int level) - Helper function for display()
 void deleteTreeHelper(Node<T>* node) - Helper function for deleteTree()
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 */

// --------------------------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions.
/*
 Specifications
 - The BST is the data container for all the movies(Comedy, Drama, and Classic).
 - It saves the movie in each node, and sort them by the given instruction below
 -comedy movies(ëFí)sorted by Title, then Year it release
 -dramas (ëDí) are sorted by Director, then Title
 -classics (ëCí)are sorted by Release date, then Majoractor
 Assumption
 -  Assuming that the movie data file is formatted in a given way by professor.
 
 */
// --------------------------------------------------------------------------------------------------------------------
#ifndef BST_HEADER
#define BST_HEADER
#include<iostream>
#include"Movie.h"
using namespace std;

// templatized Node
// contains data, node pointer to left and right
template<class T>
struct Node
{
    // casting the default setting
    Node(T m = NULL, Node* r = NULL, Node* l = NULL)
    {
        data = m;
        right = r;
        left = l;
    }
    T data;
    Node<T>* right;
    Node<T>* left;
};

template<class T>
class BST
{
public:
    
    // constructor & destructor
    BST(); // Default constructor
    ~BST(); // Destructor
    
    // public function
    void insert(T& value); // inserts the Node that contains movie data
    bool retrieve(const string director, const string movieName, T*& holder); // retrieves the Drama movie data
    bool retrieve(const string movieTitle, const int releaseYear, T*& holder); // retrieves the Comedy movie data
    bool retrieve(const string maFname, const string maLname, const int releaseMonth, const int releaseYear, T*& holder); // retrieves the Classic movie data
    bool retrieveSame(const string maFname, const string maLname, const string movieName, const string director, const int releaseMonth, const int releaseYear, T*& holder);
    bool isEmpty() const; // checks if the BST is empty
    void deleteTree(); // deletes all the existing leaves and the root
    void display() const; // displays all the leaves on the BST
    
private:
    Node<T>* root; // root node
    void insertHelper(T& value, Node<T>*& node); // Helper function for insert()
    bool retrieveHelper(const string director, const string movieName, T*& holder, Node<T>* node); // Helper function for retrieve() 1
    bool retrieveHelper(const string movieTitle, const int releaseYear, T*& holder, Node<T>* node); // Helper function for retrieve() 2
    bool retrieveHelper(const string maFname, const string maLname, const int releaseMonth, const int releaseYear, T*& holder, Node<T>* node); // Helper function for retrieve() 3
    bool retrieveSameHelper(const string maFname, const string maLname, const string movieName, const string director, const int releaseMonth, const int releaseYear, T*& holder, Node<T>* node);
    void displayHelper(Node<T>* current, int level) const; // Helper function for display()
    void deleteTreeHelper(Node<T>* node); // Helper function for deleteTree()
    
};

/*-------------------Default Constructor--------------------------*/
// Describtion
// - Constructs the object with default setting
//
// Preconditions: No parameters are passed in.
// Postconditions: The data variables are set as default value.
template<class T>
BST<T>::BST()
{
    root = NULL;
}
// end of Constructor
/*---------------------------------------------------------*/

/*-------------------Destructor--------------------------*/
// Describtion
// - execute deleteTree until the root is NULL
//
// Preconditions: No parameters are passed in.
// Postconditions: Deletes the entire BST
template<class T>
BST<T>::~BST()
{
    if (root != NULL)
    {
        deleteTree();
    }
}
// end of Constructor
/*---------------------------------------------------------*/

/*-------------------insert ()--------------------------*/
// Describtion
// - gets the address of the node and insert them through
//   its helper function
//
// Preconditions: Address of the node value is passed in
// Postconditions: Calls the helper function to insert it in sorted order
template<class T>
void BST<T>::insert(T& value)
{
    return insertHelper(value, root);
}
// end of insert
/*---------------------------------------------------------*/


/*-------------------insertHelper--------------------------*/
// Describtion
// - Helper function for the insert()
//
// Preconditions: Address of the node value and the root are passed in
// Postconditions: Finds the correct spot and insert the node
template<class T>
void BST<T>::insertHelper(T& value, Node<T>*& node)
{
    // If the root is null, instanciate the node
    if (node == NULL)
    {
        node = new Node<T>(value);
    }
    // if the movie exists, add to the movie stock
    else if (node->data == value)
    {
        node->data.addMovieStock(value.getMovieStock());
    }
    // if its smaller move left
    else if (node->data > value)
    {
        insertHelper(value, node->left);
    }
    // if its bigger move right
    else if (node->data < value)
    {
        insertHelper(value, node->right);
    }
}
// end of Constructor
/*---------------------------------------------------------*/


/*------------------- Retriever for dramaMovies --------------------------*/
// Describtion
// - find the movie, and retrieves the information & data
//
// Preconditions: string director's name, movie title, and movie holder are passed in
// Postconditions: call the helper function with parameters passed in

template<class T>
bool BST<T>::retrieve(const string director, const string movieName, T*& holder)
{
    // calls the helper function and return true if the movie is found
    return retrieveHelper(director, movieName, holder, root);
}
// end of retrieve
/*---------------------------------------------------------*/


/*-------------------dramaMovies retrieveHelper--------------------------*/
// Describtion
// - Travels BST root node to the very bottom
// - if movie is found, point the holder to the movie node and returns true
//
// Preconditions: string director's name, movie title, movie holder, and the root node are passed in
// Postconditions: Travels BST root node to the very bottom to find the movie in the data container
template<class T>
bool BST<T>::retrieveHelper(const string director, const string movieName, T*& holder, Node<T>* node)
{
    // general edge case #1
    if (node == NULL)
    {
        return false;
    }
    // if the movie exists, point the holder to the node, and return true
    else if ((node->data.getDirectorName() == director) && (node->data.getMovieName() == movieName))
    {
        holder = reinterpret_cast<T*>(node);
        return true;
    }
    else
    {
        // else travel down to the end of the BST
        return retrieveHelper(director, movieName, holder, node->left) || retrieveHelper(director, movieName, holder, node->right);
    }
    // if nothing works, return false
    return false;
}
// end of retrieveHelper
/*---------------------------------------------------------*/


/*-------------------Retriever for comedyMovies--------------------------*/
// Describtion
// - find the movie, and retrieves the information & data
//
// Preconditions: string director's name, movie title, and movie holder are passed in
// Postconditions: call the helper function with parameters passed in
template<class T>
bool BST<T>::retrieve(const string movieTitle, const int releaseYear, T*& holder)
{
    return retrieveHelper(movieTitle, releaseYear, holder, root);
}
// end of retrieve
/*---------------------------------------------------------*/


/*-------------------RetrieverHelper for comedyMovies--------------------------*/
// Describtion
// - Travels BST root node to the very bottom
// - if movie is found, point the holder to the movie node and returns true
//
// Preconditions: string director's name, movie title, movie holder, and the root node are passed in
// Postconditions: Travels BST root node to the very bottom to find the movie in the data container
template<class T>
bool BST<T>::retrieveHelper(const string movieTitle, const int releaseYear, T*& holder, Node<T>* node)
{
    if (node == NULL)
    {
        return false;
    }
    else if ((node->data.getMovieName() == movieTitle) && (node->data.getReleaseYear() == releaseYear))
    {
        holder = reinterpret_cast<T*>(node);
        return true;
    }
    else
    {
        return retrieveHelper(movieTitle, releaseYear, holder, node->left) || retrieveHelper(movieTitle, releaseYear, holder, node->right);
    }
    return false;
}
// end of retrieveHelper
/*---------------------------------------------------------*/


/*-------------------Retriever for classicMovies--------------------------*/
// Describtion
// - find the movie, and retrieves the information & data
//
// Preconditions: string director's name, movie title, and movie holder are passed in
// Postconditions: call the helper function with parameters passed in

template<class T>
bool BST<T>::retrieve(const string maFname, const string maLname, const int releaseMonth, const int releaseYear, T*& holder)
{
    return retrieveHelper(maFname, maLname, releaseMonth, releaseYear, holder, root);
}
// end of retrieve
/*---------------------------------------------------------*/


/*-------------------Default Constructor--------------------------*/
// Describtion
// - Travels BST root node to the very bottom
// - if movie is found, point the holder to the movie node and returns true
//
// Preconditions: string director's name, movie title, movie holder, and the root node are passed in
// Postconditions: Travels BST root node to the very bottom to find the movie in the data container
template<class T>
bool BST<T>::retrieveHelper(const string maFname, const string maLname, const int releaseMonth, const int releaseYear, T*& holder, Node<T>* node)
{
    if (node == NULL)
    {
        return false;
    }
    else if ((node->data.getMaFirstName() == maFname) && (node->data.getMaLastName() == maLname) && (node->data.getReleaseYear() == releaseYear) && node->data.getReleaseMonth() == releaseMonth)
    {
        holder = reinterpret_cast<T*>(node);
        return true;
    }
    else
    {
        return retrieveHelper(maFname, maLname, releaseMonth, releaseYear, holder, node->left) || retrieveHelper(maFname, maLname, releaseMonth, releaseYear, holder, node->right);
    }
    return false;
}
// end of retrieveHelper
/*---------------------------------------------------------*/

//retriever for classicMovies
template<class T>
bool BST<T>::retrieveSame(const string maFname, const string maLname, const string movieName, const string director, const int releaseMonth, const int releaseYear, T*& holder)
{
    return retrieveSameHelper(maFname, maLname, movieName, director, releaseMonth, releaseYear, holder, root);
}

template<class T>
bool BST<T>::retrieveSameHelper(const string maFname, const string maLname, const string movieName, const string director, const int releaseMonth, const int releaseYear, T*& holder, Node<T>* node)
{
    if (node == NULL)
    {
        return false;
    }
    else if ((node->data.getMovieName() == movieName) && (node->data.getDirectorName() == director) && (node->data.getReleaseYear() == releaseYear) && (node->data.getReleaseMonth() == releaseMonth) && (node->data.getMovieStock() > 0) && node->data.getMaFirstName() != maFname && node->data.getMaLastName() != maLname)
    {
        holder = reinterpret_cast<T*>(node);
        return true;
    }
    else
    {
        return retrieveSameHelper(maFname, maLname, movieName, director, releaseMonth, releaseYear, holder, node->left) || retrieveSameHelper(maFname, maLname, movieName, director, releaseMonth, releaseYear, holder, node->right);
        
    }
    return false;
}


/*-------------------isEmpty--------------------------*/
// Describtion
// - Checks if the tree is empty or not
//
// Preconditions: No parameters are passed in.
// Postconditions: Returns true if the root is empty
template<class T>
bool BST<T>::isEmpty() const
{
    if (root != NULL)
    {
        return false;
    }
    else
    {
        return true;
    }
}
// end of Constructor
/*---------------------------------------------------------*/


/*-------------------deleteTree() --------------------------*/
// Describtion
// - delete the node, leaf, on the BST
//
// Preconditions: No parameters are passed in.
// Postconditions: Calls the helper function with passing the root
template<class T>
void BST<T>::deleteTree()
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        deleteTreeHelper(root);
    }
}
// end of Constructor
/*---------------------------------------------------------*/


/*-------------------deleteTreeHelper--------------------------*/
// Describtion
// - Deletes all the nodes in the BST
//
// Preconditions: The node pointer is passed in(usually root)
// Postconditions: The function deletes entire BST recursively
template<class T>
void BST<T>::deleteTreeHelper(Node<T>* node)
{
    // stops the recursive calls
    if (node == NULL)
    {
        return;
    }
    // recursive call
    deleteTreeHelper(node->left);
    deleteTreeHelper(node->right);
    delete node;
    node = NULL;
}
// end of Constructor
/*---------------------------------------------------------*/


/*-------------------display-------------------------*/
// Describtion
// - Displays entire BST nodes by one by one
//
// Preconditions: No parameters are passed in.
// Postconditions: The function calls the helper function with passing root node
template<class T>
void BST<T>::display() const
{
    displayHelper(root, 0);
}
// end of Constructor
/*---------------------------------------------------------*/


/*-------------------displayHelper--------------------------*/
// Describtion
// - Displays the node data one by one (in-order)
//
// Preconditions: root node and the integer of level are passed in
// Postconditions: The function recursively travel inorder and prints out the data
template<class T>
void BST<T>::displayHelper(Node<T>* node, int level) const
{
    if (node != NULL) {
        // left root right =  inorder traversal
        displayHelper(node->left, level);
        cout << (node->data) << endl;        // display information of object
        displayHelper(node->right, level);
    }
}
// end of Constructor
/*---------------------------------------------------------*/
#endif
