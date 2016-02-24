#ifndef _GEOMETRICOBJECT_H_
#define _GEOMETRICOBJECT_H_

#include "../../../utils/Utils.h"

class RectWorld;


class GeometricObject
{
public:
	static int Count;

	~GeometricObject();
	virtual float getMaxX() = 0;
	virtual float getMaxY() = 0;
	virtual float getMaxZ() = 0;
	virtual float getMinX() = 0;
	virtual float getMinY() = 0;
	virtual float getMinZ() = 0;
	virtual void Move() = 0;
	virtual void getInfo(Vec3<float>&, float&, Color&, bool&) = 0;
	virtual bool isIntersects(Vec3<float> p) = 0;
	void setRect(RectWorld* c);
	Color getDiffuse() const;
	Color getAmbient() const;
	Color getSpecular() const;
	int getId() const;
	virtual bool isRayIntersects(Vec3<float> ray, Vec3<float> src, Vec3<float>&, Vec3<float> & Point, float& dist) = 0;

	virtual int nextPos(Vec3<float> p) = 0;
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