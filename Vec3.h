#pragma once
#include <ostream>

class Vec3
{
	float m_x, m_y, m_z;	
public:
	constexpr Vec3(): m_x(0), m_y(0), m_z(0) {};
	constexpr Vec3(float x, float y, float z) :
		m_x(x), m_y(y), m_z(z) {};

	float x() const { return m_x; }
	float y() const { return m_y; }
	float z() const { return m_z; }

	float squaredMagnitude() const
	{
		// dot product with itself
		return m_x*m_x + m_y*m_y + m_z*m_z;
	}

	float magnitude() const
	{
		return sqrt(squaredMagnitude());
	}

	// Returns the normalized version of itself
	Vec3 normalized() const
	{
		return *this / magnitude();
	}

	Vec3 operator-() const { return { -m_x, -m_y, -m_z }; }
	Vec3 operator+(const Vec3& other) const { 
		return { m_x + other.m_x,
				 m_y + other.m_y,
				 m_z + other.m_z };
	}
	Vec3 operator+=(const Vec3& other) {
		m_x += other.m_x;
		m_y += other.m_y;
		m_z += other.m_z;
		return *this;
	}
	Vec3 operator-(const Vec3& other) const  {
		return { m_x - other.m_x,
				 m_y - other.m_y,
				 m_z - other.m_z };
	}
	Vec3 operator-=(const Vec3& other) {
		m_x -= other.m_x;
		m_y -= other.m_y;
		m_z -= other.m_z;
		return *this;
	}
	Vec3 operator*(float t) const { return{ t * m_x, t * m_y, t * m_z }; }
	Vec3 operator*=(float t)
	{
		m_x *= t;
		m_y *= t;
		m_z *= t;
		return *this;
	}
	friend Vec3 operator*(float t, const Vec3& v) { return v * t; }
	Vec3 operator/(float t)const { 
		if (t == 0)
			return { 0,0,0 };
		return{ m_x/t, m_y/t, m_z/t }; 
	}
	Vec3 operator/=(float t)
	{
		if (t == 0)
			return *this;
		m_x /= t;
		m_y /= t;
		m_z /= t;
		return *this;
	}
	bool operator==(const Vec3& other) const
	{
		return (m_x == other.m_x) &&
			   (m_y == other.m_y) &&
			   (m_z == other.m_z);
	}
	bool operator!=(const Vec3& other) const { return !(*this == other); }

	//Direct product
	Vec3 operator*(const Vec3& other) const {
		return { m_x * other.m_x,
				 m_y * other.m_y,
				 m_z * other.m_z };
	}
	Vec3 operator*=(const Vec3& other) {
		m_x *= other.m_x;
		m_y *= other.m_y;
		m_z *= other.m_z;
		return *this;
	}

	// Dot product
	friend float dot(const Vec3& v1,const Vec3& v2)
	{
		return (v1.m_x * v2.m_x) + (v1.m_y * v2.m_y) + (v1.m_z * v2.m_z);
	}

	// Cross product
	friend Vec3 cross(const Vec3& v1, const Vec3& v2)
	{
		return Vec3(v1.m_y * v2.m_z - v1.m_z * v2.m_y,
				  -(v1.m_x * v2.m_z - v1.m_z * v2.m_x),
					v1.m_x * v2.m_y - v1.m_y* v2.m_x);
	}

	friend std::ostream& operator<<(std::ostream& out, const Vec3& v)
	{
		out << v.x() << ' ' << v.y() << ' ' << v.z();
	}
};

