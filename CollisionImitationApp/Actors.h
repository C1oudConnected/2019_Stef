#pragma once
//#include "Actors.cpp"

class Vector {
public:
	double x, y;
	Vector(double _x, double _y);
	Vector();

	Vector operator+(Vector rhs);
	Vector operator-(Vector rhs);
	Vector operator*(double rhs);
	Vector operator/(double rhs);

	float absolute();
	double scalar(Vector rhs);
	void reflect(bool wall);
};

// Main class, circles;
class Actor {
public:
	static int m_Rad; // Circles' radius;
	double X, Y; // Center's position of a current circle;
	Vector vec; // SpeedVector of a circle

	Actor();
	Actor(double _x, double _y);
	Actor(double _x, double _y, Vector v);

	void move(double _x, double _y);

	// collision between 2 circles (Actors);
	static void collide(Actor& left, Actor& right, bool secondToScoot);

	// Detecting if circles touch each-other;
	static bool touch(const Actor& left, const Actor& right);
};