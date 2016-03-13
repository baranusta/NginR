#include "Sphere.h"
#include <iostream>

Sphere::Sphere(Vec3<float> p, float r)
{
	center = p;
	radius = r;
}

Sphere::Sphere(std::string line)
{
	std::istringstream eachword(line);
	std::string type;
	eachword >> type;
	float xPos, yPos, zPos;
	eachword >> xPos >> yPos >> zPos;
	Vec3<float> c(xPos, yPos, zPos);
	center = c;
	float r;
	eachword >> r;
	radius = r;
	toRight = Count % 2 == 0;
	eachword >> xPos >> yPos >> zPos;
	ColorSpecular = Color(xPos, yPos, zPos);
	eachword >> xPos >> yPos >> zPos;
	ColorDiffuse = Color(xPos, yPos, zPos);
	eachword >> xPos >> yPos >> zPos;
	ColorAmbient = Color(xPos, yPos, zPos);
}

void Sphere::getInfo(Vec3<float>&pos, float &r, Color& c, bool& is)
{
	is = toRight;
	c = ColorDiffuse;
	pos = center;
	r = radius;
}

float Sphere::getMaxX()
{
	return center.getX() + radius;
}

float Sphere::getMaxY()
{
	return center.getY() + radius;
}

float Sphere::getMaxZ()
{
	return center.getZ() + radius;
}

float Sphere::getMinX()
{
	return center.getX() - radius;
}

float Sphere::getMinY()
{
	return center.getY() - radius;
}

float Sphere::getMinZ()
{
	return center.getZ() - radius;
}

bool Sphere::isRayIntersects(Vec3<float> & ray, Vec3<float> & src, Vec3<float> & Point, float &dist)
{
	float a = 1;
	float b = 2 * (ray.getX() *(src.getX() - center.getX()) + ray.getY() *(src.getY() - center.getY()) + ray.getZ() *(src.getZ() - center.getZ()));
	float c = pow(src.getX() - center.getX(), 2) + pow(src.getY() - center.getY(), 2) + pow(src.getZ() - center.getZ(), 2) - radius*radius;
	float disc = b*b - 4 * c;
	if (disc<0)
	{
		return false;
	}
	disc = sqrt(disc);
	float t = (0.5f)*(-b - disc);
	if (t > 0)
	{
		dist = sqrt(a) * t;
		Vec3<float> hitd(ray.getX()*t, ray.getY()*t, ray.getZ()*t);
		Point = src + hitd;
		return true;
	}
	else
		return false;
}

const Vec3<float>& Sphere::getNormal(const Vec3<float>& intersectionPoint) const
{
	Vec3<float> vect = intersectionPoint;
	vect = vect - center;
	vect.Normalize();
	return vect;
}

bool Sphere::_checkDimension(float target, float src, float dim2Max, float dim2Min)
{ 
	return target < 0 ? src >= dim2Min : src <= dim2Max;
}

bool Sphere::_isPossibleToIntersect(Vec3<float> & ray, Vec3<float> & src)
{
	return _checkDimension(ray.getX(), src.getX(), getMaxX(), getMinX())
		&& _checkDimension(ray.getX(), src.getX(), getMaxX(), getMinX())
		&& _checkDimension(ray.getX(), src.getX(), getMaxX(), getMinX());
}

bool Sphere::shouldExist()
{
	return radius > 0;
}
