//
//  HashTable.cpp
//  FinalProject
//
//  Created by Jun zhen and kwontaeyoung on 8/15/19.
//  Copyright © 2019 Jun.Zhen&Tae.Y.Kwon. All rights reserved.
//
//
// ------------------------------------------------ -------------------------------------------------------
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
#include "HashTable.h"

/*-------------------Constructor()--------------------------*/
// Description
// Creates the hashtable class and set every value to 0 or NULL
//
// Preconditions: None
// Postconditions: None
HashTable::HashTable()
{
    size = 0;
    capacity = 10;
    elements = new HashNode * [10]();
}
// end of Constructor
/*---------------------------------------------------------*/

/*-------------------Destructor--------------------------*/
// Description
// Deallocate all memory in heap
//
// Preconditions: Class is not empty
// Postconditions: No memory leak
HashTable::~HashTable()
{
    if (size != 0)
    {
        this->remove();
    }
}
// end of Destructor
/*---------------------------------------------------------*/

/*-------------------hashFunction()--------------------------*/
// Description
// Determine where in the hashtable the value will place in
//
// Preconditions: none
// Postconditions: none
int HashTable::hashFunction(int value)
{
    return value % capacity;
}
// end of hashFunction
/*---------------------------------------------------------*/

/*-------------------insert()--------------------------*/
// Description
// Insert a value into the hashtable
//
// Preconditions: None
// Postconditions: The value is sitting on the correct spot
void HashTable::insert(Customer* c)
{
    if (!this->contain(c))
    {
        int spot = hashFunction(c->customerID);
        HashNode* newNode = new HashNode(*c);
        newNode->next = elements[spot];
        elements[spot] = newNode;
        size++;
    }
}
// end of insert
/*---------------------------------------------------------*/

/*-------------------display()--------------------------*/
// Description
// Show all the values in the hashtable
//
// Preconditions: Hashtable must not be empty
// Postconditions: None
void HashTable::display()
{
    for (int i = 0; i < capacity; i++)
    {
        cout << "[" << i << "]:";
        HashNode* current = elements[i];
        while (current != NULL)
        {
            cout << " -> " << setw(2) << current->data;
            current = current->next;
        }
        cout << " /" << endl;
    }
    cout << "size = " << size << endl;
}
// end of display
/*---------------------------------------------------------*/

/*-------------------remove()--------------------------*/
// Description
// Remove value from hashtable
//
// Preconditions: Hashtable must not be empty
// Postconditions: No memory leak
void HashTable::remove()
{
    for (int i = 0; i < capacity; i++)
    {
        HashNode* current;
        while (elements[i] != NULL)
        {
            current = elements[i];
            elements[i] = elements[i]->next;
            delete current;
            current = NULL;
            size--;
        }
    }
    delete elements;
}
// end of remove
/*---------------------------------------------------------*/

/*-------------------contain()--------------------------*/
// Description
// Check whether the value is inside the hashtable
//
// Preconditions: None
// Postconditions: None
bool HashTable::contain(Customer* c)
{
    int spot = hashFunction(c->customerID);
    HashNode* current = elements[spot];
    while (current != NULL)
    {
        if (current->data == *c)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}
// end of contain
/*---------------------------------------------------------*/

/*-------------------getHistory()--------------------------*/
// Describtion
// Find the value and print out all its transaction history
//
// Preconditions: Must exist in the hashtable
// Postconditions: None
bool HashTable::getHistory(int id)
{
    int spot = hashFunction(id);
    HashNode* current = elements[spot];
    while (current != NULL)
    {
        if (current->data.customerID == id)
        {
            current->data.showRecords();
            return true;
        }
        current = current->next;
    }
    return false;
}
// end of getHistory
/*---------------------------------------------------------*/


/*-------------------exist()--------------------------*/
// Description
// Check whether the value is inside the hashtable
//
// Preconditions: None
// Postconditions: None
bool HashTable::exist(int id)
{
    int spot = hashFunction(id);
    HashNode* current = elements[spot];
    while (current != NULL)
    {
        if (current->data.customerID == id)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}
// end of exist
/*---------------------------------------------------------*/


/*-------------------retrieve()--------------------------*/
// Describtion
// Find the associate value and set it to the holder
//
// Preconditions: Value must exist in the hashtable
// Postconditions:
bool HashTable::retrieve(int id, Customer*& holder)
{
    int spot = hashFunction(id);
    HashNode* current = elements[spot];
    while (current != NULL)
    {
        if (current->data.customerID == id)
        {
            holder = &current->data;
            return true;
        }
        current = current->next;
    }
    return false;
}
// end of retrieve
/*---------------------------------------------------------*/
