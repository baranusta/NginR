#ifndef _RAYTRACINGSTRATEGY_H_
#define _RAYTRACINGSTRATEGY_H_

#include "../utils/Utils.h"
#include "../world/World.h"

class RenderStrategy{
public:
	RenderStrategy(float d, float p, ProcessorType type)
		:diffuseConst(d), phongPower(p), pType(type)
	{
	}

	virtual ~RenderStrategy()
	{
		delete name;
	}

	virtual void DrawNextFrame(const Light & light, 
		const std::vector<GameObject*>& objects,
		unsigned int* src,
		unsigned int* dst,
		const Vec3<float>& camPos,
		int distance,
		int width,
		int height) = 0;
	//virtual void setUpStaticScene(std::vector<GameObject*> staticObjectsArr);

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
