#include "GeometricObject.h"


int GeometricObject::Count = 0;

GeometricObject::~GeometricObject()
{
}


void GeometricObject::setRect(RectWorld* c)
{
	container = c;
}
int GeometricObject::getId() const
{
	return id;
}


Color GeometricObject::getDiffuse() const
{
	return ColorDiffuse;
}
Color GeometricObject::getAmbient() const
{
	return ColorDiffuse;
}
Color GeometricObject::getSpecular() const
{
	return ColorDiffuse;
}
