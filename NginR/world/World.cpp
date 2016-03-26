#include "World.h"
#include "objects-cpu/game-objects/GameObjectFactory.h"


extern "C" void CudaUpdateObjects(float*, int);

World::World() 
{
	AmbientColor = Color(0,0,0);
	gLibrary = nullptr;
}

World::World(Color c)
{
	AmbientColor = c;
	gLibrary = nullptr;
}

World::~World()
{
	static_game_objects.clear();
	moveable_game_objects.clear();
	lights.clear();
}

void World::addWorld(World w)
{
	for (Light light : w.lights)
		this->addLight(light);

	for (GameObject* object : w.static_game_objects) static_game_objects.push_back(object);
	for (GameObject* object : w.moveable_game_objects) moveable_game_objects.push_back(object);
	for (Moveable* object : w.moveable_list) moveable_list.push_back(object);

	if (isCUDAenabled && updateType != GPUCUDA)
		initGPUMemoryForObjects();
}

void World::addObject(GameObject* p)
{
	if (Moveable* moveable = dynamic_cast< Moveable* >(p))
	{
		moveable_list.push_back(moveable);
		moveable_game_objects.push_back(p);
	}
	else
	{
		static_game_objects.push_back(p);
	}
}

Color World::getAmbient() const
{
	return AmbientColor;
}

bool World::createWithFile(std::string fileName)
{
	std::ifstream file(fileName);
	if (file.is_open())
	{
		std::string line;
		Vec3<float> fCorner,sCorner;
		file >> fCorner >> sCorner;
		_setWorldBoundaries(fCorner,sCorner);
		file >> line;
		//To pass explanation line in file
		std::getline(file, line);

		GameObjectFactory factory;
		while (std::getline(file, line))
		{
			GameObject* object = factory.getGameObjectFromLine(line);
			if (object!=nullptr)
				addObject(object);
		}
		return true;
	}
	return false;
}

void World::setCudaEnabled(bool isCudaEnabled)
{
	isCUDAenabled = isCudaEnabled;
}

void World::initGPUMemoryForObjects()
{
	//gLibrary->initializeCudaMemory(Objects.size() * 8 * sizeof(float));
}

void World::unmapCUDAObjects()
{
	gLibrary->unMapObjects();
}

void World::addLight(Vec3<float> pos, Color Ambient, Color Diffuse, Color Specular)
{
	addLight(Light(pos,Ambient,Diffuse,Specular));
}

void World::addLight(Light light)
{
	lights.push_back(light);
}

void World::setGraphicLibrary(Engine::GraphicLibraryWrapper* library)
{
	gLibrary = library;
}

Light World::getLight() const
{
	return lights[0];
}


float* World::getCudaObjects() const
{
	return cudaObjects;
}

void World::updateObjects()
{
	switch (pType)
	{
	case CPU:
		switch (updateType)
		{
		case Sequential:
			_updateObjectsSequential();
			break;
		case OpenMP:
			_updateObjectsOpenMP(); 
			break;
		default:
			_updateObjectsSequential(); 
			break;
		}
		break;
	case GPUCUDA:
		_updateObjectsCUDA();
		break;
	}
}

void World::_updateObjectsOpenMP()
{
	#pragma omp parallel for schedule(static)
	for (int i = 0; i< moveable_list.size(); i++)
		moveable_list[i]->update();
}

void World::_publishStaticWorldChanged(std::vector<GameObject*> objects, std::vector<Light> lights)
{

	for (Observer* obs : observers)
		if (IStaticWorldChangeObserver* c = dynamic_cast<IStaticWorldChangeObserver*>(obs))
		{
			c->staticWorldChanged(objects, lights);
		}
}

void World::_updateObjectsSequential()
{
	for (Moveable* object : moveable_list)
		object->update();
}

void World::_updateObjectsCUDA()
{
	//int objectSize = Objects.size();
	//float* &wow = cudaObjects;
	//gLibrary->updateObjectsAtCudaMemory([objectSize,&wow](float* objects)
	//{
	//	wow = objects;
	//	CudaUpdateObjects(objects, objectSize);
	//});
}

void World::notifyRenderOptionNameChanged(RenderOptionNames type, char* text)
{
	updateType = type;
}

void World::attachObserver(Observer* observer)
{
	Observable::attachObserver(observer);
	if (IStaticWorldChangeObserver* staticWorldObserver = dynamic_cast<IStaticWorldChangeObserver*>(observer))
		staticWorldObserver->staticWorldChanged(static_game_objects, lights);
}

void World::setUpdateType(RenderOptionNames type)
{
	if (updateType==CUDA)
	{
		if (type!=CUDA)
		{
			//float* objectArr = new float[Objects.size() * 8];
			//for (int i = 0; i < Objects.size(); i++)
			//{
			//	Vec3<float> pos;
			//	Color color;
			//	float r;
			//	bool toRight;
			//	//Objects[i]->getInfo(pos, r, color, toRight);
			//	//objectArr[i * 8] = pos.getX();
			//	//objectArr[i * 8 + 1] = pos.getY();
			//	//objectArr[i * 8 + 2] = pos.getZ();
			//	//objectArr[i * 8 + 3] = r;
			//	//objectArr[i * 8 + 4] = color.getR();
			//	//objectArr[i * 8 + 5] = color.getG();
			//	//objectArr[i * 8 + 6] = color.getB();
			//	//objectArr[i * 8 + 7] = toRight ? 1.0f : -1.0f;
			//}
			//gLibrary->copyObjectsFromCuda(objectArr, Objects.size() * 8);
			//delete objectArr;
		}
	}
	else
	{
		/*if (type == CUDA)
		{
			float* objectArr = new float[Objects.size() * 8]; 
			
			CopyToGPUArray(objectArr);
			gLibrary->copyObjectsToCuda(objectArr, Objects.size() * 8);
			delete objectArr;
		}*/
	}
	updateType = type;
}

#pragma region private_methods
template<class T>
void World::CopyToGPUArray(T *obj)
{
	for (int i = 0; i < Objects.size(); i++)
	{
		Vec3<float> pos;
		Color color;
		float r;
		bool toRight;
		//Objects[i]->getInfo(pos, r, color, toRight);
		//obj[i * 8] = pos.getX();
		//obj[i * 8 + 1] = pos.getY();
		//obj[i * 8 + 2] = pos.getZ();
		//obj[i * 8 + 3] = r;
		//obj[i * 8 + 4] = color.getR();
		//obj[i * 8 + 5] = color.getG();
		//obj[i * 8 + 6] = color.getB();
		//obj[i * 8 + 7] = toRight ? 1.0f : -1.0f;
	}
}

template<class T>
void World::CopyFromGPUArray(T *obj)
{
	for (int i = 0; i < Objects.size(); i++)
	{
		Vec3<float> pos;
		Color color;
		float r;
		bool toRight;
		//Objects[i]->getInfo(pos, r, color, toRight);
		//obj[i * 8] = pos.getX();
		//obj[i * 8 + 1] = pos.getY();
		//obj[i * 8 + 2] = pos.getZ();
		//obj[i * 8 + 3] = r;
		//obj[i * 8 + 4] = color.getR();
		//obj[i * 8 + 5] = color.getG();
		//obj[i * 8 + 6] = color.getB();
		//obj[i * 8 + 7] = toRight ? 1.0f : -1.0f;
	}
}

void World::_setWorldBoundaries(Vec3<float> boundariesFCorner, Vec3<float> boundariesSCorner)
{
	
}

#pragma endregion private_methods