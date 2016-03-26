#pragma once
#include "../Observer.h"
#include "../utils/CommonEnums.h"

class IStaticWorldChangeObserver : public Observer
{
public:
	virtual ~IStaticWorldChangeObserver()
	{

	};
	virtual void staticWorldChanged(std::vector<GameObject*> objects, std::vector<Light> lights) = 0;
};
