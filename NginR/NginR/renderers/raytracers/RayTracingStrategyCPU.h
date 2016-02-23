#ifndef _RAYTRACINGSTRATEGYCPU_H_
#define _RAYTRACINGSTRATEGYCPU_H_

#include "../../world/World.h"
#include "../RenderStrategy.h"

class RayTracingStrategyCPU : public RenderStrategy
{
public:
	RayTracingStrategyCPU(float d, float p)
		: RenderStrategy(d, p, CPU)
	{}

	void IterateInnerLoop(World w, Vec3 ViewPort, int i, int k, unsigned int* dst);
private:
	int DetermineColor(Light light, Vec3 ray, Vec3 Normal, Vec3 hitPoint, int objId, std::vector<GeometricObject*>* Objects);
};

#endif