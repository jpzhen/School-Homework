//
//  ClassicMovie.h
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
 Getter & Setter
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 string getMaFirstName() - returns Major Actor's First Name
 string getMaLastName()  - returns Major Actor's Last Name
 int getReleaseMonth()   - returns Released Month
 
 
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 Overriding Operator Overloads
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 The Classic Movie is sorted by the released date( Month / Year) and name of the Major Actor in the movie
 The comparisons are based on the released date( Month / Year) and name of the Major Actor in the movie
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
 - The Classic Movie class is a child class of the Movie class. It has the access to the parents class's public functions and protected data
 - When "cout <<," the first two information are one that used on sorting. Rest of the information will be printed inisde of the bracket.

 Assumption
 -  Assuming that the movie data file is formatted in a given way by professor.
 
 */
// --------------------------------------------------------------------------------------------------------------------
#include"Movie.h"
#ifndef ClassicMovie_h
#define ClassicMovie_h

class ClassicMovie : public Movie
{
public:
	// Constructor & Destructor
	ClassicMovie(); // default constructor
	ClassicMovie(const char movieType, int movieStock, const string derName, const string movieName, const string majFname, const string majLname, int releaseMonth, int releaseYear); // data is set equal to parameter
	virtual ~ClassicMovie(); // virtual destructor

	// Getter Function
	string getMaFirstName() const; // returns Major Actor's First Name
	string getMaLastName() const; // returns Major Actor's Last Name
	int getReleaseMonth() const; // returns Released Month

	// Operator Overloads
	bool operator <(ClassicMovie& other) const;
	bool operator >(ClassicMovie& other) const;
	bool operator ==(ClassicMovie& other) const;
	bool operator !=(ClassicMovie& other) const;
	friend ostream& operator <<(ostream& out, ClassicMovie& other);

private:
    // These are the additional key data specifically required for Classic Movies
	int releaseMonth; // released Month
	string maFirtname; // Major Actor's First Name
	string maLastname; // Major Actor's Last Name
};
#endif
