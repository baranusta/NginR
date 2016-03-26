#ifndef _RAYTRACINGCONTROLLER_H_
#define _RAYTRACINGCONTROLLER_H_

#include <map>

#include "RenderStrategy.h"
#include "../world/World.h"
#include "../Observer.h"

class RenderController : public Observable
{
public:
	RenderController();
	~RenderController();

	void AddStrategy(RenderOptionNames key, RenderStrategy* strategy);
	void Apply(const Light & light,
		const std::vector<GameObject*>& objects,
								unsigned int* src,
								unsigned int* dst,
								const Vec3<float>& camPos,
								int distance,
								int width,
								int height) const;
	bool SetStrategy(RenderOptionNames key);
	ProcessorType getProcessorType() const;
private:
	void publishRenderOptionChanged(RenderOptionNames key, char* text);
	RenderStrategy* selectedStrategy;
	RenderStrategy** Strategies;
};

#endif
