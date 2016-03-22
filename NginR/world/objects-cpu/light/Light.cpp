#include "Light.h"

Vec3<float> Light::getPos() const
{
	return position;
}

Color Light::getSpec() const
{
	return SpecularhighLight;
}

Color Light::getDiffuse() const
{
	return DiffuseLight;
}

Color Light::getAmbient() const
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

void Light::changePosition(Vec3<float> pos)
{
	position = pos;
}