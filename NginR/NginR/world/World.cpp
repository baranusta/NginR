#include "World.h"
#include "objects-cpu/game-objects/GameObjectFactory.h"


extern "C" void CudaUpdateObjects(float*, int);

World::World()
{
	AmbientColor = Color(0,0,0);
}

World::World(Color c, Engine::GraphicLibraryWrapper* library)
{
	AmbientColor = c;
	gLibrary = library;
}

World::~World()
{
	Objects.clear();
	lights.clear();
}

void World::AddWorld(World w)
{
	for (Light light : w.lights)
		this->AddLight(light);
	for (GeometricObject* object : w.Objects)
		this->AddObject(object);
	if (isCUDAenabled && updateType != GPUCUDA)
		InitGPUMemoryForObjects();
}

void World::AddObject(GeometricObject* p)
{
	Objects.push_back(p);
}

Color World::GetAmbient() const
{
	return AmbientColor;
}

bool World::CreateWithFile(std::string fileName)
{
	std::ifstream file(fileName);
	if (file.is_open())
	{
		std::string line;
		Vec3<float> fCorner,sCorner;
		file >> fCorner >> sCorner;
		SetWorldBoundaries(fCorner,sCorner);
		file >> line;
		//To pass explanation line in file
		std::getline(file, line);
		std::getline(file, line);

		GameObjectFactory factory;
		while (std::getline(file, line))
		{
			GeometricObject* object = factory.getGameObjectFromLine(line);
			if (object!=nullptr)
				AddObject(object);
		}
		return true;
	}
	return false;
}

void World::SetCudaEnabled(bool isCudaEnabled)
{
	isCUDAenabled = isCudaEnabled;
}

void World::InitGPUMemoryForObjects()
{
	gLibrary->initializeCudaMemory(Objects.size() * 8 * sizeof(float));
}

void World::AddLight(Vec3<float> pos, Color Ambient, Color Diffuse, Color Specular)
{
	AddLight(Light(pos,Ambient,Diffuse,Specular));
}

void World::AddLight(Light light)
{
	lights.push_back(light);
}

Light World::GetLight() const
{
	return lights[0];
}

void World::UpdateObjects(ProcessorType pType)
{
	switch (pType)
	{
	case CPU:
		switch (updateType)
		{
		case Sequential:
			UpdateObjectsSequential();
			break;
		case OpenMP:
			UpdateObjectsOpenMP(); 
			break;
		default:
			UpdateObjectsSequential(); 
			break;
		}
		break;
	case GPUCUDA:
		UpdateObjectsCUDA();
		break;
	}
}

void World::UpdateObjectsOpenMP()
{
	#pragma omp parallel for schedule(static)
	for (int i = 0; i< Objects.size(); i++)
		Objects[i]->Move();
}

void World::UpdateObjectsSequential()
{
	for (GeometricObject* object : Objects)
		object->Move();
}

void World::UpdateObjectsCUDA()
{
	int objectSize = Objects.size();
	gLibrary->updateObjectsAtCudaMemory([objectSize](float* objects)
	{
		CudaUpdateObjects(objects, objectSize);
	});
}

void World::SetUpdateType(RenderOptionNames type)
{
	if (updateType==CUDA)
	{
		if (type!=CUDA)
		{
			float* objectArr = new float[Objects.size() * 8];
			for (int i = 0; i < Objects.size(); i++)
			{
				Vec3<float> pos;
				Color color;
				float r;
				bool toRight;
				Objects[i]->getInfo(pos, r, color, toRight);
				objectArr[i * 8] = pos.getX();
				objectArr[i * 8 + 1] = pos.getY();
				objectArr[i * 8 + 2] = pos.getZ();
				objectArr[i * 8 + 3] = r;
				objectArr[i * 8 + 4] = color.getR();
				objectArr[i * 8 + 5] = color.getG();
				objectArr[i * 8 + 6] = color.getB();
				objectArr[i * 8 + 7] = toRight ? 1.0f : -1.0f;
			}
			gLibrary->copyObjectsFromCuda(objectArr, Objects.size() * 8);
			delete objectArr;
		}
	}
	else
	{
		if (type == CUDA)
		{
			float* objectArr = new float[Objects.size() * 8]; 
			for (int i = 0; i < Objects.size(); i++)
			{
				Vec3<float> pos;
				Color color;
				float r;
				bool toRight;
				Objects[i]->getInfo(pos, r, color, toRight);
				objectArr[i * 8] = pos.getX();
				objectArr[i * 8 + 1] = pos.getY();
				objectArr[i * 8 + 2] = pos.getZ();
				objectArr[i * 8 + 3] = r;
				objectArr[i * 8 + 4] = color.getR();
				objectArr[i * 8 + 5] = color.getG();
				objectArr[i * 8 + 6] = color.getB();
				objectArr[i * 8 + 7] = toRight ? 1.0f : -1.0f;
			}
			gLibrary->copyObjectsFromCuda(objectArr, Objects.size() * 8);
			delete objectArr;
		}
	}
	updateType = type;
}

int World::GetObjectSize() const
{
	return Objects.size();
}

#pragma region private_methods
template<class T>
void World::CopyToGPUArray(T *obj)
{
	
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
		Objects[i]->getInfo(pos, r, color, toRight);
		obj[i * 8] = pos.getX();
		obj[i * 8 + 1] = pos.getY();
		obj[i * 8 + 2] = pos.getZ();
		obj[i * 8 + 3] = r;
		obj[i * 8 + 4] = color.getR();
		obj[i * 8 + 5] = color.getG();
		obj[i * 8 + 6] = color.getB();
		obj[i * 8 + 7] = toRight ? 1.0f : -1.0f;
	}
}

void World::SetWorldBoundaries(Vec3<float> boundariesFCorner, Vec3<float> boundariesSCorner)
{
	
}

#pragma endregion private_methods