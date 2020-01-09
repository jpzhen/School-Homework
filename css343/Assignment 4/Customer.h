//
//  Customer.h
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

#ifndef Customer_h
#define Customer_h
#include<iostream>
#include <stdio.h>
#include<string>
#include<vector>

using namespace std;

class Customer
{
public:
    // Constructor & Destructor
	Customer(); // default constructor
	Customer(int ID, string fName, string lName); // data is set equal to parameter
	~Customer(); // destructor
    
    // Getter function
    int& getCustomerID(); // returns customer ID;
    
    // public function
	void trackRecords(string s); // Saves the customer's transaction
	void showRecords(); // Displays the customer's transaction chronogical order. (Newest to oldest)
    
    //operation overloads
	friend ostream& operator <<(ostream& out, Customer& other);
	bool operator==(const Customer&) const;
	bool operator!=(const Customer&) const;

private:
	int customerID; // customer ID
	string firstName; // customer's first name
	string lastName; // customer's last name
	vector<string> records;
	friend class HashTable;

	// Stack or Map for saving the transaction History
	// The order needs to be "latest to oldest"


};
#endif /* Customer_HEADER */
