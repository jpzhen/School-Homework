//
//  ClassicMovie.cpp
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
//
#include <stdio.h>
#include "ClassicMovie.h"

/*-------------------Default Constructor--------------------------*/
// Describtion
// - Constructs the object with default setting
//
// Preconditions: No parameters are passed in.
// Postconditions: The data variables are set as default value.
ClassicMovie::ClassicMovie()
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
ClassicMovie::ClassicMovie(const char movieType, int movieStock, const string derName, const string movieName, const string majFname, const string majLname, int releaseMonth, int releaseYear)
:Movie(movieType, movieStock, derName, movieName, releaseYear)
{
    this->releaseMonth = releaseMonth;
    this->maFirtname = majFname;
    this->maLastname = majLname;
};
// end of Constructor
/*---------------------------------------------------------*/

/*------------------- Virtual Destructor --------------------------*/
// Describtion
// - Needed so movie data are deleted properly
//
// Preconditions: No parameters are passed in
// Postconditions: Will be deleted by BST
ClassicMovie::~ClassicMovie()
{
    // delete all the movie data
    // delete all the allocated memories
}
// end of Destructor
/*---------------------------------------------------------*/

/*-------------------getMaFirstName()--------------------------*/
// Describtion
// - returns Major Actor's First Name
//
// Preconditions: No parameters are passed in
// Postconditions: returns Major Actor's first name
string ClassicMovie::getMaFirstName() const
{
    // Only the Classic Movie contains name of the major actor in the movie
    return this->maFirtname;
}
// end of getMaFirstName
/*---------------------------------------------------------*/

/*-------------------getMaLastName()--------------------------*/
// Describtion
// - returns Major Actor's Last Name
//
// Preconditions: No parameters are passed in
// Postconditions: returns Major Actor's last name
string ClassicMovie::getMaLastName() const
{
    // Only the Classic Movie contains name of the major actor in the movie
    return this->maLastname;
}
// end of getMaLastName
/*---------------------------------------------------------*/

/*-------------------getReleaseMonth()--------------------------*/
// Describtion
// The classic movie contains released month in addition to released year.
// - The function returns released month
//
// Preconditions: No parameters are passed in
// Postconditions: returns released month of the movie
int ClassicMovie::getReleaseMonth() const
{
    // Only the Classic Movie contains released month
    return releaseMonth;
}
// end of getMovieType
/*---------------------------------------------------------*/

/*-------------------operator <()--------------------------*/
// Describtion
// - Compares by title of the Comedy movie and released year
//
// Preconditions: Address of the other Comedy movie object is passed in
// Postconditions: Compares it by the Comedy movie title and the released year
bool ClassicMovie::operator <(ClassicMovie& other) const
{
    // checks general edge case
    if (other.releaseMonth == 0)
    {
        return false;
    }
    else
    {
        // compare the year of released date
        if (releaseYear != other.releaseYear)
        {
            if (this->releaseYear < other.releaseYear)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            // if release year is same
            // then compare by released month
            if (this->releaseMonth < other.releaseMonth)
            {
                return true;
            }
            else if (this->releaseMonth == other.releaseMonth)
            {
                // if released dates are identicle
                // then compare by major Actor's last name
                if (maFirtname < other.maFirtname)
                {
                    return true;
                }
                else if(maFirtname == other.maFirtname)
                {
                    if(maLastname < other.maLastname)
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                // the release date is bigger(recent)
                return false;
            }
        }
    }
}
// end of operator <()
/*---------------------------------------------------------*/

/*-------------------operator >()--------------------------*/
// Describtion
// - Compares by title of the Comedy movie and released year
//
// Preconditions: Address of the other Comedy movie object is passed in
// Postconditions: Compares it by the Comedy movie title and the released year
bool ClassicMovie::operator >(ClassicMovie& other) const
{
    // checks general edge case
    if (other.releaseMonth == 0)
    {
        return false;
    }
    else
    {
        // compare the year of released date
        if (releaseYear != other.releaseYear)
        {
            if (this->releaseYear > other.releaseYear)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            // if release year is same
            // then compare by released month
            if (this->releaseMonth > other.releaseMonth)
            {
                return true;
            }
            else if (this->releaseMonth == other.releaseMonth)
            {
                // if released dates are identicle
                // then compare by major Actor's last name
                if (maFirtname > other.maFirtname)
                {
                    return true;
                }
                else if(maFirtname == other.maFirtname)
                {
                    if(maLastname > other.maLastname)
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                // the release date is bigger(recent)
                return false;
            }
        }
    }
}
// end of operator <()
/*---------------------------------------------------------*/

/*-------------------operator ==()--------------------------*/
// Describtion
// - Compares by title of the Comedy movie and released year
//
// Preconditions: Address of the other Comedy movie object is passed in
// Postconditions: Compares it by the Comedy movie title and the released year

bool ClassicMovie::operator ==(ClassicMovie& other) const
{
    // checks general edge case
    if (other.releaseMonth == 0)
    {
        return false;
    }
    else
    {
        // Must check the release year, month, and Major actor's first name and last name
        if (this->releaseYear == other.releaseYear && this->releaseMonth == other.releaseMonth && this->maFirtname == other.maFirtname && this->maLastname == other.maLastname)
        {
            
            return true;
        }
        else return false;
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
bool ClassicMovie::operator !=(ClassicMovie& other) const
{
    // checks general edge case
    if (other.releaseMonth == 0)
    {
        return false;
    }
    else
    {
        // if one of them is different return true
        if (this->releaseYear != other.releaseYear || this->releaseMonth != other.releaseMonth || this->maFirtname != other.maFirtname || this->maLastname != other.maLastname)
        {
            return true;
        }
        else return false;
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
ostream& operator<<(ostream& out, ClassicMovie& other)
{
    out << "Released date: " << other.releaseMonth << " / " << other.releaseYear << "   Major Actor: " << other.maFirtname << " " << other.maLastname << "  ( Title: " << other.movieName << "  Director:" << other.directorName << " Type: " << other.movieType << " **Stock: " << other.movieStock << " )" << endl;
    
    return out;
}
// end of operator<<
/*---------------------------------------------------------*/

