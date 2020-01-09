//
//  ComedyMovie.cpp
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
 - This ComedyMovie class is a child class of the Movie class. It has the access to the parents class's public functions and protected data
 - When "cout <<," the first two information are one that used on sorting. Rest of the information will be printed inisde of the bracket.

 Assumption
 -  Assuming that the movie data file is formatted in a given way by professor.
 
 */
// --------------------------------------------------------------------------------------------------------------------
//
#include "ComedyMovie.h"
#include <stdio.h>

/*-------------------Default Constructor--------------------------*/
// Describtion
// - Constructs the object with default setting
//
// Preconditions: No parameters are passed in.
// Postconditions: The data variables are set as default value.
ComedyMovie::ComedyMovie()
{
	movieName = "";
	directorName = "";
	movieType = 0;
	releaseYear = 0;
	movieStock = 0;
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
ComedyMovie::ComedyMovie(const char movieType, int movieStock, const string derName, const string movieName, int releaseYear) :Movie(movieType, movieStock, derName, movieName, releaseYear)
{

};
// end of Constructor
/*---------------------------------------------------------*/

/*------------------- Virtual Destructor --------------------------*/
// Describtion
// - Needed so movie data are deleted properly
//
// Preconditions: No parameters are passed in
// Postconditions: Will be deleted by BST
ComedyMovie::~ComedyMovie()
{
	// delete all the movie data
	// delete all the allocated memories
}
// end of Destructor
/*---------------------------------------------------------*/


/*-------------------operator <()--------------------------*/
// Describtion
// - Compares by title of the Comedy movie and released year
//
// Preconditions: Address of the other Comedy movie object is passed in
// Postconditions: Compares it by the Comedy movie title and the released year
bool ComedyMovie::operator <(ComedyMovie& other) const
{
	// checks general edge case
	if (other.getMovieName() == "")
	{
		return false;
	}
	else
	{
		// if Title is different
		// sort by Title
		if (movieName != other.getMovieName())
		{
			if (this->movieName < other.getMovieName())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		// if Title is identicle
		// then sort by released year
		else
		{
			if (releaseYear < other.getReleaseYear())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}
// end of operator <()
/*---------------------------------------------------------*/

/*-------------------operator >()--------------------------*/
// Describtion
// - Compares by title of the Comedy movie and released year
//
// Preconditions: Address of the other Comedy movie object is passed in
// Postconditions: Compares it by the Comedy movie title and the released year
bool ComedyMovie::operator >(ComedyMovie& other) const
{
	// checks general edge case
	if (other.getMovieName() == "")
	{
		return false;
	}
	else
	{
		// if Title is different
		// just sort by Title
		if (movieName != other.getMovieName())
		{
			if (this->movieName > other.getMovieName())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		// if Title is identicle
		// then sort by released year
		else
		{
			if (releaseYear > other.getReleaseYear())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}
// end of operator <()
/*---------------------------------------------------------*/

/*-------------------operator ==()--------------------------*/
// Describtion
// - Compares by title of the Comedy movie and released year
//
// Preconditions: Address of the other Comedy movie object is passed in
// Postconditions: Compares it by the Comedy movie title and the released year

bool ComedyMovie::operator ==(ComedyMovie& other) const
{
	// checks general edge case
	if (other.getMovieName() == "")
	{
		return false;
	}
	else
	{
		// Must check the Title and the released year
		// The movie may have same Title but different released year
		if (this->movieName == other.getMovieName() && this->releaseYear == other.getReleaseYear())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
// end of operator ==()
/*---------------------------------------------------------*/

/*-------------------operator !=()--------------------------*/
// Describtion
// - Compares by title of the Comedy movie and released year
//
// Preconditions: Address of the other Comedy movie object is passed in
// Postconditions: Compares it by the Comedy movie title and the released year
bool ComedyMovie::operator !=(ComedyMovie& other) const
{
	// checks general edge case
	if (other.getMovieName() == "")
	{
		return false;
	}
	else
	{
		// compare the Title
		if (this->movieName != other.getMovieName())
		{
			return true;
		}
		else
		{
			// if the Titles are identicle
			// , compare release year
			if (this->releaseYear != other.getReleaseYear())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}
// end of operator !=()
/*---------------------------------------------------------*/

/*-------------------operator<<()--------------------------*/
// Describtion
// - Overloads the operator <<
// - When the object is casted with cout <<, the following line will be printed
//
// Preconditions: Ostream and ComedMovie object are passed in
// Postconditions: Retrieves data information and print out in the order below
ostream& operator<<(ostream& out, ComedyMovie& other)
{
	out << "Title: " << other.movieName << "    Release Year: " << other.releaseYear << "  ( Director:" << other.directorName << " Type: " << other.movieType <<
		" **Stock: " << other.movieStock << " )" << endl;
	return out;
}
// end of operator<<()
/*---------------------------------------------------------*/

