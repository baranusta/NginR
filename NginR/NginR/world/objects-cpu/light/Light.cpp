#include "Light.h"

Vec3 Light::getPos()
{
	return position;
}

Color Light::getSpec()
{
	return SpecularhighLight;
}

Color Light::getDiffuse()
{
	return DiffuseLight;
}

Color Light::getAmbient()
{
	return AmbientLight;
}

Light::~Light()
{
}

void Light::changeStatus(bool stat)
{
	status = stat;
}

void Light::changePosition(Vec3 pos)
{
	position = pos;
}