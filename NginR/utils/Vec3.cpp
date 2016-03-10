#include <istream>
#ifdef _VEC3_H_

#include <math.h>

template <typename T>
std::istream& operator>>(std::istream& is, Vec3<T>& obj)
{
	T x,y,z;
	is>>x;
	is>>y;
	is>>z;

	obj = Vec3<T>(x,y,z);
	return is;
}

template <typename T>
Vec3<T>::Vec3()
{
	x = 0;
	y = 0;
	z = 0;
}

template <typename T>
Vec3<T>::Vec3(T xPos, T yPos, T zPos)
{
	x = xPos;
	y = yPos;
	z = zPos;
}

template <typename T>
Vec3<T> Vec3<T>::operator-(const Vec3 & rhs)
{
	return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
}

template <typename T>
Vec3<T> Vec3<T>::operator+(const Vec3 & rhs)
{
	return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
}

template <typename T>
void Vec3<T>::operator+=(const Vec3<T>& rhs)
{
	x = x + rhs.x;
	y = y + rhs.y;
	z = z + rhs.z;
}

template <typename T>
bool Vec3<T>::operator==(const Vec3<T>& rhs) const
{
	return x == rhs.getX() && y == rhs.getY() && z == rhs.getZ();
}

template <typename T>
T Vec3<T>::dotProduct(const Vec3 & vec)
{
	return x*vec.x + y*vec.y + z*vec.z;
}


template <typename T>
void Vec3<T>::crossProduct(Vec3<T> vec3)
{
	float xPos = getY()*vec3.getZ() - getZ()*vec3.getY();
	float yPos = getZ()*vec3.getX() - getX()*vec3.getZ();
	float zPos = getX()*vec3.getY() - getY()*vec3.getX();
	x = xPos;
	y = yPos;
	z = zPos;
}

template <typename T>
void Vec3<T>::rotate(Vec3<T> angle)
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

template <typename T>
void Vec3<T>::Normalize()
{
	float length = sqrt(x*x + y*y + z*z);
	x = x / length;
	y = y / length;
	z = z / length;
}



template <typename T>
T Vec3<T>::getX() const
{
	return x;
}

template <typename T>
T Vec3<T>::getY() const
{
	return y;
}

template <typename T>
T Vec3<T>::getZ() const
{
	return z;
}

#endif
