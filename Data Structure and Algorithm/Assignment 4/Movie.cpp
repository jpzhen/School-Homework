//
//  Movie.cpp
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

#include <stdio.h>
#include "Movie.h"
using namespace std;

/*-------------------Default Constructor--------------------------*/
// Describtion
// - Constructs the object with default setting
//
// Preconditions: No parameters are passed in.
// Postconditions: The data variables are set as default value.
Movie::Movie()
{
	movieName = "";
	directorName = "";
	movieType = 0;
	releaseYear = 0;
	movieStock = 0;
    fmovieStock = 0;
};
// end of Default Constructor
/*---------------------------------------------------------*/

/*------------------- Casting datas to Constructor --------------------------*/
// Describtion
// - Constructs a object with the following parameters saved in to the data variables
//
// Preconditions: Character of movie genre, integer of movie stock, string of director name
//                string of movie title, and integer of released year are passed in as parameter.
// Postconditions: The parameters are saved into the data variables by a given structure.
Movie::Movie(char mType, int mStock, string dName, string mName, int relYear)
{
	movieName = mName;
	directorName = dName;
	movieType = mType;
	releaseYear = relYear;
	movieStock = mStock;
    fmovieStock = movieStock;
};
// end of Constructor
/*---------------------------------------------------------*/

/*------------------- Virtual Destructor --------------------------*/
// Describtion
// - Needed so movie data are deleted properly
//
// Preconditions: No parameters are passed in
// Postconditions: Will be deleted by BST
Movie::~Movie()
{

}
// end of Destructor
/*---------------------------------------------------------*/

/*-------------------getMovieName()--------------------------*/
// Describtion
// - returns the Title of the movie
//
// Preconditions: No parameters are passed in
// Postconditions: Returns the title of the movie
string Movie::getMovieName() const
{
	return this->movieName;
}
// end of getMovieName
/*---------------------------------------------------------*/

/*-------------------getDirectorName()--------------------------*/
// Describtion
// - returns the Director's name of the movie
//
// Preconditions: No parameters are passed in
// Postconditions: Returns the Director's name
string Movie::getDirectorName() const
{
	return directorName;
}
// end of getMovieName
/*---------------------------------------------------------*/


/*-------------------getMovieType()--------------------------*/
// Describtion
// - returns the Movie genre
//
// Preconditions: No parameters are passed in
// Postconditions: Returns the movie genre
char Movie::getMovieType() const
{
	return this->movieType;
}
// end of getMovieType
/*---------------------------------------------------------*/

/*-------------------getReleaseYear()--------------------------*/
// Describtion
// - returns the released year
//
// Preconditions: No parameters are passed in
// Postconditions: Returns the released year
int Movie::getReleaseYear() const
{
	return this->releaseYear;
}
// end of getReleaseYear
/*---------------------------------------------------------*/

/*-------------------getMovieStock()--------------------------*/
// Describtion
// - returns the dvd stock of the movie
//
// Preconditions: No parameters are passed in
// Postconditions: Returns the dvd stock of the movie
int Movie::getMovieStock() const
{
	return this->movieStock;
}
// end of getMovieStock
/*---------------------------------------------------------*/

/*-------------------getMovieDetails()--------------------------*/
// Describtion
// - returns string line of the following information listed below
//
// Preconditions: No parameters are passed in
// Postconditions: Returns the movie title and director's name in string line
string Movie::getMovieDetails() const
{
    return "Movie Name: " + movieName + " by " + directorName;
}
// end of getMovieDetails
/*---------------------------------------------------------*/

/*-------------------Return()--------------------------*/
// Describtion
// - adds the movie stock for returning the borrowed dvd
//
// Preconditions: No parameters are passed in
// Postconditions: If the movie stock is not negative, adds the stock for returning dvd.
bool Movie::Return()
{
    if (movieStock < fmovieStock)
    {
        movieStock++;
        return true;
    }
    else
    {
        cout << "MOVIE NOT FROM THE STORE" << endl;
        return false;
    }
};
// end of addMovieStock
/*---------------------------------------------------------*/

/*-------------------borrow()--------------------------*/
// Describtion
// - subtracts the movie stock for borrowing dvd
//
// Preconditions: No parameters are passed in
// Postconditions: If the movie stock is enough to rent it, subtracts the stock for borrowing dvd.
bool Movie::borrow()
{
	if (!(movieStock <= 0))
	{
		movieStock--;
		return true;
	}
	else
	{
		cout << "TRANSACTION DENIED! " <<  movieName << " stock: " << movieStock << endl;
		return false;
	}
};
// end of subtractMovieStock
/*---------------------------------------------------------*/

/*-------------------addMovieStock()--------------------------*/
// Describtion
// - adds movie stock if there is a duplicated one during the
//   inserting the movie data into the BST.
//
// Preconditions: The stock number is passed in as integer
// Postconditions: Adds the movie stock and update.
void Movie::addMovieStock(int stock)
{
    movieStock += stock;
};
// end of addMovieStock
/*---------------------------------------------------------*/

/*-------------------operator <()--------------------------*/
// Describtion
// - Compares by title of the movie and released year
//
// Preconditions: Address of the other movie object is passed in
// Postconditions: Compares it by the movie title and the released year
bool Movie::operator <(Movie& other) const
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
// - Compares by title of the movie and released year
//
// Preconditions: Address of the other movie object is passed in
// Postconditions: Compares it by the movie title and the released year
bool Movie::operator >(Movie& other) const
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
// - Compares by title of the movie and released year
//
// Preconditions: Address of the other movie object is passed in
// Postconditions: Compares it by the movie title and the released year

bool Movie::operator ==(Movie& other) const
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
// - Compares by title of the movie and released year
//
// Preconditions: Address of the other movie object is passed in
// Postconditions: Compares it by the movie title and the released year
bool Movie::operator !=(Movie& other) const
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
