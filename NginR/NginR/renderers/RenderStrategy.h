#ifndef _RAYTRACINGSTRATEGY_H_
#define _RAYTRACINGSTRATEGY_H_

#include "../utils/Utils.h"
#include "../world/World.h"

class RenderStrategy{
public:
	RenderStrategy(float d, float p,ProcessorType type)
		:diffuseConst(d), phongPower(p), pType(type)
	{
	}

	virtual ~RenderStrategy()
	{
		delete name;
	}

	virtual void DrawNextFrame(World w, Vec3<int> ViewPort, unsigned int* dst) = 0;
	
	char* GetName() const
	{
		return name;
	}

	ProcessorType getProcessorType() const
	{
		return pType;
	}

protected:
	ProcessorType pType;
	const float diffuseConst;
	const float phongPower;
	char* name;
};

#endif