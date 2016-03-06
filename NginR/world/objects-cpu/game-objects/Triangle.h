#ifndef _QUADRILATERALS_H_
#define _QUADRILATERALS_H_

#include "../../../utils/Utils.h"
#include <string>
#include <sstream>
#include "GeometricObject.h"


class Triangle :public GeometricObject
{
public:
	Triangle(Vec3<float> top, Vec3<float> right, Vec3<float> left);
	explicit Triangle(std::string line);
	Triangle(const Triangle & copied);

	float getMaxX() override;
	float getMaxY() override;
	float getMaxZ() override;
	float getMinX() override;
	float getMinY() override;
	float getMinZ() override;

	void Move() override;

	bool isRayIntersects(Vec3<float> & ray, Vec3<float> & src, Vec3<float>&, Vec3<float> & Point, float& dist) override;
	bool isIntersects(Vec3<float> p) override;
	int nextPos(Vec3<float> p) override;

	const Vec3<float> & getNormal() const;

private:
	float getMax(float arr[]) const;
	float getMin(float arr[]) const;

	void copyTriangle(Vec3<float> top, Vec3<float> right, Vec3<float> left);
	Vec3<float>& calculateNormal();

	Vec3<float> corners[3];
	Vec3<float> normal;
};

#endif
