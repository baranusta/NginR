#include <iostream>
#include <Engine.h>
TextViewGL* mode;


#define KEYBOARD_LISTENER_FOR_RENDER "processorBidisi"

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

		world->createWithFile("World.txt");
		world->addLight(Vec3<float>(0.f, 0.f, 500.f),
			Color(0.1f, 0.1f, 0.1f),
			Color(0.8f, 0.8f, 0.8f),
			Color(1.f, 1.f, 1.f));

		setWorld(world);
		listener('1', 0, 0);
	}
	~DemoGame()
	{
		removeKeyboardListener(KEYBOARD_LISTENER_FOR_RENDER);
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
	//Engine::Engine a;
	//a.startEngine();
	mode = nullptr;
	Engine::Engine Enginar;
	addTexts(Enginar);
	DemoGame mGame(true);
	Enginar.setGame(&mGame);
	Enginar.startEngine();
	return 0;
}