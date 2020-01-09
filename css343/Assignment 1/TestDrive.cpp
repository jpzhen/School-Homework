// ------------------------------------------------ TestDrive.cpp -------------------------------------------------------
// Jun Zhen CSS343 Section A
// Creation Date: 6/27/19
// Date of Last Modification: 7/1/19
// --------------------------------------------------------------------------------------------------------------------
// Purpose - Driver to test every function of the circulary doubly linked list: polynomial
// -------------------------------------------------------------------------------------------------------------------- 
#include"polymonial.h"

int main()
{
	Polynomial p1;
	p1.changeCoefficient(5, 1);
	p1.changeCoefficient(2, 4);
	p1.changeCoefficient(2.2, 2);
	p1.changeCoefficient(-3.8, 3);
	cout << "p1 = " << p1 << endl;

	p1.changeCoefficient(0, 2);
	cout << "Test for changeCoefficient(0,2), with p1: " << "p1 = " << p1 << endl;

	Polynomial p2;
	cout << "p2 = " << p2 << endl;
	cout << "Test for operator =, with p2 = p1: " << "p2 = " << p2 << endl;

	Polynomial p3 = p1 + p2;
	cout << "p3 = " << p3 << endl;
	cout << "Test for operator +, with p3 = p1 + p2: " << "p3 = " << p3 << endl;;

	Polynomial defaultPoly;
	cout << "Test for default constructor, with defaultPoly: " << defaultPoly << endl;

	Polynomial copy(p1);
	cout << "Test for copy consturctor, with copyPoly(p1): " << copy << endl;

	cout << "Test for coefficient function, with p1 coeff power 3: " << p1.coefficient(3) << endl;
	cout << "Test for coefficient function, with p1 coeff power 1: " << p1.coefficient(1) << endl;

	Polynomial p7;
	p7.changeCoefficient(10, 4);
	p7.changeCoefficient(3, 2);
	p7.changeCoefficient(-5, 1);
	p7.changeCoefficient(15, 9);

	cout << "Testing for degree function, with p1: " << p1.degree() << endl;
	cout << "Testing for degree function, with p7: " << p7.degree() << endl;


	p1 += p2;
	cout << "Testing for += operator, with p1 = p1 + p2: " << p1 << endl;

	Polynomial p4;
	p4.changeCoefficient(5, 5);
	p4.changeCoefficient(6, 6);
	p4.changeCoefficient(7, 7);

	Polynomial p5;
	p5.changeCoefficient(1, 5);
	p5.changeCoefficient(1, 6);
	p5.changeCoefficient(3, 7);
	p5.changeCoefficient(2, -2);

	cout << "p4:" << p4 << endl;
	cout << "p5:" << p5 << endl;

	p4 -= p5;
	cout << "Testing for -= operator, p4 = p4 - p5: " << p4 << endl;

	Polynomial p10;
	p10 = p5 - p4;
	cout << "Test for operator -, with p10 = p5 - p4: " << "p10 = " << p10 << endl;;
	
	cout << "Testing for == operator and operater !=, with p4 == p5: ";
	if (p5 == p4)
	{
		cout << "p4 and p5 are the same" << endl;
	}
	else
	{
		cout << "p4 and p5 are not the same" << endl;
	}
	return 0;

}
//pass in zero power