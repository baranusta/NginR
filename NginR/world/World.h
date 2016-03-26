#ifndef _WORLD_H_
#define _WORLD_H_

#include <vector>
#include <string>
#include <fstream>

#include "../graphic-library-wrappers/GraphicLibraryWrapper.h"
#include "objects-cpu/game-objects/GameObject.h"
#include "objects-cpu/light/Light.h"
#include "objects-cpu/moving-objects/Moveable.h"
#include "../renderers/IRenderOptionChangeObserver.h"
#include "IStaticWorldChangeObserver.h"


enum RenderOptionNames;
/*
This class is responsible for all the objects in the scene
1. all Objects
2. Light
3. Camera
*/
class World : public IRenderOptionChangedObserver,public Observable
{
public:
	void publishProcessorTypeChanged(RenderOptionNames type, char* text) override;

	World();
	World(Color);
	~World();
	void addWorld(World);
	void addObject(GameObject*);
	void addLight(Vec3<float> pos, Color Ambient, Color Diffuse, Color Specular);
	void addLight(Light light);

	void setGraphicLibrary(Engine::GraphicLibraryWrapper* library);
	void setUpdateType(RenderOptionNames type);
	
	void updateObjects();

	Light getLight() const;
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

	std::vector<GameObject*> getMovingObjects() const
	{
		return moveable_game_objects;
	}

private:

	void _publishStaticWorldChanged(std::vector<GameObject*> objects, std::vector<Light> lights);
	void _updateObjectsSequential();
	void _updateObjectsCUDA();
	void _updateObjectsOpenMP();

	void _setWorldBoundaries(Vec3<float> boundariesFCorner, Vec3<float> boundariesSCorner);

	bool isCUDAenabled;

	//This must be set somehow too..
	ProcessorType pType = CPU;
	RenderOptionNames updateType;
	Engine::GraphicLibraryWrapper* gLibrary;

	Color AmbientColor;

	//Later This Will hold Light Objects
	std::vector<Light> lights;
	std::vector<GameObject*> static_game_objects;
	std::vector<GameObject*> moveable_game_objects;

	std::vector<Moveable*> moveable_list;

	//StaticWorldChangeObservers

	std::forward_list<IStaticWorldChangeObserver*> observers;

	//CUDA Object
	float* cudaObjects;
	float* cudaLights;
	
};



#endif