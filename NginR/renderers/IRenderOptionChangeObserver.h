#pragma once
#include "../Observer.h"
#include "../utils/CommonEnums.h"

class IRenderOptionChangedObserver : public Observer
{
public:
	virtual ~IRenderOptionChangedObserver()
	{
		
	};
	virtual void notifyRenderOptionNameChanged(RenderOptionNames type, char* text) = 0;
};
