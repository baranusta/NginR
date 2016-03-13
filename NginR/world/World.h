#ifndef _WORLD_H_
#define _WORLD_H_

#include <vector>
#include <string>
#include <fstream>

#include "../graphic-library-wrappers/GraphicLibraryWrapper.h"
#include "objects-cpu/game-objects/GameObject.h"
#include "objects-cpu/light/Light.h"
#include "objects-cpu/moving-objects/Moveable.h"


enum RenderOptionNames;

/*
This class is responsible for all the objects in the scene
1. all Objects
2. Light
3. Camera
*/
class World
{
public:

	World();
	World(Color);
	~World();
	void addWorld(World);
	void addObject(GameObject*);
	void addLight(Vec3<float> pos, Color Ambient, Color Diffuse, Color Specular);
	void addLight(Light light);

	void setGraphicLibrary(Engine::GraphicLibraryWrapper* library);
	void setUpdateType(RenderOptionNames type);
	void updateObjects(ProcessorType pType);

	Light getLight() const;
	int getObjectSize() const;
	Color getAmbient() const;
	float* getCudaObjects() const;

	bool createWithFile(std::string);
	void setCudaEnabled(bool isCudaEnabled);
	void initGPUMemoryForObjects();
	void unmapCUDAObjects();

	template<class T>
	void CopyToGPUArray(T *obj);
	template<class T>
	void CopyFromGPUArray(T *obj);

	//This will be removed
	//when the raytracing strategies implemented
	std::vector<GameObject*> GetObjects() const
	{
		return Objects;
	}

private:
	void _updateObjectsSequential();
	void _updateObjectsCUDA();
	void _updateObjectsOpenMP();

	void _setWorldBoundaries(Vec3<float> boundariesFCorner, Vec3<float> boundariesSCorner);

	bool isCUDAenabled;

	RenderOptionNames updateType;
	Engine::GraphicLibraryWrapper* gLibrary;

	Color AmbientColor;

	//Later This Will hold Light Objects
	std::vector<Light> lights;
	std::vector<GameObject*> Objects;
	std::vector<Moveable*> moveable_objects;

	//CUDA Object
	float* cudaObjects;
	float* cudaLights;
	
};



#endif