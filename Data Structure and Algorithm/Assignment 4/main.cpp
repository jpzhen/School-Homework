//
//  main.cpp
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
 
 */

// --------------------------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions.
/*
 Specifications
 
 
 Assumption
 -  Make sure the input file address is in correct format and correct name
 - Assuming that Movie Data file is fo
 
 -  Assuming that the command data are formatted correctly.
     - For Inventory = I
     - For History = H (four digit account number)
     - For Borrow & Return
         = For Classic Movie - (B || R) (account number) (Media Type) (C) (Released Month) (Released Year) (Major Actor's First Name) (Major Actor's Last Name)
         = For Comedy Movie  - (B || R) (account number) (Media Type) (F) (Movie Title), (Released Year)
         = For Drama Movie   - (B || R) (account number) (Media Type) (D) (Director's Name), (Movie Title),
 
 */
// --------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include"Store.h"

int main()
{
    // Welcome to the Block Buster!
    Store blockbuster;
	string s;
	// Processing the Movie Data
	cout << "Please enter a Movie file: ";
	cin >> s;
	blockbuster.readMovieFile(s);

	// Processing the Customer data
	cout << "Please enter a Customer file: ";
	cin >> s;
	
	// Processing the Command data
	blockbuster.readCustomerFile(s);
	cout << "Please enter a Command file: ";
	cin >> s;
	blockbuster.readCommandFile(s);
	cout << endl;
    return 0;
}
