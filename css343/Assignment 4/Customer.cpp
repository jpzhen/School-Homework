//
//  Customer.cpp
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
 Getter
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 int& getCustomerID()   - returns address of the customer ID;
 
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 Public Function
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 void trackRecords()    - Saves the customer's transaction
 void showRecords()     - Displays the customer's transaction chronogical order. (Newest to oldest)
 
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 Overriding Operator Overloads
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 friend ostream& operator <<(ostream& out, Customer& other)
 bool operator==(const Customer&)
 bool operator!=(const Customer&)
 
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 */

// --------------------------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions.
/*
 Specifications
 - The customer class stores customer information: ID, first name, last name, and transaction history
 
 Assumption
 -  Assuming that the customer data file is formatted in a given way by professor.
 
 */
// --------------------------------------------------------------------------------------------------------------------


#include "Customer.h"

/*-------------------Default Constructor--------------------------*/
// Describtion
// - Constructs the object with default setting
//
// Preconditions: No parameters are passed in.
// Postconditions: The data variables are set as default value.
Customer::Customer()
{
	customerID = 0;
	firstName = "";
	lastName = "";
}
// end of Constructor
/*---------------------------------------------------------*/

/*------------------- Casting datas to Constructor --------------------------*/
// Describtion
// - Constructs a object with the following parameters saved in to the data variables
//
// Preconditions: Character of movie genre, integer of movie stock, string of director name
//                string of movie title, and integer of released year are passed in as parameter.
// Postconditions: The parameters are saved into the data variables by a given structure.
Customer::Customer(int ID, string fName, string lName)
{
	customerID = ID;
	firstName = fName;
	lastName = lName;
}
// end of Constructor
/*---------------------------------------------------------*/

/*--------------------Destructor-----------------------*/
// Describtion
// - needed so customer data can be deleted
//
// Preconditions: No parameters are passed in
// Postconditions: Will be deleted from the Hash Table
Customer::~Customer()
{
	// delete all the Customer data
}
// end of Destructor
/*---------------------------------------------------------*/

/*--------------------getCustomerID()-----------------------*/
// Describtion
// - returns the customer ID number
//
// Preconditions: No parameters are passed in
// Postconditions: Returns the address of the Customer ID
int& Customer::getCustomerID()
{
	int& ptr = customerID;
	return ptr;
}
// end of getCustomerID
/*---------------------------------------------------------*/

/*--------------------trackRecords()-----------------------*/
// Describtion
// - Saves the transaction history by pushing in string line
//
// Preconditions: string s, which it contains transation information, is passed in
// Postconditions: push in the data into the transaction memory(vector<string>)
void Customer::trackRecords(string s)
{
	records.push_back(s);
}
// end of getCustomerID
/*---------------------------------------------------------*/

/*--------------------showRecords()-----------------------*/
// Describtion
// - Iteratively go through each elements in vector and prints out the data
//
// Preconditions: No parameters are passed in
// Postconditions: prints out the data
void Customer::showRecords()
{
	if (records.empty())
	{
		cout << "NO CUSTOMER HISTORY" << endl;
	}
	else
	{
        for (auto it = records.end()-1; it != records.begin()-1; it--)
        {
            cout << *it << endl;
        }
	}
}
// end of getCustomerID
/*---------------------------------------------------------*/

/*--------------------operator==()-----------------------*/
// Describtion
// - checks if the customer ID is identicle
//
// Preconditions: address of the customer object is passed in
// Postconditions: returns true if the both customer ID are identicle
bool Customer::operator==(const Customer& other) const
{
	return customerID == other.customerID;
}

// end of operator==
/*---------------------------------------------------------*/

/*--------------------operator!=()-----------------------*/
// Describtion
// - checks if the customer ID is un-identicle
//
// Preconditions: address of the customer object is passed in
// Postconditions: returns true if the both customer ID are un-identicle
bool Customer::operator!=(const Customer& other) const
{
	return customerID != other.customerID;
}

// end of operator!=
/*---------------------------------------------------------*/

/*-------------------- operator <<()-----------------------*/
// Describtion
// - prints out in a specific structure listed below
//
// Preconditions: ostream and the address of the customer object are passed in
// Postconditions: returns ostream that is saved with the set of string line.
ostream& operator <<(ostream& out, Customer& other)
{
	return out << "Customer ID: " << other.customerID << " Name: " << other.firstName << " " << other.lastName;
}

// end of operator <<
/*---------------------------------------------------------*/
