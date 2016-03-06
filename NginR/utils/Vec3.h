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

	bool operator==(const Vec3& rhs) const;

	void rotate(Vec3 angle);
	T dotProduct(const Vec3 & vec);
	void crossProduct(Vec3<T> vec3);

private:
	T x;
	T y;
	T z;
};

template<typename T>
using Angle = Vec3<T>;

#include "Vec3.cpp"

#endif