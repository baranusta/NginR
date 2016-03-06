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

	void IterateInnerLoop(const World& w, Vec3<int> ViewPort, int i, int k, unsigned int* dst);
private:
	int DetermineColor(Light& light, Vec3<float>& ray, Vec3<float>& Normal, Vec3<float>& hitPoint, int objId, std::vector<GeometricObject*>* Objects) const;
};

#endif