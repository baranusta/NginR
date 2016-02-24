#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "../../../utils/Utils.h"
#include <string>
#include <sstream>
#include "GeometricObject.h"


class Sphere :public GeometricObject
{
public:
	Sphere(Vec3<float> p, float r);
	Sphere(std::string line);
	float getMaxX() override;
	float getMaxY() override;
	float getMaxZ() override;
	float getMinX() override;
	float getMinY() override;
	float getMinZ() override;
	bool shouldExist();
	void Move();
	void getInfo(Vec3<float>&, float &r, Color& c, bool&);
	bool isRayIntersects(Vec3<float> ray, Vec3<float> src, Vec3<float>&, Vec3<float> & Point, float& dist);
	bool isIntersects(Vec3<float> p);
	int nextPos(Vec3<float> p);

private:
	Vec3<float> center;
	float radius;
};

#endif