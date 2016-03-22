#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "../../../utils/Utils.h"

class Light
{
public:
	Light(Vec3<float> pos, Color Ambient, Color Diffuse, Color Specular) :
	status(true), AmbientLight(Ambient), DiffuseLight(Diffuse), SpecularhighLight(Specular), position(pos)
	{};
	~Light();
	Vec3<float> getPos() const;

	Color getSpec() const;
	Color getDiffuse() const;
	Color getAmbient() const;
	void changeStatus(bool);
	void changePosition(Vec3<float> pos);
	
private:
	bool status;
	Color AmbientLight;
	Color DiffuseLight;
	Color SpecularhighLight;
	Vec3<float> position;
};

#endif