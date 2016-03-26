#include "Camera.h"

Camera::~Camera()
{
	delete renderController;
}


Camera::Camera(Vec3<float> position, float distance, float sceneWidth, float sceneHeight)
{
	memberSetter(position, distance, sceneWidth, sceneHeight);
	renderController = new RenderController();
	renderController->AddStrategy(Sequential, new RayTracingStrategySequential(0.8f, 20.0));
}

Camera::Camera(Vec3<float> position, float distance, float sceneWidth, float sceneHeight, RenderController* controller)
{
	renderController = controller;
	memberSetter(position, distance, sceneWidth, sceneHeight);
	this->renderController = controller;
}

void Camera::memberSetter(Vec3<float> position, float distance, float sceneWidth, float sceneHeight)
{
	this->position = position;
	this->distanceToScene = distance;
	this->sceneWidth = sceneWidth;
	this->sceneHeight = sceneHeight;
}

bool Camera::setRenderingStrategy(RenderOptionNames key)
{
	return renderController->SetStrategy(key);
}

void Camera::staticWorldChanged(std::vector<GameObject*> objects, std::vector<Light> lights)
{
}

void Camera::renderNextFrame(World& w, unsigned* dst)
{
	unsigned int* src = new unsigned int[(int)sceneWidth * sceneHeight]();
	renderController->Apply(w.getLight(), w.getMovingObjects(), src, dst, position, distanceToScene, sceneWidth, sceneHeight);
	delete src;
}

void Camera::rotate(Angle& moveVector)
{
}

void Camera::move(Vec3<float>& moveVector)
{
}
