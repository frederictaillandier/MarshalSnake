#pragma once

#include <iostream>  
#include <fstream>

namespace MarshalAPI
{
	class Vector3
	{
		float m_x;
		float m_y;
		float m_z;
	public:
		Vector3();
		Vector3(float _x, float _y, float _z);
		Vector3(Vector3 const &other);
		float X() const;
		float Y() const;
		float Z() const;
		Vector3 operator=(Vector3 const &other);
		Vector3 operator+(Vector3 const & other) const;
		Vector3 operator-(Vector3 const & other) const;
		Vector3 operator+=(Vector3 const &other);
		Vector3 operator-=(Vector3 const &other);
		Vector3 operator*=(float mult);
		bool operator==(Vector3 const &other) const;
		Vector3 operator* (float mult) const;
		Vector3 Vector3::Normalized() const;
		double Vector3::Distance() const;

		static const Vector3 LEFT;
		static const Vector3 RIGHT;
		static const Vector3 UP;
		static const Vector3 DOWN;
		static const Vector3 FORWARD;
		static const Vector3 BACKWARD;
		static const Vector3 ZERO;
	};

	std::ostream& operator<<(std::ostream& os, Vector3 const & v);
}