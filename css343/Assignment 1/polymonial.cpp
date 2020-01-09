// ------------------------------------------------ polynomial.cpp -------------------------------------------------------
// Jun Zhen CSS343 Section A
// Creation Date: 6/27/19
// Date of Last Modification: 7/1/19
// --------------------------------------------------------------------------------------------------------------------
// Purpose - Creating a ciricular doubly linked list that repsent a polynomial function
// -------------------------------------------------------------------------------------------------------------------- 
// Specifiaction - The driver will take in a coefficiant and power and attach it our linked list
// --------------------------------------------------------------------------------------------------------------------
#include "polymonial.h"

// ------------------------------------Polynomial----------------------------------------------- 
// Description
// Polynomial: Default constructer
// precondition: Default constructor that takes no argument in the paramenter
// [ostcondition: Initialize a dummy node that have no values and have the head pointer point to it
// -------------------------------------------------------------------------------------------- 
Polynomial::Polynomial()
{
	//Dummy Node
	Term* dummy = new Term(0.0,0);
	head = dummy;
	head->next = head;
	head->prev = head;
	size = 0;
}
//end of Polynomial()

//Precondition: After main is finished running, the destrcutor will run
//Postcondition: This destructor will free up all dynamic allocated memories
Polynomial::Polynomial(const Polynomial& p)
{
	Term* dummy = new Term(0.0, 0);
	head = dummy;
	head->next = head;
	head->prev = head;
	size = 0;
	*this = p;
}
//end of Polynomial(const Polynomial)

// ------------------------------------~Polynomial-----------------------------------------------
// Description
// - ~Polynomial() : destructor, clears all the data from the objects at the end.
// preconditions: no parameters needed.
// postconditions:  no parameters gets passed in. The destructor delets every objects until it is empty
// --------------------------------------------------------------------------------------------
Polynomial::~Polynomial()
{
	if (head != NULL)
	{
		while (size != 0) 
		{
			this->remove(head->next);
		}
		remove(head);
	}
}
//end of ~Polynomial()

// ------------------------------------degree----------------------------------------------- 
// Description
// degree: Find the highest term's power
// precondition: Take in no argument, but the list must contain 
// postcondition: Return the highest dregree of this polymonial function
// -------------------------------------------------------------------------------------------- 
int Polynomial::degree() const
{
	if (size != 0)
	{
		return head->next->power;
	}
	else
	{
		return head->power;
	}
}
//end of degree()

// ------------------------------------coefficient----------------------------------------------- 
// Description
// coefficient: Find the coefficiant of the term based on the power of the term
// precondition: Take in a power related to a coefficenet
// postcondition: Return the coefficient based on the power
// -------------------------------------------------------------------------------------------- 
double Polynomial::coefficient(const int power) const
{
	int tempSize = size;
	Term* current = head->next;
	while (tempSize != 0) {
		if (current->power == power) 
		{
			return current->coeff;
		}
		current = current->next;
	}
	return 0.0;
}
//end of coefficient (const int power) const

// ------------------------------------changeCoefficient----------------------------------------------- 
// Description
// changeCoefficient: Change the coefficant of the term based on the given power 
// preconditions: Take in the double for coeff and int for power
// postconditions: If the coefficient is zero, remove that term, but insert a new term if there is no corrsponding power
// -------------------------------------------------------------------------------------------- 
bool Polynomial::changeCoefficient(const double newCoefficient, const int power)
{
	Term* current = head;
	int tempSize = size;
	if (newCoefficient == 0) 
	{
		current = head->next;
		while (tempSize != 0) 
		{
			if (current->power == power) 
			{
				this->remove(current);
				return true;
			}
			current = current->next;
			tempSize--;
		}
		return false;
	}
	else 
	{
		while (tempSize != 0) 
		{
			if (current->next->power == power) 
			{
				current->next->coeff = newCoefficient;
				return true;
			}
			else if (current->next->power < power) 
			{
				this->insert(current, newCoefficient, power);
				return true;
			}
			current = current->next;
			tempSize--;
		}
		this->insert(current, newCoefficient, power);
		return true;
	}
	return false;
}
//end of changeCoefficient(const double newCoefficient, const int power)

