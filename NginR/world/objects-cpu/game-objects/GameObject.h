#ifndef _GEOMETRICOBJECT_H_
#define _GEOMETRICOBJECT_H_

#include "../../../utils/Utils.h"

class RectWorld;


class GameObject
{
public:
	static int Count;

	GameObject();
	~GameObject();
	virtual float getMaxX() = 0;
	virtual float getMaxY() = 0;
	virtual float getMaxZ() = 0;
	virtual float getMinX() = 0;
	virtual float getMinY() = 0;
	virtual float getMinZ() = 0;

	//virtual bool isIntersects(Vec3<float> p) = 0;
	void setRect(RectWorld* c);
	Color getDiffuse() const;
	Color getAmbient() const;
	Color getSpecular() const;

	void setDiffuse(Color);
	void setAmbient(Color);
	void setSpecular(Color);
	


	virtual bool isRayIntersects(Vec3<float> & ray, Vec3<float> & src, Vec3<float> & Point, float& dist) = 0;
	//virtual int nextPos(Vec3<float> p) = 0;

	//Getters
	virtual const Vec3<float>& getNormal(const Vec3<float>& intersectionPoint) const = 0;
	int getId() const;

protected:
	int id;
	Color ColorAmbient;
	Color ColorSpecular;
	Color ColorDiffuse;
	bool toRight;


	Vec3<float> angle;

private:
	RectWorld * container;
};


#endif