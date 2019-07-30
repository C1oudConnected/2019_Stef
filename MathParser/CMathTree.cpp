#include "stdafx.h"
#include "CMathTree.h"
#include <iostream>


CMathTree::CMathTree(std::string _value, CMathTree * _left, CMathTree * _right) : value(_value), left(_left), right(_right) {};
CMathTree::~CMathTree() {
	if (value == "+" || value == "-" || value == "*" || value == "/" || value == "^") {
		delete(left);
		delete(right);
	}
}

double CMathTree::evaluate() {
	if (this->left == NULL)
		return std::stod(value);
	else
		if (value == "+") return left->evaluate() + right->evaluate();
		else if (value == "-") return left->evaluate() - right->evaluate();
		else if (value == "*") return left->evaluate() * right->evaluate();
		else if (value == "/") return left->evaluate() / right->evaluate();
		else if (value == "^") return pow(left->evaluate(), right->evaluate());
}

void CMathTree::representInPrefix() {
	if (left == NULL)
		std::cout << value << " ";
	else {
		std::cout << value << " ";
		left->representInPrefix();
		right->representInPrefix();
	}
}

void CMathTree::representInPostfix() {
	if (left == NULL)
		std::cout << value << " ";
	else {
		right->representInPostfix();
		left->representInPostfix();
		std::cout << value << " ";
	}
}

void CMathTree::representInInfix() {
	if (left == NULL)
		std::cout << value << " ";
	else {
		if (((value == "*" || value == "/") && (left->value == "+" || left->value == "-")) || ((value == "^") && (left->value == "+" || left->value == "-" || left->value == "*" || left->value == "/")))
			std::cout << "( ";
		left->representInInfix();
		if (((value == "*" || value == "/") && (left->value == "+" || left->value == "-")) || ((value == "^") && (left->value == "+" || left->value == "-" || left->value == "*" || left->value == "/")))
			std::cout << ") ";
		std::cout << value << " ";
		if (((value == "*" || value == "/") && (right->value == "+" || right->value == "-")) || ((value == "^") && (right->value == "+" || right->value == "-" || right->value == "*" || right->value == "/")))
			std::cout << "( ";
		right->representInInfix();
		if (((value == "*" || value == "/") && (right->value == "+" || right->value == "-")) || ((value == "^") && (right->value == "+" || right->value == "-" || right->value == "*" || right->value == "/")))
			std::cout << ") ";
	}
}

// Main parsing function;
CMathTree* CMathTree::parseStringToTree(char* string) {
	static int i; //Symbol counter;
	CMathTree* ret_val = NULL; //Return value;
	int numb_start = -1; // start position of a current number
	std::string val;	 // current number string;
	bool prev_brackets = false; // If previous expression was in brackets;

	for (; true; i++) { // Main loop;
						// Check if number starts;
		if ((string[i] >= '0' && string[i] <= '9') || string[i] == '.') {
			if (numb_start == -1) numb_start = i;
		}
		else {
			//If number is started and finished, store it to the string;
			if (numb_start != -1) {
				val = "";
				for (int j = 0; j < i - numb_start; j++)
					val += string[numb_start + j];
				// Make a Tree Node with a current number;
				CMathTree* temp = new CMathTree(val);
				if (ret_val == NULL)
					ret_val = temp;
				else if (ret_val->right->value == "?") {
					delete ret_val->right;
					ret_val->right = temp;
				}
				else {
					delete ret_val->right->right;
					ret_val->right->right = temp;
				}

				// Exit if expression ends;
				if (string[i] == '\0') {
					i = 0;
					break;
				}

				if (string[i] == ')') {
					i++;
					break;
				}
			}

			// Recursively process the expression in brackets;
			if (string[i] == '(') {
				i++;
				CMathTree* temp = parseStringToTree(string);
				if (ret_val == NULL)
					ret_val = temp;
				else if (ret_val->right->value == "?") {
					delete ret_val->right;
					ret_val->right = temp;
				}
				else if (ret_val->right->right->value == "?") {
					delete ret_val->right->right;
					ret_val->right->right = temp;
				}
				prev_brackets = true;
				numb_start = -1;

				//Exit if expression ends;
				if (string[i] == '\0') {
					i = 0;
					break;
				}
				if (string[i] == ')') {
					i++;
					break;
				}
			}

			// Process + and -;
			if (string[i] == '+' || string[i] == '-') {
				std::string temp = "", q = "?";
				temp += string[i];
				ret_val = new CMathTree(temp, ret_val, new CMathTree(q));
				prev_brackets = false;
				numb_start = -1;
			}

			// Process * and /;
			if (string[i] == '*' || string[i] == '/') {

				if (prev_brackets || ret_val->left == NULL) {
					std::string temp = "", q = "?";
					temp += string[i];
					ret_val = new CMathTree(temp, ret_val, new CMathTree(q));
				}
				else {
					std::string temp = "", q = "?";
					temp += string[i];
					ret_val->right = new CMathTree(temp, ret_val->right, new CMathTree(q));
				}

				prev_brackets = false;
				numb_start = -1;
			}

			// Process ^;
			if (string[i] == '^') {
				std::string temp = "", q = "?";
				temp += string[i];

				if (prev_brackets || ret_val->left == NULL) {
					ret_val = new CMathTree(temp, ret_val, new CMathTree(q));
				}
				else {
					if (ret_val->right->right == NULL)
						ret_val->right = new CMathTree(temp, ret_val->right, new CMathTree(q));
					else
						ret_val->right->right = new CMathTree(temp, ret_val->right, new CMathTree(q));
				}
				prev_brackets = false;
				numb_start = -1;
			}
		}
	}

	return ret_val;
}