// Arithmetic operators
// ------------------------------------ operator+-----------------------------------------------
// Description
// - operator+ : Operator overload + adds the two Polynomial, 2nd polynomial from the 1st one.
// preconditions: The &p is the value of the polynomials.
// postconditions:  The left side of the polynomial gets copied to the new object, and then return the object
// --------------------------------------------------------------------------------------------
Polynomial Polynomial::operator+(const Polynomial& p) const
{
	return Polynomial(*this) += p;
}
//end of operator+

// ------------------------------------ operator- -----------------------------------------------
// Description
// operator- : Operator overload - subtracts the two Polynomials, 2nd polynomial from the 1st one.
// preconditions: The &p is the value of the polynomials.
// postconditions:  The left side of the polynomial gets copied to the new object, and then return the object
// --------------------------------------------------------------------------------------------
Polynomial Polynomial::operator-(const Polynomial& p) const
{
	return Polynomial(*this) -= p;
}
//end of operator-

// Boolean comparison operators
// ------------------------------------operator=-----------------------------------------------
// Description
// operator ==: Overload the == operator to check if two objects are identicle.
// preconditions: The operand's must contain values.
// postconditions: Returns true if two objects are identicle.
// --------------------------------------------------------------------------------------------
bool Polynomial::operator==(const Polynomial& p) const
{
	Term* current = head->next;
	Term* otherCurrent = p.head->next;
	if (this->size != p.size)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			if (current->coeff != otherCurrent->coeff || current->power != otherCurrent->power)
			{
				return false;
			}
			current = current->next;
			otherCurrent = otherCurrent->next;
		}
		return true;
	}
}
//end of operator==

// ------------------------------------operator!= -----------------------------------------------
// Description
// operator !=: Overload the != operator to check if two objects are unidenticle.
// preconditions: The operand's must contain values.
// postconditions: Returns true if two Polynomials are unidenticle.
// --------------------------------------------------------------------------------------------
bool Polynomial::operator!=(const Polynomial& p) const
{
	return (!(*this == p));
}
//end of operator!=

// Assignment operators
// ------------------------------------operator= -----------------------------------------------
// Description
// operator =: Overload the = operator to copy and assign objects
// preconditions: The operand's must contain values
// postconditions: Return the object with values copied from the parameter object
// --------------------------------------------------------------------------------------------
Polynomial& Polynomial::operator=(const Polynomial& p)
{
	if (*this != p)
	{
		while (size != 0)
		{
			this->remove(head->next);
		}
		Term* otherCurrent = p.head->next;
		for (int i = 0; i < p.size; i++)
		{
			this->changeCoefficient(otherCurrent->coeff, otherCurrent->power);
			otherCurrent= otherCurrent->next;
		}
	}
	return *this;
}
//end of operator=

// ------------------------------------operator +=----------------------------------------------- 
// Description
// operator +=: Overload the += operator to add and assign objects
// preconditions: The operand's must contain values
// postconditions: Return the object with values added from the parameter object
// -------------------------------------------------------------------------------------------- 
Polynomial& Polynomial::operator+=(const Polynomial& p)
{
	if (p.size == 0)
	{
		return *this;
	}
	else
	{
		Term* otherCurrent = p.head->next;
		for (int i = 0; i < p.size; i++)
		{
			Term* holder = NULL;
			{
				if (findTerm(otherCurrent->power, holder))
				{
					this->changeCoefficient(otherCurrent->coeff + holder->coeff, otherCurrent->power);
				}
				else
				{
					this->changeCoefficient(otherCurrent->coeff, otherCurrent->power);
				}
			}
			otherCurrent = otherCurrent->next;
		}
		return *this;
	}
}
//end of operator +=

// ------------------------------------operator -=----------------------------------------------- 
// Description
// operator -=: Overload the -= operator to subtract and assign objects
// preconditions: The operand's must contain values
// postconditions: Return the object with values subtracted from the parameter object
// -------------------------------------------------------------------------------------------- 
Polynomial& Polynomial::operator-=(const Polynomial& p)
{
	if (p.size == 0)
	{
		return *this;
	}
	else
	{
		Term* otherCurrent = p.head->next;
		for (int i = 0; i < p.size; i++)
		{
			Term* holder = NULL;
			{
				if (findTerm(otherCurrent->power, holder))
				{
					this->changeCoefficient(holder->coeff - otherCurrent->coeff, otherCurrent->power);
				}
				else
				{
					this->changeCoefficient(-otherCurrent->coeff, otherCurrent->power);
				}
			}
			otherCurrent = otherCurrent->next;
		}
		return *this;
	}
}
//end of operator -=

