#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../moving-objects/Moveable.h"
#include "../../renderers/RenderController.h"
#include "../../IStaticWorldChangeObserver.h"
#include "../../../renderers/raytracers/RayTracingStrategySequential.h"

class Camera : public Moveable, public IStaticWorldChangeObserver
{
public:
	~Camera();
	Camera(Vec3<float> position, float distance, float sceneWidth, float sceneHeight);
	explicit Camera(Vec3<float> position, float distance, float sceneWidth, float sceneHeight, RenderController* controller);

	void rotate(Angle& moveVector) override;
	void move(Vec3<float>& moveVector) override;

	bool setRenderingStrategy(RenderOptionNames key);

	void staticWorldChanged(std::vector<GameObject*> objects, std::vector<Light> lights);
	void renderNextFrame(World& w, unsigned int* dst);

private:
	void memberSetter(Vec3<float> position, float distance, float sceneWidth, float sceneHeight);

	RenderController* renderController;

	Vec3<float> position;
	float distanceToScene, sceneWidth, sceneHeight;
};

#endif