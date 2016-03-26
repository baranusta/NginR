#pragma once
#include "../Observer.h"
#include "../utils/CommonEnums.h"

class IStaticWorldChangeObserver : public Observer
{
public:
	virtual ~IStaticWorldChangeObserver()
	{

	};
	virtual void staticWorldChanged(const std::vector<GameObject*>& objects, const std::vector<Light>& lights) = 0;
};
