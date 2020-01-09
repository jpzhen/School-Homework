//
//  DamaMovie.h
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
 Overriding Operator Overloads
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 The Drama is sorted by the Director's name and the Title of the movie.
 The comparisons are based on Director's name and the Title of the movie.
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
 - The DramaMovie class is a child class of the Movie class. It has the access to the parents class's public functions and protected data
 - When "cout <<," the first two information are one that used on sorting. Rest of the information will be printed inisde of the bracket.

 
 Assumption
 -  Assuming that the movie data file is formatted in a given way by professor.
 
 */
// --------------------------------------------------------------------------------------------------------------------
#include"Movie.h"
#ifndef DramaMovie_h
#define DramaMovie_h

class DramaMovie : public Movie
{
public:
	// Constructor & Destructor
	DramaMovie(); // default constructor
	DramaMovie(const char movieType, int movieStock, const string derName, const string movieName, int releaseYear); // data is set equal to parameter
	virtual ~DramaMovie();

	// Operator Overloads
	bool operator <(DramaMovie& other) const;
	bool operator >(DramaMovie& other) const;
	bool operator ==(DramaMovie& other) const;
	bool operator !=(DramaMovie& other) const;
	friend ostream& operator <<(ostream& out, DramaMovie& other);

private:
	

};

#endif
