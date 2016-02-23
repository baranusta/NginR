#include "Vec3.h"
#include <math.h>


Vec3::Vec3(float xPos, float yPos, float zPos)
{
	x = xPos;
	y = yPos;
	z = zPos;
}


Vec3 Vec3::operator-(Vec3 rhs)
{
	return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vec3 Vec3::operator+(Vec3 rhs)
{
	return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
}

float Vec3::dotProduct(Vec3 vec)
{
	return x*vec.x + y*vec.y + z*vec.z;
}

void Vec3::rotate(Vec3 angle)
{
	//rotate around x
	y = y*cos(angle.getX()) - z*sin(angle.getX());
	z = z*sin(angle.getX()) + z*cos(angle.getX());

	//rotate around y
	x = x*cos(angle.getY()) + z*sin(angle.getY());
	z = -x*sin(angle.getY()) + z*cos(angle.getY());

	//rotate around z
	x = x*cos(angle.getZ()) - y*sin(angle.getZ());
	y = y*sin(angle.getZ()) + y*cos(angle.getZ());
}

void Vec3::Normalize()
{
	float length = sqrt(x*x + y*y + z*z);
	x = x / length;
	y = y / length;
	z = z / length;
}

Vec3::Vec3()
{
	x = 0;
	y = 0;
	z = 0;
}

float Vec3::getX()
{
	return x;
}

float Vec3::getY()
{
	return y;
}

float Vec3::getZ()
{
	return z;
}