//
//  Movie.h
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
 string getMovieName()     - Returns Movie Title
 string getDirectorName()  - Returns Director's name
 char getMovieType()       - Returns Movie Genre
 int getReleaseYear()      - Returns Released Year
 int getMovieStock()       - Returns Movie DVD stock
 string getMovieDetails()  - Returns string line of "Movie Name: " + movieName + " by " + directorName;
 bool Return()             - Adds the movie stock for returning borrowed DVD
 bool borrow()             - Subtracts the movie stock for borrowing DVD
 void addMovieStock()      - Adds the movie stock, if the movie is already existed during the inserting movie data(Duplicated)
 
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 Default Operator Overloads
 ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- ------- -------
 If the new derived movie classes don't have the overrided operator overloads, these will be executed.
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
 - This class is the Abstract Class. It contains the core functions & key data that every child movie class requires.
 
 Assumption
 -  Assuming that the movie data file is formatted in a given way by professor.
 
 */
// --------------------------------------------------------------------------------------------------------------------

#ifndef Movie_h
#define Movie_h
#include <iostream>

using namespace std;
class Movie
{
public:
	// Constructor & Destructor
	Movie(); // Default constructor
	Movie(char mType, int mStock, string dName, string mName, int relYear); // data is set equal to parameter
	virtual ~Movie(); // Virtual destructor

	// Getter Function
	string getMovieName()const; // returns Movie Title
	string getDirectorName()const; // returns Director's name
	char getMovieType()const; // returns Movie Genre
	int getReleaseYear()const; // returns Released Year
	int getMovieStock()const; // returns Movie DVD stock
	string getMovieDetails() const; // returns string line of "Movie Name: " + movieName + " by " + directorName;
	bool Return(); // adds the movie stock for returning borrowed DVD
	bool borrow(); // subtracts the movie stock for borrowing DVD

	// Setter Function
    void addMovieStock(int stock); // adds the movie stock, if the movie is already existed(Duplicated)
    
    // Default operator overloads
    // These will be used only if the new derived movie class doesn't have over-written operators
	virtual bool operator <(Movie& other) const;
	virtual bool operator >(Movie& other) const;
	virtual bool operator !=(Movie& other) const;
	virtual bool operator ==(Movie& other) const;

protected:
	string movieName; // Movie Title
	string directorName; // Director's name of the movie
	char movieType; // Movie Genre
	int releaseYear; // Released Year of the movie
	int movieStock; // DvD Stock of the movie
    int fmovieStock;
};

#endif 
