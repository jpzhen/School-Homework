//
//  HashTable.h
//  FinalProject
//
//  Created by Jun zhen and kwontaeyoung on 8/15/19.
//  Copyright © 2019 Jun.Zhen&Tae.Y.Kwon. All rights reserved.
//
//
// ------------------------------------------------graphm.h -------------------------------------------------------
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
 int hashFunction(int value)              - resizes the Hash size
 void insert(Customer* c)                 - insert customer hashnode in the HashTable
 void display()                           - displays all the customer in the HashTable
 void remove()                            - removes the customer from HashTable
 bool contain(Customer* c)                - checks if customer is saved
 bool retrieve(int id, Customer*& holder) - retrieves customer's data by pointing with holder
 bool getHistory(int id)                  - retrieves customer's history
 bool exist(int id)                       - checks if the customer exists
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 
 */

// --------------------------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions.
/*
 Specifications

 
 Assumption

 
 */
// --------------------------------------------------------------------------------------------------------------------
#ifndef HashTable_h
#define HashTable_h
#include<vector>
#include<iomanip>
#include "Customer.h"
#include "Movie.h"
#include "BST.h"

struct HashNode
{
	HashNode(Customer data, HashNode* next = NULL)
	{
		this->data = data;
		this->next = next;
	}
	Customer data;
	HashNode* next;
};

class HashTable
{
public:
    
    // constructor & destructor
	HashTable(); // default constructor
	~HashTable(); // destructor
    
    // public function
	int hashFunction(int value); // resizes the Hash size
	void insert(Customer* c); // insert customer hashnode in the HashTable
	void display(); // displays all the customer in the HashTable
	void remove(); // removes the customer from HashTable
	bool contain(Customer* c); // checks if customer is saved
	bool retrieve(int id, Customer*& holder); // retrieves customer's data by pointing with holder
	bool getHistory(int id); // retrieves customer's history
	bool exist(int id); // checks if the customer exists
    
    
private:
	int size;
	int capacity;
	HashNode** elements;
};

#endif
