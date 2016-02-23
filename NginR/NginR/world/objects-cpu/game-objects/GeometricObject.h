#ifndef _GEOMETRICOBJECT_H_
#define _GEOMETRICOBJECT_H_

#include "../../../utils/Utils.h"

class RectWorld;


class GeometricObject
{
public:
	static int Count;
	virtual float getMaxX() = 0;
	virtual float getMaxY() = 0;
	virtual float getMaxZ() = 0;
	virtual float getMinX() = 0;
	virtual float getMinY() = 0;
	virtual float getMinZ() = 0;
	virtual void Move() = 0;
	virtual void getInfo(Vec3&, float&, Color&, bool&) = 0;
	virtual bool isIntersects(Vec3 p) = 0;
	void setRect(RectWorld* c);
	Color getDiffuse();
	Color getAmbient();
	Color getSpecular();
	int getId();
	virtual bool isRayIntersects(Vec3 ray, Vec3 src, Vec3&, Vec3 & Point, float& dist) = 0;

	virtual int nextPos(Vec3 p) = 0;
protected:
	int id;
	Color ColorAmbient;
	Color ColorSpecular;
	Color ColorDiffuse;
	bool toRight;

private:
	RectWorld * container;
};


#endif