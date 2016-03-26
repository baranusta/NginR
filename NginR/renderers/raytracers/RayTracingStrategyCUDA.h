#ifndef _RAYTRACINGSTRATEGYCUDA_H_
#define _RAYTRACINGSTRATEGYCUDA_H_

#include "../RenderStrategy.h"
#include "../../world/objects-gpu/SphereGPU.h"

class RayTracingStrategyCUDA : public RenderStrategy
{
public:
	RayTracingStrategyCUDA(float d, float p)
		:RenderStrategy(d, p,GPUCUDA)
	{
		this->name = "CUDA";
	}

	void DrawNextFrame(const Light & light,
		const std::vector<GameObject*>& objects,
		unsigned int* src,
		unsigned int* dst,
		const Vec3<float>& camPos,
		int distance,
		int width,
		int height) override;

	void updateStaticScene(const std::vector<GameObject*>& objects, const std::vector<Light>& lights, int width, int height) override
	{
		
	}
private:
	int elmSize;
};

#endif
