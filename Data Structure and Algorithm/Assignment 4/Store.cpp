//
//  Store.cpp
//  FinalProject
//
//  Created by Jun zhen and kwontaeyoung on 8/15/19.
//  Copyright � 2019 Jun.Zhen&Tae.Y.Kwon. All rights reserved.
//
//
// -------------------------------------------------------------------------------------------------------
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
 
 */
// --------------------------------------------------------------------------------------------------------------------

#include "Store.h"

/*-------------------Default Constructor--------------------------*/
// Describtion
// - Constructs the object with default setting
//
// Preconditions: No parameters are passed in.
// Postconditions: The data variables are set as default value.
Store::Store()
{
    comedyBST;
    dramaBST;
    classicBST;
    accountTable;
}
// end of Constructor
/*---------------------------------------------------------*/

/*-------------------Destructor--------------------------*/
// Describtion
// - needed to delete store object.
//
// Preconditions: No parameters are passed in.
// Postconditions: Deletes the Store object
Store::~Store()
{
}
// end of Destructor
/*---------------------------------------------------------*/

/*-------------------readMovieFile--------------------------*/
// Describtion
// - Reads the movie data file, and retrieves the information.
//   the retrieved data are saved in to one of the data container
//   according to the movie genre
//
// Preconditions: name of the file is passed in
// Postconditions: reads the line until the end of the file
bool Store::readMovieFile(string fileName)
{
    ifstream moviedata(fileName);
    
    // general edge case
    if (!moviedata)
    {
        cout << "File could not be opened." << endl;
        return false;
    }
    // reads till the end of file
    for (;;)
    {
        // data that are required to be retrieved from the file
        char type, comma;
        string directorName, skip, title, fname, lname;
        int stock, month, year;
        
        // always the first character of the line is the movie genre
        moviedata >> type >> comma;
        
        // break if it reach end of the file
        if (moviedata.eof())
        {
            break;
        }
        // Classic Movie
        if (type == 'C')
        {
            moviedata >> stock >> comma;
            getline(moviedata, directorName, ',');
            getline(moviedata, title, ',');
            moviedata >> fname >> lname >> month >> year;
            // ------------------------------------------
            // Here we can create memory of Classic Movie
            // and insert it into Classic Movie BST
            ClassicMovie cm(type, stock, directorName, title, fname, lname, month, year);
            classicBST.insert(cm);
            // ------------------------------------------
        }
        // Drama Movie and Comedy Movie
        else if (type == 'D' || type == 'F')
        {
            moviedata >> stock >> comma;
            getline(moviedata, directorName, ',');
            getline(moviedata, title, ',');
            moviedata >> year;
            // ------------------------------------------
            // Here we can create memory of Classic Movie
            // and insert it into Classic Movie BST
            if (type == 'F')
            {
                ComedyMovie fm(type, stock, directorName, title, year);
                comedyBST.insert(fm);
            }
            if (type == 'D')
            {
                DramaMovie dm(type, stock, directorName, title, year);
                dramaBST.insert(dm);
            }
        }
        else
        {
            // if the movie genre is not either C, F, or D, throw error code
            getline(moviedata, skip);
            cout << "------------------------------------------------------------------------------" << endl;
            cout << endl;
            cout << "Invalid input from Movie Data" << endl;
            cout << type << ", " << skip << endl;
            cout << "------------------------------------------------------------------------------" << endl;
        }
    }
    return true;
}
// end of readMovieFile
/*---------------------------------------------------------*/

/*-------------------readCustomerFile--------------------------*/
// Describtion
// - Reads the customer data file, and retrieves the information.
//   The retrieved data are saved in to customer object then saved into
//   the HashTable
//
// Preconditions: name of the file is passed in
// Postconditions: reads the line until the end of the file
bool Store::readCustomerFile(string fileName)
{
    ifstream customerData(fileName);
    // first general edge case
    if (!customerData)
    {
        cout << "File could not be opened." << endl;
        return false;
    }
    // Processing the customers data in following order
    // Account Number, First Name, Last Name
    for (;;)
    {
        // Account Number, First Name, Last Name
        int accountNumber = 0;
        string firstName, lastName, skip;
        
        customerData >> accountNumber;
        
        // breaks if it reaches end of the file
        if (customerData.eof())
        {
            break;
        }
        // if Account Number is less than 0, return false
        if (accountNumber < 0 && accountNumber > 9999)
        {
            getline(customerData, skip);
        }
        else
        {
            // ------------------------------------------
            // Here we can insert into the HashTable
            // The customer data is followed by account number, last name and first name.
            customerData >> lastName >> firstName;
            Customer c(accountNumber, firstName, lastName);
            accountTable.insert(&c);
            // ------------------------------------------
        }
    }
    return true;
}
// end of readCustomerFile
/*---------------------------------------------------------*/


