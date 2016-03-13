#include <iostream>
#include <Engine.h>
#include <world/objects-cpu/game-objects/Triangle.h>
#include <world/objects-cpu/game-objects/Sphere.h>
#include <world/objects-cpu/moving-objects/MoveableTriangle.h>
#include <world/objects-cpu/moving-objects/MoveableSphere.h>
TextViewGL* mode;


#define KEYBOARD_LISTENER_FOR_RENDER "processorBidisi"
#define KEYBOARD_LISTENER_FOR_TRIANGLE "HizliDonCanisi"

class DemoGame : public Engine::Game
{
public:

	DemoGame(bool willCudaRender) : Game(willCudaRender)
	{
		addRenderingStrategy(Sequential, new RayTracingStrategySequential(0.8f, 20.0));
		addRenderingStrategy(OpenMP, new RayTracingStrategyOpenMP(0.8f, 20.0));
		if (willCudaRender)
		{
			addRenderingStrategy(CUDA, new RayTracingStrategyCUDA(0.8f, 20.0));
		}

		auto listener = [this](unsigned char key, int x, int y)
		{
			this->setProcessType(key, [](char* str)
			{
				if (mode != nullptr)
					mode->SetText(str);
			});
		};

		addKeyboardListener(KEYBOARD_LISTENER_FOR_RENDER, listener);
		World* world = new World(Color(0.3f, 0.3f, 0.3f));
		
		world->addLight(Vec3<float>(0.f, 0.f, 500.f),
			Color(0.1f, 0.1f, 0.1f),
			Color(0.8f, 0.8f, 0.8f),
			Color(1.f, 1.f, 1.f));

		addTriangle(*world);
		addSpheres(*world);
		
		setWorld(world);
		listener('1', 0, 0);
	}
private:
	void addTriangle(World& w)
	{
		MoveableTriangle* object = new MoveableTriangle(Vec3<float>(0, 50, 0),
			Vec3<float>(0, -50, 0),
			Vec3<float>(0, 0, 50));

		object->setUpdateFunction([object]()
		{
			Angle wow(2, 0, 0, Angle::DEGREE);
			object->rotate(wow);
		});

		auto listener = [object](unsigned char key, int x, int y)
		{
			Angle wow(Angle(20, 0, 0, Angle::DEGREE));
			object->rotate(wow);
			if (key == 'a')
				object->setSpeed(Vec3<float>(0, -2, 0));
			else if (key == 'd')
				object->setSpeed(Vec3<float>(0, 2, 0));

		};

		addKeyboardListener(KEYBOARD_LISTENER_FOR_TRIANGLE, listener);

		w.addObject(object);
	};
	void addSpheres(World& w)
	{
		MoveableSphere* sphere = new MoveableSphere(Vec3<float>(0, 100, 150), 75);
		sphere->setDiffuse(Color(1, 0.4, 0.7));
		sphere->setAmbient(Color(18, 80, 26));
		sphere->setSpecular(Color(82, 23, 32));

		sphere->setSpeed(Vec3<float>(0, 1,0));

		sphere->setUpdateFunction([sphere]()
		{
			Vec3<float> speed = sphere->getSpeed();
			if (sphere->getMaxY() >= 300 || sphere->getMinY() <= -300)
			{
				speed = speed * -1;
				sphere->setSpeed(speed);
			}
		});

		w.addObject(sphere);
	}
};

void addTexts(Engine::Engine& Enginar)
{
	std::vector<TextViewGL*> textViewArr;
	mode = new TextViewGL(-0.95, 0.88);
	textViewArr.push_back(mode);
	Enginar.addTextViews(textViewArr);
}


int main()
{
	mode = nullptr;
	Engine::Engine Enginar;
	addTexts(Enginar);
	DemoGame mGame(true);
	Enginar.setGame(&mGame);
	Enginar.startEngine();
	return 0;
}