#include "stdafx.h"
#include "math.h"
#include "Actors.h"


//// Vector definition: ////

// Constructors:
Vector::Vector(double _x, double _y) : x(_x), y(_y) {}
Vector::Vector() : x(0), y(0) {}

// Operators overloading:
Vector Vector::operator+(Vector rhs) {
	return Vector(rhs.x + x, rhs.y + y);
}
Vector Vector::operator-(Vector rhs) {
	 return Vector(x - rhs.x, y - rhs.y);
}
Vector Vector::operator*(double rhs) {
	return Vector(x * rhs, y * rhs);
}
Vector Vector::operator/(double rhs) {
	return Vector(x / rhs, y / rhs);
}


// Getting the length of a vector;
float Vector::absolute() {
	return sqrt(x * x + y * y);
}

// Evaluating the scalar product of 2 vectors;
double Vector::scalar(Vector rhs) {
	return x * rhs.x + y * rhs.y;
}

void Vector::reflect(bool wall) {
	if (wall) x = -x;
	else y = -y;
}

//// Actor definition: ////

int Actor::m_Rad;

//Constructors
Actor::Actor() : X(0), Y(0), vec(Vector(0, 0)) {}
Actor::Actor(double _x, double _y) : X(_x), Y(_y), vec(Vector(0, 0)) {}
Actor::Actor(double _x, double _y, Vector v) : X(_x), Y(_y), vec(v) {}

// Moving of an actor with his speed;
void Actor::move(double _x, double _y) {
	vec.x = _x;
	vec.y = _y;
	X += _x; Y += _y;
}

void Actor::collide(Actor& left, Actor& right, bool secondToScoot) {
	Vector colLR(right.X - left.X, right.Y - left.Y);   // Creating a vector of distance between Actors
	colLR = colLR / colLR.absolute();					// ... and making unit-vector
														
	// Scooting one of circles out of another's radius (depends of mouse-dragged Actor)
	if (secondToScoot) {
		right.X = left.X + (colLR * (2 * m_Rad + 1)).x;
		right.Y = left.Y + (colLR * (2 * m_Rad + 1)).y;
	}
	else {
		left.X = right.X - (colLR * (2 * m_Rad + 1)).x;
		left.Y = right.Y - (colLR * (2 * m_Rad + 1)).y;
	}
	// Main action;
	Vector exchange = colLR * (left.vec.scalar(colLR) + right.vec.scalar(colLR * (-1)));
	left.vec = left.vec - exchange;
	right.vec = right.vec + exchange;
		return;
}

// Detecting if circles touch each-other;
bool Actor::touch(const Actor& left, const Actor& right) {
	return ((left.X - right.X) * (left.X - right.X) + (left.Y - right.Y) * (left.Y - right.Y)) <= m_Rad * m_Rad * 4;
}

