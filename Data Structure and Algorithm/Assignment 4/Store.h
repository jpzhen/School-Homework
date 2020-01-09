//
//  Store.h
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
 bool readMovieFile(string fileName)      - process movie data file
 bool readCustomerFile(string fileName)   - process customer data file
 bool readCommandFile(string fileName)    - process command data file
 void inventory()                         - checks inventory of dvds for movie
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 
 */

// --------------------------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions.
/*
 Specifications
 
 
 Assumption
 -  Make sure the input file address is in correct format.
 -  Assuming that the command data are formatted correctly.
    - For Inventory = I
    - For History = H (four digit account number)
    - For Borrow & Return
        = For Classic Movie - (B || R) (account number) (Media Type) (C) (Released Month) (Released Year) (Major Actor's First Name) (Major Actor's Last Name)
        = For Comedy Movie  - (B || R) (account number) (Media Type) (F) (Movie Title), (Released Year)
        = For Drama Movie   - (B || R) (account number) (Media Type) (D) (Director's Name), (Movie Title),
 */
// --------------------------------------------------------------------------------------------------------------------
#ifndef Store_h
#define Store_h
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "BST.h"
#include "HashTable.h"
#include "Customer.h"
#include "Movie.h"
#include"ClassicMovie.h"
#include"ComedyMovie.h"
#include"DramaMovie.h"
using namespace std;

class Store
{
public:
    
    // Constructor and Destructor
	Store(); // default constructor
	~Store(); // destructor
    
    // public function
	bool readMovieFile(string fileName); // process movie data file
	bool readCustomerFile(string fileName); // process customer data file
	bool readCommandFile(string fileName); // process command data file
	void inventory(); // checks inventory of dvds for movie

private:
	BST <ComedyMovie> comedyBST;
	BST <DramaMovie> dramaBST;
	BST <ClassicMovie> classicBST;
	HashTable accountTable;
};
#endif
