#ifndef _RAYTRACINGSTRATEGYOPENMP_H_
#define _RAYTRACINGSTRATEGYOPENMP_H_

#include "RayTracingStrategyCPU.h"

class RayTracingStrategyOpenMP : public RayTracingStrategyCPU
{
public:

	RayTracingStrategyOpenMP(float d, float p)
		: RayTracingStrategyCPU(d, p)
	{
		this->name = "OpenMP";
	}

	void DrawNextFrame(const Light & light,
		const std::vector<GameObject*>& objects,
		unsigned int* src,
		unsigned int* dst,
		const Vec3<float>& camPos,
		int distance,
		int width,
		int height) override
	{
		int i;
		int min = -height / 2;
		int max = height / 2;
		#pragma omp parallel for num_threads(4) private(i)
			for (i = min; i < max; i++)
			{
				int k = (i - min) * width;
				IterateInnerLoop(light,objects, width, i, k, dst);
			}
	}
};
#endif