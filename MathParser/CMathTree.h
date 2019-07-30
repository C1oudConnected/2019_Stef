#pragma once
#include <string>
class CMathTree {
private:
	std::string value; // Value stored in the node;
	CMathTree* left;   // Pointer to the left node;
	CMathTree* right;  // Pointer to the right node;
public:
	CMathTree(std::string _value, CMathTree* _left = NULL, CMathTree* _right = NULL);
	~CMathTree();

	double evaluate(); // Getting the whole expression's value;

	// Representing stored expression in several notations;
	void representInPrefix();
	void representInPostfix();
	void representInInfix();

	// Abstract function to parse the c-string into MathTree;
	static CMathTree* parseStringToTree(char*);
};

