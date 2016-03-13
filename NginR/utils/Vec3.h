#ifndef _VEC3_H_
#define _VEC3_H_

template <typename T>
class Vec3
{
public:
	Vec3();
	Vec3(T xPos, T yPos, T zPos);
	void Normalize();
	T getX() const;
	T getY() const;
	T getZ() const;
	Vec3 operator-(const Vec3 & rhs);
	Vec3 operator+(const Vec3 & rhs);
	Vec3 operator*(T value);

	void operator+=(const Vec3 & rhs);
	bool operator==(const Vec3& rhs) const;

	T distance(const Vec3<T>& vec3);
	void rotate(Vec3 angle);
	T dotProduct(const Vec3 & vec);
	Vec3<T> crossProduct(Vec3<T> vec3);

protected:
	T x;
	T y;
	T z;
};

#include "Vec3.cpp"

#endif