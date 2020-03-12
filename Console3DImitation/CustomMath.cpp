#include "CustomMath.h"
#include "math.h"

Vector::Vector() : m_data{} {}

Vector::Vector(const FLOAT* _data = nullptr) {
	for (unsigned char i = 0; i < 4; ++i)
		m_data[i] = _data[i];
}

Vector::Vector(FLOAT a, FLOAT b, FLOAT c, FLOAT d) {
	m_data[0] = a;
	m_data[1] = b;
	m_data[2] = c;
	m_data[3] = d;
}

FLOAT& Vector::operator[](unsigned char index) {
	if (index > 3) throw "Bad 4D vector index";
	return m_data[index];
}

const FLOAT& Vector::operator()(unsigned char index) const {
	if (index > 3) throw "Bad 4D vector index";
	return m_data[index];
}

Vector Vector::operator+(const Vector& rhs) const
{
	FLOAT newData[4] = {
		m_data[0] + rhs(0),
		m_data[1] + rhs(1),
		m_data[2] + rhs(2),
		m_data[3] + rhs(3)
	};
	return Vector(newData);
}

Vector& Vector::operator+=(const Vector& rhs)
{
	m_data[0] += rhs(0);
	m_data[1] += rhs(1);
	m_data[2] += rhs(2);
	m_data[3] += rhs(3);

	return *this;
}

Vector Vector::operator-(const Vector& rhs) const
{
	FLOAT newData[4] = {
		m_data[0] - rhs(0),
		m_data[1] - rhs(1),
		m_data[2] - rhs(2),
		m_data[3] - rhs(3)
	};
	return Vector(newData);
}

Vector& Vector::operator-=(const Vector& rhs)
{
	m_data[0] -= rhs(0);
	m_data[1] -= rhs(1);
	m_data[2] -= rhs(2);
	m_data[3] -= rhs(3);

	return *this;
}

Vector Vector::operator*(FLOAT rhs) const
{
	FLOAT newData[4] = {
		m_data[0] * rhs,
		m_data[1] * rhs,
		m_data[2] * rhs,
		m_data[3] * rhs
	};
	return Vector(newData);
}

Vector& Vector::operator*=(FLOAT rhs)
{
	m_data[0] *= rhs;
	m_data[1] *= rhs;
	m_data[2] *= rhs;
	m_data[3] *= rhs;

	return *this;
}

Vector Vector::operator/(FLOAT rhs) const
{
	FLOAT newData[4] = {
		m_data[0] / rhs,
		m_data[1] / rhs,
		m_data[2] / rhs,
		m_data[3] / rhs
	};
	return Vector(newData);
}

Vector& Vector::operator/=(FLOAT rhs)
{
	m_data[0] /= rhs;
	m_data[1] /= rhs;
	m_data[2] /= rhs;
	m_data[3] /= rhs;

	return *this;
}

Vector Vector::proj(const Vector& rhs) {
	auto magn = rhs.L();
	Vector v = rhs * (*this).dot(rhs) / (magn *	magn);
	return v;
}

Vector& Vector::nrmlz()
{
	*this /= this->L();
	return *this;
}

Vector Vector::nrmlzd() const
{
	return *this / this->L();
}

FLOAT Vector::dot(const Vector& rhs) const
{
	return	m_data[0] * rhs(0) +
			m_data[1] * rhs(1) + 
			m_data[2] * rhs(2) + 
			m_data[3] * rhs(3);
}

Vector Vector::cross(const Vector& rhs) const
{
	FLOAT newData[4] = {
		m_data[1] * rhs(2) - m_data[2] * rhs(1),
		m_data[2] * rhs(0) - m_data[0] * rhs(2),
		m_data[0] * rhs(1) - m_data[1] * rhs(0),
		0
	};
	return Vector(newData);
}

FLOAT Vector::L() const
{
	return sqrt(m_data[0] * m_data[0] +
				m_data[1] * m_data[1] + 
				m_data[2] * m_data[2] + 
				m_data[3] * m_data[3] );
}
