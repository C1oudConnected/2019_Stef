#pragma once

#include "windows.h"

class Vector
{
private:
	//4D vector data (accessed by an operator[] to read & write).
	FLOAT m_data[4];

public:
	Vector();
	Vector(const FLOAT*);
	Vector(FLOAT, FLOAT, FLOAT, FLOAT);

	// Overloading operators to simplify the code.
	FLOAT&			operator[]	(unsigned char);		// Data access.
	const FLOAT&	operator()	(unsigned char) const;	// Data access(write only).
	Vector			operator+	(const Vector&) const;	// Summation with another vector.
	Vector&			operator+=	(const Vector&);		// Summation with assigning.
	Vector			operator-	(const Vector&) const;	// Subtracting.
	Vector&			operator-=	(const Vector&);		// Subtracting and assigning.
	Vector			operator*	(FLOAT)	const;			// Vector-number product.
	Vector&			operator*=	(FLOAT);				// Vector-number product with assigning.
	Vector			operator/	(FLOAT)	const;			// Vector-number division
	Vector&			operator/=	(FLOAT);				// Vector-number division with assigning.

	// Methods:	

	Vector	proj(const Vector&);		// Get vector's projection on another vector;
	Vector&	nrmlz();					// Normalizes vector and gets it.
	Vector	nrmlzd() const;				// Gets normalized copy of the vector.
	FLOAT	dot(const Vector&) const;	// Dot-product.
	Vector	cross(const Vector&) const;	// Cross-product.
	FLOAT	L() const;					// Length of a vector.					
};

