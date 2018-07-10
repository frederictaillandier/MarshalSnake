#include <math.h>
#include "Vector3.h"

namespace MarshalAPI
{
	const Vector3 Vector3::LEFT = Vector3(-1, 0, 0);
	const Vector3 Vector3::RIGHT = Vector3(1, 0, 0);
	const Vector3 Vector3::UP = Vector3(0, 1, 0);
	const Vector3 Vector3::DOWN = Vector3(0, -1, 0);
	const Vector3 Vector3::FORWARD = Vector3(0, 0, 1);
	const Vector3 Vector3::BACKWARD = Vector3(0, 0, -1);
	const Vector3 Vector3::ZERO = Vector3(0, 0, 0);

	Vector3::Vector3()
		: m_x(0), m_y(0), m_z(0)
	{
	}

	Vector3::Vector3(float _x, float _y, float _z)
		: m_x(_x), m_y(_y), m_z(_z)
	{
	}

	Vector3::Vector3(Vector3 const &other)
	{
		m_x = other.m_x;
		m_y = other.m_y;
		m_z = other.m_z;
	}

	float Vector3::X() const
	{
		return m_x;
	}

	float Vector3::Y() const
	{
		return m_y;
	}

	float Vector3::Z() const
	{
		return m_z;
	}

	Vector3 Vector3::operator=(Vector3 const &other)
	{
		m_x = other.m_x;
		m_y = other.m_y;
		m_z = other.m_z;
		return (*this);
	}

	Vector3 Vector3::operator+=(Vector3 const & other)
	{
		m_x += other.m_x;
		m_y += other.m_y;
		m_z += other.m_z;
		return (*this);
	}

	Vector3 Vector3::operator-=(Vector3 const & other)
	{
		m_x -= other.m_x;
		m_y -= other.m_y;
		m_z -= other.m_z;
		return (*this);
	}

	Vector3 Vector3::operator+(Vector3 const & other) const
	{
		return Vector3(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
	}

	Vector3 Vector3::operator-(Vector3 const & other) const
	{
		return Vector3(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
	}

	Vector3 Vector3::operator*=(float mult)
	{
		m_x *= mult;
		m_y *= mult;
		m_z *= mult;
		return (*this);
	}

	bool Vector3::operator==(Vector3 const &other) const
	{
		return (m_x == other.m_x && m_y == other.m_y && m_z == other.m_z);
	}

	Vector3 Vector3::operator* (float mult) const
	{
		return 	Vector3(m_x * mult, m_y * mult, m_z * mult);
	}

	Vector3 Vector3::Normalized() const
	{
		double dist = sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
		return Vector3(m_x / dist, m_y / dist, m_z / dist);
	}
	double Vector3::Distance() const
	{
		return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
	}

	std::ostream& operator<<(std::ostream& os, Vector3 const & v)
	{
		os << v.X() << "." << v.Y() << "." << v.Z();
		return os;
	}


}