#include "Triangle.h"


void Triangle::copyTriangle(Vec3<float> top, Vec3<float> right, Vec3<float> left)
{
	corners[0] = top;
	corners[1] = right;
	corners[2] = left;
	normal = calculateNormal();
}

Vec3<float>& Triangle::calculateNormal()
{
	Vec3<float> vec1 = corners[2] - corners[0];
	Vec3<float> vec2 = corners[1] - corners[0];
	vec2.crossProduct(vec1);
	vec2.Normalize();
	return vec2;
}

Triangle::Triangle(Vec3<float> top,Vec3<float> right,Vec3<float> left)
{
	copyTriangle(top, left, right);
}

Triangle::Triangle(std::string line)
{
	Vec3<float> top(0, 1, 0);
	Vec3<float> right(1, 0, 0);
	Vec3<float> left(0, 0, 0);

	copyTriangle(top, right, left);
}

Triangle::Triangle(const Triangle& copied)
{
}

float Triangle::getMax(float arr[]) const
{
	float max = arr[0];
	for (int i = 1; i < 2; i++)
	{
		if (max < arr[i])
			max = arr[i];
	}
	return max;
	
}

float Triangle::getMin(float arr[]) const
{
	float min = arr[0];
	for (int i = 1; i < 2; i++)
	{
		if (min < arr[i])
			min = arr[i];
	}
	return min;
}

float Triangle::getMaxX()
{
	float values[3] = { corners[0].getX(), corners[1].getX(), corners[2].getX() };
	return getMax(values);
}

float Triangle::getMaxY()
{
	float values[3] = { corners[0].getY(), corners[1].getY(), corners[2].getY() };
	return getMax(values);
}

float Triangle::getMaxZ()
{
	float values[3] = { corners[0].getZ(), corners[1].getZ(), corners[2].getZ() };
	return getMax(values);
}

float Triangle::getMinX()
{
	float values[3] = { corners[0].getX(), corners[1].getX(), corners[2].getX() };
	return getMin(values);
}

float Triangle::getMinY()
{
	float values[3] = { corners[0].getY(), corners[1].getY(), corners[2].getY() };
	return getMin(values);
}

float Triangle::getMinZ()
{
	float values[3] = { corners[0].getZ(), corners[1].getZ(), corners[2].getZ() };
	return getMin(values);
}

void Triangle::Move()
{
}

bool Triangle::isRayIntersects(Vec3<float>& ray, Vec3<float>& src, Vec3<float>&, Vec3<float>& Point, float& dist)
{
	return 1;
}

bool Triangle::isIntersects(Vec3<float> p)
{
	return 1;
}

int Triangle::nextPos(Vec3<float> p)
{
	return 1;
}

const Vec3<float>& Triangle::getNormal() const
{
	return normal;
}