/*-------------------readCommandFile--------------------------*/
// Describtion
// - Reads the Command data file, and retrieves the information.
//   The retrieved data are executed accordingly based on the command.
//
// Preconditions: name of the file is passed in
// Postconditions: reads the line until the end of the file
bool Store::readCommandFile(string fileName)
{
    ifstream commandData(fileName);
    // first general edge case
    if (!commandData)
    {
        cout << "File could not be opened." << endl;
        return false;
    }
    // reads until the end of the file
    for (;;)
    {
        // These are the information we can retrieve from the command data file
        string command;
        int accountNumber;
        string skip;
        Customer* cHolder = NULL;
        
        // reads the first letter of the line, which is the command
        commandData >> command;
        
        // break if it reaches end of the file
        if (commandData.eof())
        {
            break;
        }
        // Inventory for DvD stock
        if (command == "I")
        {
            cout << "Print current inventory of DVD stocks." << endl;
            this->inventory();
            
        }
        // History, displays Customer's transaction
        else if (command == "H")
        {
            commandData >> accountNumber;
            if (accountNumber < 1000 || accountNumber > 9999 || accountTable.exist(accountNumber))
            {
                cout << "Print the history of " << accountNumber << " customer." << endl;
                accountTable.getHistory(accountNumber);
            }
            else
            {
                cout << "ACCOUNT NOT FOUND: " << accountNumber << endl;
            }
        }
        // Borrow & Return
        else if (command == "B" || command == "R")
        {
            // These are the data required for the B & R command
            // Media Type, Movie Genre
            string mediaType, movieType;
            // Retrieving account number
            commandData >> accountNumber;
            
            // finding the customer
            if (accountNumber < 1000 || accountNumber > 9999 || accountTable.retrieve(accountNumber, cHolder))
            {
                // getting media type
                // Only, D(DvD) is considered in this project
                commandData >> mediaType;
                if (mediaType == "D")
                {
                    // getting movie genre
                    commandData >> movieType;
                    // Comedy Movie
                    if (movieType == "F")
                    {
                        // getting information for comedy movie
                        string title;
                        int releaseYear;
                        getline(commandData, title, ',');
                        if (commandData >> releaseYear)
                        {
                            // this is for retrieving information
                            ComedyMovie* fholder = NULL;
                            
                            // if movie is found, execute Borrow or Return based on the command
                            if (comedyBST.retrieve(title, releaseYear, fholder))
                            {
                                // if B, execute Borrow Dvd
                                if (command == "B")
                                {
                                    fholder->borrow();
                                }
                                // if R, execute Return Dvd
                                else if (command == "R")
                                {
                                    fholder->Return();
                                }
                                // Tracks customer's transaction
                                // by sending string line
                                cHolder->trackRecords(" " + command + " " + to_string(accountNumber) + " " + mediaType + " " + movieType + title + " " + to_string(releaseYear));
                            }
                            else
                            {
                                // if the movie does not exist, throw an error
                                cout << "NOT A VALID MOVIE TITLE: " << title << endl;
                            }
                        }
                        else
                        {
                            cout << "INVALID INPUT" << endl;
                            commandData.clear();
                            getline(commandData, skip);
                        }
                    }
                    // if drama movie
                    else if (movieType == "D")
                    {
                        // information required for Drama Movie
                        string director, title;
                        getline(commandData, director, ',');
                        getline(commandData, title, ',');
                        // for retrieving drama movie from data container
                        DramaMovie* dHolder = NULL;
                        
                        // if movie exist
                        if (dramaBST.retrieve(director, title, dHolder))
                        {
                            // if B, execute borrow
                            if (command == "B")
                            {
                                dHolder->borrow();
                            }
                            // if R, execute Return
                            else if (command == "R")
                            {
                                dHolder->Return();
                            }
                            // saving customer's transaction history
                            cHolder->trackRecords(" " + command + " " + to_string(accountNumber) + " " + mediaType + " " + movieType + title + director);
                        }
                        else
                        {
                            // if the movie does not exist throw an error code
                            cout << "NOT A VALID MOVIE TITLE: " << title << endl;
                        }
                    }
                    // if it's classic movie
                    else if (movieType == "C")
                    {
                        // retrieving information required for Classic Movie
                        int releaseMonth, releaseYear;
                        string maFirstName, maLastName;
                        if ((commandData >> releaseMonth >> releaseYear >> maFirstName >> maLastName))
                        {
                            // for retrieving classic movie from the BST
                            ClassicMovie* clHolder = NULL;
                            ClassicMovie* clHolder2 = NULL;
                            // if the movie exist
                            if (classicBST.retrieve(maFirstName, maLastName, releaseMonth, releaseYear, clHolder))
                            {
                                if (command == "B")
                                {
                                    if (clHolder->getMovieStock() > 0)
                                    {
                                        clHolder->borrow();
                                        cHolder->trackRecords(" " + command + " " + to_string(accountNumber) + " " + mediaType + " " + movieType + " " + maFirstName + " " + maLastName);
                                    }
                                    else if (classicBST.retrieveSame(maFirstName, maLastName, clHolder->getMovieName(), clHolder->getDirectorName(), releaseMonth, releaseYear, clHolder2))
                                    {
										string yesno;
										cout << "No Stock of Movie `" << clHolder->getMovieName() << "' with '" << maFirstName << " " << maLastName << "', would you like the Movie `" << clHolder2->getMovieName() << "' with '" << clHolder2->getMaFirstName() << " " << clHolder2->getMaLastName() << "'? Enter YES or NO (All CAPS)" << endl;
										cin >> yesno;
										if (yesno == "YES")
										{
											clHolder2->borrow();
											cHolder->trackRecords(" " + command + " " + to_string(accountNumber) + " " + mediaType + " " + movieType + " " + clHolder2->getMaFirstName() + " " + clHolder2->getMaLastName());
										}
                                    }
                                    else
                                    {
                                        cout << "TRANSACTION DENIED! " << clHolder->getMovieName() << " stock: " << clHolder->getMovieStock() << endl;
                                    }
                                }
                                // if R, execute return
                                else if (command == "R")
                                {
                                    clHolder->Return();
                                    cHolder->trackRecords(" " + command + " " + to_string(accountNumber) + " " + mediaType + " " + movieType + " " + maFirstName + " " + maLastName);
                                }
                                // save the transaction history
                            }
                            else
                            {
                                cout << "NOT A VALID MOVIE TITLE WITH ACTOR/ACTRESS: " << maFirstName << " " << maLastName << " " << releaseMonth << " " << releaseYear << endl;
                            }
                        }
                        else
                        {
                            cout << "INVALID INPUT" << endl;
                            commandData.clear();
                            getline(commandData, skip);
                        }
                    }
                    else
                    {
                        cout << "The movie genre, " << movieType << ", does not exist" << endl;
                        getline(commandData, skip);
                    }
                }
                else
                {
                    cout << "Currently, we only have DvD available" << endl;
                    getline(commandData, skip);
                }
            }
            else
            {
                cout << "ACCOUNT NOT FOUND: " << accountNumber << endl;
                getline(commandData, skip);
            }
        }
        else
        {
            cout << "Command " << command << " is not available" << endl;
            getline(commandData, skip);
        }
    }
    return 0;
}
// end of readCommandFile
/*---------------------------------------------------------*/


/*-------------------inventory--------------------------*/
// Describtion
// - prints out the inventory of the entire movie stock
//
// Preconditions: No parameter is passed in
// Postconditions: Execute the display function from each movie data container
void Store::inventory()
{
    cout << "\n****** Movie Inventory ******\n" << endl;
    cout << "**************************************************" << endl;
    cout << "Comedy Movie (Sorted by Title, then Released Year)" << endl;
    cout << "**************************************************\n" << endl;
    this->comedyBST.display();
    cout << "********************************************" << endl;
    cout << "Drama Movie (Sorted by Director, then Title)" << endl;
    cout << "********************************************\n" << endl;
    this->dramaBST.display();
    cout << "******************************************************************" << endl;
    cout << "Classic Movie (Sorted by Released Date(mm/yyyy), then Major Actor)" << endl;
    cout << "******************************************************************\n" << endl;
    this->classicBST.display();
}
// end of inventory
/*---------------------------------------------------------*/
