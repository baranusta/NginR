#include "Sphere.h"
#include <iostream>

Sphere::Sphere(Vec3<float> p, float r, bool movable) : GeometricObject(movable)
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
	isMovable = true;
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

void Sphere::Move()
{
	if (center.getY() > 300)
		toRight = false;
	if (center.getY() < -300)
		toRight = true;
	int t = 2;
	if (!toRight)
		t *= -1;
	center = Vec3<float>(center.getX(), center.getY() + t, center.getZ());
}

bool Sphere::isRayIntersects(Vec3<float> & ray, Vec3<float> & src, Vec3<float>& Normal, Vec3<float> & Point, float &dist)
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
		Normal = Point - center;
		return true;
	}
	else
		return false;
}

bool Sphere::isIntersects(Vec3<float> p)
{
	if (getMaxX() > p.getX() && getMinX() < p.getX())
		return true;
	if (getMaxY() > p.getY() && getMinY() < p.getY())
		return true;
	if (getMaxZ() > p.getZ() && getMinZ() < p.getZ())
		return true;
	return false;
}

int Sphere::nextPos(Vec3<float> p)
{
	float pos = 0;
	if (center.getX() > p.getX())
		pos += 4;
	if (center.getY() > p.getY())
		pos += 2;
	if (center.getZ() > p.getZ())
		pos += 1;
	return pos;
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
