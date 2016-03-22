#ifndef _RAYTRACINGSTRATEGYSEQUENTIAL_H_
#define _RAYTRACINGSTRATEGYSEQUENTIAL_H_

#include "RayTracingStrategyCPU.h"


class RayTracingStrategySequential : public RayTracingStrategyCPU
{
public:

	RayTracingStrategySequential(float d, float p)
		: RayTracingStrategyCPU(d, p)
	{
		this->name = "CPU";
	}

	void DrawNextFrame(const Light & light,
		const std::vector<GameObject*>& objects,
		unsigned int* src,
		unsigned int* dst,
		const Vec3<float>& camPos,
		int distance,
		int width,
		int height)
	{
		for (int i = -height / 2, k = 0; i < height / 2; i++)
		{
			IterateInnerLoop(light, objects, width, i, k, dst);
			k += width;
		}
	}
};

#endif