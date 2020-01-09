//
//  ComedyMovie.h
//  FinalProject
//
//  Created by Jun zhen and kwontaeyoung on 8/15/19.
//  Copyright © 2019 Jun.Zhen&Tae.Y.Kwon. All rights reserved.
//
//
// ------------------------------------------------graphm.h -------------------------------------------------------
// Jun Zheng & Tae Young Kwon. Implementation Group #5.CSS 343A
//
// Date of Last Modification = 8/15/19
// --------------------------------------------------------------------------------------------------------------------
// Purpose - The purpose of this program is to practice & to implement designing program, class inheritence, HashTable,
//           and choosing data structures that are efficient in storing data- Movie information and customer information.
/*

 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 Overriding Operator Overloads
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 The comedy is sorted by the Title of the movie and the released year.
 The comparisons are based on the movie title and the released year.
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 virtual bool operator <()
 virtual bool operator >()
 virtual bool operator !=()
 virtual bool operator ==()
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 */

// --------------------------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions.
/*
 Specifications
 - This class is a child class of the Movie class. It has the access to the parents class's public functions and protected data
 - When "cout <<," the first two information are one that used on sorting. Rest of the information will be printed inisde of the bracket.
 Assumption
 -  Assuming that the movie data file is formatted in a given way by professor.
 
 */
// --------------------------------------------------------------------------------------------------------------------
#include"Movie.h"
#ifndef ComedyMovie_h
#define ComedyMovie_h

class ComedyMovie : public Movie
{
public:
	// Constructor & Destructor
	ComedyMovie(); // Default Constructor
	ComedyMovie(const char movieType, int movieStock, const string derName, const string movieName, int releaseYear); // data is set equal to parameter
	virtual ~ComedyMovie(); // virtual destructor

	// Overriding Operator Overloads
	bool operator <(ComedyMovie& other) const;
	bool operator >(ComedyMovie& other) const;
	bool operator ==(ComedyMovie& other) const;
	bool operator !=(ComedyMovie& other) const;
	friend ostream& operator <<(ostream& out, ComedyMovie& other);

private:

};
#endif
