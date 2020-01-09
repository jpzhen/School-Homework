//
//  DamaMovie.cpp
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
 
 Assumption
 -  Assuming that the movie data file is formatted in a given way by professor.
 
 */
// --------------------------------------------------------------------------------------------------------------------
#include "DramaMovie.h"
#include <stdio.h>

/*-------------------Default Constructor--------------------------*/
// Describtion
// - Constructs the object with default setting
//
// Preconditions: No parameters are passed in.
// Postconditions: The data variables are set as default value.
DramaMovie::DramaMovie()
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
DramaMovie::DramaMovie(const char movieType, int movieStock, const string derName, const string movieName, int releaseYear) :Movie(movieType, movieStock, derName, movieName, releaseYear)
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
DramaMovie::~DramaMovie()
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
bool DramaMovie::operator <(DramaMovie& other) const
{
	// checks general edge case
	if (other.getMovieName() == "")
	{
		return false;
	}
	else
	{
		// Compares by director's name, then Title
		if (directorName != other.getDirectorName())
		{
			if (this->directorName < other.getDirectorName())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		// if Director's name is identicle
		// then sort by movie name(Title)
		else
		{
			if (movieName < other.getMovieName())
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
bool DramaMovie::operator >(DramaMovie& other) const
{
	// checks general edge case
	if (other.getMovieName() == "")
	{
		return false;
	}
	else
	{
		// Compares by director's name, then Title
		if (directorName != other.getDirectorName())
		{
			if (this->directorName > other.getDirectorName())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		// if Director's name is identicle
		// then sort by movie name(Title)
		else
		{
			if (movieName > other.getMovieName())
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
// end of operator >()
/*---------------------------------------------------------*/

/*-------------------operator ==()--------------------------*/
// Describtion
// - Compares by title of the Comedy movie and released year
//
// Preconditions: Address of the other Comedy movie object is passed in
// Postconditions: Compares it by the Comedy movie title and the released year

bool DramaMovie::operator ==(DramaMovie& other) const
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
		if (this->directorName == other.getDirectorName() && this->movieName == other.getMovieName())
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

bool DramaMovie::operator !=(DramaMovie& other) const
{
	// checks general edge case
	if (other.getMovieName() == "")
	{
		return false;
	}
	else
	{
		// Compare director's name
		if (this->directorName != other.getDirectorName())
		{
			return true;
		}
		else
		{
			// if Director's name is identicle
			// compare by movie name(Title)
			if (this->movieName != other.getMovieName())
			{
				return true;
			}
			else
			{
				return false;
			}
		};
	}
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
ostream& operator<<(ostream& out, DramaMovie& other)
{
	out << "Director: " << other.directorName << "   Title: " << other.movieName << "  (Type: " << other.movieType <<
		" Release Year: " << other.releaseYear << " **Stock: " << other.movieStock << " )" << endl;
	return out;
}
// end of operator<<()
/*---------------------------------------------------------*/

