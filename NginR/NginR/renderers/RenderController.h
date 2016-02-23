#ifndef _RAYTRACINGCONTROLLER_H_
#define _RAYTRACINGCONTROLLER_H_

#include <map>

#include "RenderStrategy.h"
#include "../world/World.h"

class RenderController{
public:
	RenderController();
	~RenderController();
	void AddStrategy(RenderOptionNames key, RenderStrategy* strategy);
	void Apply(World w, Vec3 ViewPort, unsigned int* dst) const;
	bool SetStrategy(RenderOptionNames key, void(*fnc)(char*));
	ProcessorType getProcessorType() const;
private:
	RenderStrategy* selectedStrategy;
	std::map<int, RenderStrategy*> Strategies;
};


#endif