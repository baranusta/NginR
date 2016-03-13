#include "GameObject.h"


int GameObject::Count = 0;

GameObject::GameObject()
{
	this->id = Count++;
}

GameObject::~GameObject()
{
}


void GameObject::setRect(RectWorld* c)
{
	container = c;
}
int GameObject::getId() const
{
	return id;
}

Color GameObject::getDiffuse() const
{
	return ColorDiffuse;
}
Color GameObject::getAmbient() const
{
	return ColorDiffuse;
}
Color GameObject::getSpecular() const
{
	return ColorDiffuse;
}

void GameObject::setDiffuse(Color diffuse)
{
	ColorDiffuse = diffuse;
}

void GameObject::setAmbient(Color ambient)
{
	ColorAmbient = ambient;
}

void GameObject::setSpecular(Color specular)
{
	ColorSpecular = specular;
}
