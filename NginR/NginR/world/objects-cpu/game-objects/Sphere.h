#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "../../../utils/Utils.h"
#include <string>
#include <sstream>
#include "GeometricObject.h"


class Sphere :public GeometricObject
{
public:
	Sphere(Vec3 p, float r);
	Sphere(std::string line);
	float getMaxX();
	float getMaxY();
	float getMaxZ();
	float getMinX();
	float getMinY();
	float getMinZ();
	bool shouldExist();
	void Move();
	void getInfo(Vec3&, float &r, Color& c, bool&);
	bool isRayIntersects(Vec3 ray, Vec3 src, Vec3&, Vec3 & Point, float& dist);
	bool isIntersects(Vec3 p);
	int nextPos(Vec3 p);

private:
	Vec3 center;
	float radius;
};

#endif