// ------------------------------------Operator <<----------------------------------------------- 
// Description
// Operator <<: Overload the << operator to print out the all linked list's value
// preconditions: The linked list must contain values in it
// postconditions: All the values in linked list will be formated and printed out on console 
// -------------------------------------------------------------------------------------------- 
ostream& operator<<(ostream& output, const Polynomial& p)
{
	Polynomial::Term* current = p.head->next;
	if (p.size != 0)
	{
		if (current->power == 1 && current->coeff == 1)
		{
			if (current->coeff < 0)
			{
				output << "-x";
				current = current->next;
			}
			else
			{
				output << "x";
				current = current->next;
			}
		}
		else if (current->power == 1)
		{
			output << current->coeff << "x";
			current = current->next;

		}
		else if (current->power == 0)
		{
			output << current->coeff;
			current = current->next;
		}
		else
		{
			output << current->coeff << "x^" << current->power;
			current = current->next;
		}
		while (current != p.head)
		{
			if (current->coeff < 0)
			{
				if (current->power == 1 && current->coeff == 1)
				{
					output << "-x";
					current = current->next;
				}
				else if (current->power == 1)
				{

					output << current->coeff << "x";
					current = current->next;


				}
				else if (current->power == 0)
				{
					output << current->coeff;
					current = current->next;
				}
				else
				{
					output << current->coeff << "x^" << current->power;
					current = current->next;
				}
			}
			else
			{
				if (current->power == 1 && current->coeff == 1)
				{
					output << " + x";
					current = current->next;
				}
				else if (current->power == 1)
				{
					output << " + " << current->coeff << "x";
					current = current->next;
				}
				else if (current->power == 0)
				{
					output << " + " << current->coeff;
					current = current->next;
				}
				else
				{
					output << " + " << current->coeff << "x^" << current->power;
					current = current->next;
				}
			}
		}
	}
	return output;
}
//end of operator <<

// ------------------------------------insert----------------------------------------------- 
// Description
// insert: Given a location and value, generate a new node and attach to the link list  
// preconditions: Parameter pointer must be pointing to a linked list with other nodes
// postconditions: Return true if sucessfully insert a new node with given value
// -------------------------------------------------------------------------------------------- 
bool Polynomial::insert(Term* pos, const double newCoefficient, const int power)
{
	if (pos != NULL)
	{
		Term* temp = new Term(newCoefficient, power);
		temp->next = pos->next;
		temp->prev = pos;
		pos->next->prev = temp;
		pos->next = temp;
		size++;
		return true;
	}
	else
	{
		return false;
	}
}
//end of insert()

// ------------------------------------remove----------------------------------------------- 
// Description
// remove: Given a location, remove that node. Return true if sucessfully removed, return false if not.
// preconditions: Parameter address must be point to a node on a linked list
// postconditions: Deallocate the node by using delete and setting its pointer to NULL
// -------------------------------------------------------------------------------------------- 
bool Polynomial::remove(Term* pos)
{
	if (size == 0) 
	{
		pos->next = NULL;
		pos->prev = NULL;
//		cout << "deleting" << pos->coeff << endl;
		delete pos;
		return true;
	}
	else 
	{
		pos->prev->next = pos->next;
		pos->next->prev = pos->prev;
		pos->next = NULL;
		pos->prev = NULL;
	//	cout << "deleting" << pos->coeff << endl;
		delete pos;
		size--;
		return true;
	}
	return false;
}
//end of remove()

// ------------------------------------findTerm----------------------------------------------- 
// Description
// findTerm: Given a value, find the location based on that value return true if found, return false if not found
// preconditions: the pointer variable must NULL and value must be an int
// postconditions: point the parameter pointer to the found address 
// -------------------------------------------------------------------------------------------- 
bool Polynomial::findTerm(int power, Term*& holder)
{
	Term* current = head->next;
	for (int i = 0; i < size; i++)
	{
		if (current->power == power)
		{
			holder = current;
			return true;
		}
		current = current->next;
	}
	holder = NULL;
	return false;
}
//end of findTerm()
