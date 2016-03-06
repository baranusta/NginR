#ifndef _VEC3_H_
#define _VEC3_H_

template <typename T>
class Vec3
{
public:
	Vec3();
	Vec3(T xPos, T yPos, T zPos);
	void Normalize();
	T getX();
	T getY();
	T getZ();
	Vec3 operator-(const Vec3 & rhs);
	Vec3 operator+(const Vec3 & rhs);
	void rotate(Vec3 angle);
	T dotProduct(const Vec3 & vec);

private:
	T x;
	T y;
	T z;
};

template<typename T>
using Angle = Vec3<T>;

#include "Vec3.cpp"

#endif