#pragma once
#include "../Observer.h"
#include "../utils/CommonEnums.h"

class IRenderOptionChangedObserver : public Observer
{
public:
	virtual ~IRenderOptionChangedObserver()
	{

	};
	virtual void publishProcessorTypeChanged(RenderOptionNames type, char* text) = 0;
};
