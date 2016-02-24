#ifndef _RAYTRACINGSTRATEGYCUDA_H_
#define _RAYTRACINGSTRATEGYCUDA_H_

#include "../RenderStrategy.h"
#include "../../world/objects-gpu/SphereGPU.h"

class RayTracingStrategyCUDA : public RenderStrategy
{
public:
	RayTracingStrategyCUDA(float d, float p)
		:RenderStrategy(d, p, GPUCUDA)
	{
		this->name = "CUDA";
	}

	void DrawNextFrame(World w, Vec3<int> ViewPort, unsigned int* dst) override;
private:
	int elmSize;
};

#endif
