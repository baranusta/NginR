#include "Engine.h"
#include <cuda_runtime_api.h>
#include <iostream>

Engine::GameLooper* mLooper;
std::vector<TextViewGL*> textViews;
TextViewGL*Mode = nullptr;


void keyboard_func(unsigned char key, int _x, int _y)
{
	mLooper->setProcessType(key, [](char* str){
		Mode->SetText(str);
	});
}


Engine::Engine::~Engine()
{
	delete graphicLib;
	DeleteArray(textViews);
}


Engine::Engine::Engine(GraphicLibraryWrapper* mGraphicLib, bool startWithCuda) :
	graphicLib(mGraphicLib), mainLooper(GameLooper(startWithCuda && isCudaAvailable(), mGraphicLib))
{
	mLooper = &mainLooper;
	//Sequential is alreadyAdded.


	textViews.push_back(new FrameTextViewGL(-0.95f, 0.88f));
	Mode = new TextViewGL(-0.95f, 0.88f);
	textViews.push_back(Mode);

	initializeLoopFunctions();

	keyboard_func('1', 0, 0);
}
void Engine::Engine::setTextViews(const std::vector<TextViewGL*>& textViewArr)
{
	textViews = textViewArr;
	if (textViews.size() > 0)
		Mode = textViews[0];
}

void Engine::Engine::startEngine()
{

	World world(Color(0.3f,0.3f, 0.3f), graphicLib);

	world.CreateWithFile("World.txt");
	world.AddLight(Vec3<float>(0.f, 0.f, 500.f),
		Color(0.1f, 0.1f, 0.1f),
		Color(0.8f, 0.8f, 0.8f),
		Color(1.f, 1.f, 1.f));
	mainLooper.setWorld(world);
}

void Engine::Engine::playGame() const
{
	graphicLib->startMainLoop();
}

#pragma region private_methods
bool Engine::Engine::isCudaAvailable() const
{
	int deviceCount = 0;
	cudaGetDeviceCount(&deviceCount);
	if (deviceCount > 0)
		return true;

	printf("Cuda is not available. Continue without cuda");
	return false;
}

void Engine::Engine::initializeLoopFunctions()
{
	graphicLib->setTextDisplayFunction([]()
	{
		for (TextViewGL *v : textViews)
		{
			v->draw();
		}
	});

	graphicLib->setKeyboardEvents(keyboard_func);

	graphicLib->setMainLoop([](unsigned int* dst)
	{
		mLooper->processNextFrame(dst);
	});

	graphicLib->setCleanupFunction([]()
	{
		std::cout << "yo madafaka";
	});
}

template <class T>
void Engine::Engine::DeleteArray(std::vector<T> arr)
{
	for (T obj : arr)
		delete obj;
	arr.clear();
}

#pragma endregion private_methods  
