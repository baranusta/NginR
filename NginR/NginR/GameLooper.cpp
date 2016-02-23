#include "GameLooper.h"

float eyePosx = -25000;

Vec3 ViewPort(eyePosx + 23000, 768, 512);
Vec3 eyePos(eyePosx, 0, 0);
Angle ViewPortAngle(0, 0, 0);


Engine::GameLooper::GameLooper()
{

}

Engine::GameLooper::GameLooper(bool withCuda,GraphicLibraryWrapper* gLibrary)
{
	isCudaEnabled = withCuda;
	this->gLibrary = gLibrary;

	addRenderingStrategy(Sequential, new RayTracingStrategySequential(0.8f, 20.0));
	addRenderingStrategy(OpenMP, new RayTracingStrategyOpenMP(0.8f, 20.0));
	addRenderingStrategy(CUDA, new RayTracingStrategyCUDA(0.8f, 20.0));
}

Engine::GameLooper::~GameLooper()
{
}

void Engine::GameLooper::setWorld(const World & w)
{
	this->world = w;
}

void Engine::GameLooper::addWorld(const World & w)
{
	this->world.AddWorld(w);
}

void Engine::GameLooper::addRenderingStrategy(RenderOptionNames rType, RenderStrategy* strategy)
{
	mRenderController.AddStrategy(rType, strategy);
}

void Engine::GameLooper::processNextFrame(unsigned int* dst)
{
	world.UpdateObjects(mRenderController.getProcessorType());
	mRenderController.Apply(world, ViewPort, dst);
}

void Engine::GameLooper::setProcessType(unsigned char key, void(*fnc)(char*))
{
	if (key == '1' || key == '2' || key == '3')
	{
		mRenderController.SetStrategy(RenderOptionNames((int)(key - '1')), fnc);
		world.SetUpdateType(RenderOptionNames((int)(key - '1')));
	}
}