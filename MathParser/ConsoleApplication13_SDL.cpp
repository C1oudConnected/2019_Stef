// MathParser.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "CMathTree.h"

int main()
{
	std::string str = "(2+3)*2^(4*(2+4))+0.5";
	CMathTree* t = CMathTree::parseStringToTree((char*)str.data());

	std::cout << str;
	std::cout << std::endl << "Value = " << t->evaluate() << std::endl;
	std::cout << "Representation in prefix: "; t->representInPrefix();
	std::cout << std::endl;
	std::cout << "Representation in postfix: "; t->representInPostfix();
	std::cout << std::endl;
	std::cout << "Representation in infix: "; t->representInInfix();
	std::cout << std::endl;

	delete(t);
	return 0;
}
