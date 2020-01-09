// ------------------------------------------------ polynomial.h -------------------------------------------------------
// Jun Zhen CSS343 Section A
// Creation Date: 6/27/19
// Date of Last Modification: 7/1/19
// --------------------------------------------------------------------------------------------------------------------
// Purpose - header file that will outline the main functions and fields of the circular doubly linked list
// -------------------------------------------------------------------------------------------------------------------- 

// A Polynomial class                              
#ifndef POLYNOMIAL_H                            
#define POLYNOMIAL_H
#include <iostream>
#include <string>
using namespace std;


class Polynomial {
	//Overloaded <<: prints Cn * x^n + Cn-1 * X^n-1 + ... C1 * X + C0
	friend ostream& operator<<(ostream& output, const Polynomial& p);
	// Constructor: the default is a 0-degree polynomial with 0.0 coefficient
public:
	// Member functions
	Polynomial();
	Polynomial(const Polynomial& p);
	~Polynomial();
	int degree() const; // returns the degree of a polynomial
	double coefficient(const int power) const;
	// returns the coefficient of the x^power term.
	bool changeCoefficient(const double newCoefficient, const int power);
	// replaces the coefficient of the x^power term

	// Arithmetic operators
	Polynomial operator+(const Polynomial& p) const;
	Polynomial operator-(const Polynomial& p) const;

	//// Boolean comparison operators
	bool operator==(const Polynomial& p) const;
	bool operator!=(const Polynomial& p) const;

	//// Assignment operators
	Polynomial& operator=(const Polynomial& p);
	Polynomial& operator+=(const Polynomial& p);
	Polynomial& operator-=(const Polynomial& p);
	
private:
	struct Term 
	{     // a term on the sparce polynomial
		double coeff;   // the coefficient of each term
		int power;      // the degree of each term
		Term* prev;     // a pointer to the previous higher term
		Term* next;     // a pointer to the next lower term
		Term(double c = 0.0, int p = 0, Term * pr = NULL, Term * ne = NULL) {
			coeff = c;
			power = p;
			prev = pr;
			next = ne;
		}
	};
	int size;         // # terms in the sparce polynomial
	Term* head;       // a pointer to the doubly-linked circular list of
					  // sparce polynomial
	bool insert(Term* pos, const double newCoefficient, const int power);
	bool remove(Term* pos); //  void print( const string& msg ) const;
	bool findTerm(int power, Term*& holder);
};

#endif
