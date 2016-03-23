#include <iostream>
#include <Engine.h>
#include <world/objects-cpu/game-objects/Triangle.h>
#include <world/objects-cpu/game-objects/Sphere.h>
#include <world/objects-cpu/moving-objects/MoveableTriangle.h>
#include <world/objects-cpu/moving-objects/MoveableSphere.h>


class textController : public IRenderOptionChangedObserver
{
public:
	textController() :mode(TextViewGL(-0.95, 0.88))
	{

	}

	void publishProcessorTypeChanged(RenderOptionNames type, char* text) override
	{
		mode.SetText(text);
	}

	void addTextsToScene(std::vector<TextViewGL*>& textViewArr)
	{
		textViewArr.push_back(&mode);
	}
private:
	TextViewGL mode;
};
textController* text;
#define KEYBOARD_LISTENER_FOR_RENDER "processorBidisi"
#define KEYBOARD_LISTENER_FOR_TRIANGLE "HizliDonCanisi"

class DemoGame : public Engine::Game
{
public:

	DemoGame(bool willCudaRender) : Game(willCudaRender)
	{
		RenderController* renderer = new RenderController();
		renderer->AddStrategy(Sequential, new RayTracingStrategySequential(0.8f, 20.0));
		renderer->AddStrategy(OpenMP, new RayTracingStrategyOpenMP(0.8f, 20.0));
		if (willCudaRender)
		{
			renderer->AddStrategy(CUDA, new RayTracingStrategyCUDA(0.8f, 20.0));
		}

		Camera* cam = new Camera(Vec3<float>(-2000,0,0),2000,768,512,renderer);
		
		auto listener = [this,cam](unsigned char key, int x, int y)
		{
			if (key == '1' || key == '2' || key == '3')
			{
				cam->setRenderingStrategy(RenderOptionNames((int)(key - '1')));
			}
		};

		addKeyboardListener(KEYBOARD_LISTENER_FOR_RENDER, listener);
		World* world = new World(Color(0.3f, 0.3f, 0.3f));
		
		world->addLight(Vec3<float>(0.f, 0.f, 500.f),
			Color(0.1f, 0.1f, 0.1f),
			Color(0.8f, 0.8f, 0.8f),
			Color(1.f, 1.f, 1.f));

		addTriangle(*world);
		zPos = -150;
		addSpheres(*world);
		addSpheres(*world);
		addSpheres(*world);
		
		addSpheres(*world);
		addSpheres(*world);
		addSpheres(*world);

		setWorld(world);
		setCamera(cam);

		renderer->registerObservingEvent(text);
		renderer->registerObservingEvent(world);
		listener('1', 0, 0);
	}
private:

	int zPos;
	void addTriangle(World& w)
	{
		MoveableTriangle* object = new MoveableTriangle(Vec3<float>(0, 50, 0),
			Vec3<float>(0, -50, 0),
			Vec3<float>(0, 0, 50));

		object->setDiffuse(Color(1, 0.4, 0.7));
		object->setAmbient(Color(1, 1, 1));
		object->setSpecular(Color(1, 1, 1));
		object->rotate(Angle(0,80, 0, Angle::DEGREE));
		object->setUpdateFunction([object]()
		{
			Angle wow(0, 2, 0, Angle::DEGREE);
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
		MoveableSphere* sphere = new MoveableSphere(Vec3<float>(0, 0, zPos), 75);
		zPos += 40;
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


Vec3<int> ViewPort(23000, 768, 512);
int main()
{
	Engine::Engine Enginar;

	text = new textController();
	std::vector<TextViewGL*> textViewArr;
	text->addTextsToScene(textViewArr);
	Enginar.addTextViews(textViewArr);

	DemoGame mGame(true);
	Enginar.setGame(&mGame);
	Enginar.startEngine();
	return 0;
}