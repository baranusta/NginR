#ifndef _RAYTRACINGSTRATEGYCPU_H_
#define _RAYTRACINGSTRATEGYCPU_H_

#include "../../world/World.h"
#include "../RenderStrategy.h"

#define MAX_DISTANCE (100000.f);

class RayTracingStrategyCPU : public RenderStrategy
{
public:
	RayTracingStrategyCPU(float d, float p)
		: RenderStrategy(d, p, CPU)
	{}
	
	void IterateInnerLoop(const Light & light, const std::vector<GameObject*>& objects, int screenSizeX, int i, int k, unsigned int* dst);

protected:
	struct StaticSceneElement
	{
		StaticSceneElement() :color(Color(0.3f, 0.3f, 0.3f).rgbToInt())
		{
			distanceToScene = MAX_DISTANCE;
		}
		int color;
		float distanceToScene;
	};
	StaticSceneElement* staticScene;

private:
	int DetermineColor(const Light& light, Vec3<float>& ray, Vec3<float>& Normal, Vec3<float>& hitPoint, int objId, const std::vector<GameObject*>& Objects) const;
};

#endif