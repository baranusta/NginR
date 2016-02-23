#include "GeometricObject.h"


int GeometricObject::Count = 0;

void GeometricObject::setRect(RectWorld* c)
{
	container = c;
}
int GeometricObject::getId()
{
	return id;
}


Color GeometricObject::getDiffuse()
{
	return ColorDiffuse;
}
Color GeometricObject::getAmbient()
{
	return ColorDiffuse;
}
Color GeometricObject::getSpecular()
{
	return ColorDiffuse;
}