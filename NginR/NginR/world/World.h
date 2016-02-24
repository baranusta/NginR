#ifndef _WORLD_H_
#define _WORLD_H_

#include <vector>
#include <string>
#include <fstream>

#include "../graphic-library-wrappers/GraphicLibraryWrapper.h"
#include "objects-cpu/game-objects/GeometricObject.h"
#include "objects-cpu/light/Light.h"


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
	World(Color, Engine::GraphicLibraryWrapper* gLib);
	~World();
	void AddWorld(World);
	void SetUpdateType(RenderOptionNames type);
	void AddObject(GeometricObject*);
	Light GetLight() const;
	void UpdateObjects(ProcessorType pType);
	int GetObjectSize() const;
	Color GetAmbient() const;

	bool CreateWithFile(std::string);
	void SetCudaEnabled(bool isCudaEnabled);
	void InitGPUMemoryForObjects();

	template<class T>
	void CopyToGPUArray(T *obj);
	template<class T>
	void CopyFromGPUArray(T *obj);

	void AddLight(Vec3<float> pos, Color Ambient, Color Diffuse, Color Specular);
	void AddLight(Light light);
	//This will be removed
	//when the raytracing strategies implemented
	std::vector<GeometricObject*> GetObjects() const
	{
		return Objects;
	}
private:
	void UpdateObjectsSequential();
	void UpdateObjectsCUDA();
	void UpdateObjectsOpenMP();

	void SetWorldBoundaries(Vec3<float> boundariesFCorner, Vec3<float> boundariesSCorner);

	bool isCUDAenabled;

	RenderOptionNames updateType;
	Color AmbientColor;

	Engine::GraphicLibraryWrapper* gLibrary;

	//Later This Will hold Light Objects
	std::vector<Light> lights;
	std::vector<GeometricObject*> Objects;
	
};



#endif