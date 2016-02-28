#include "Engine.h"
#include <cuda_runtime_api.h>
#include <iostream>

Engine::Game* mainGame;
std::vector<TextViewGL*> textViews;

void keyboard_func(unsigned char key, int _x, int _y)
{
	mainGame->keyboardEvent(key, _x, _y);
}

Engine::Engine::~Engine()
{
	delete graphicLib;
	_deleteArray(textViews);
}



Engine::Engine::Engine()
{
	_constructEngine(OpenGL, true);
}

Engine::Engine::Engine(const GraphicLibraryName & libName, bool showFrame)
{
	_constructEngine(libName, showFrame);
}

void Engine::Engine::setGame(Game* game)
{
	mainGame = game;
	if (game->getCudaRequest() && _isCudaAvailable())
	{
		graphicLib->initializeCuda();
	}
	GameWrapper wrapper(game);
	wrapper.world->setGraphicLibrary(graphicLib);
}

void Engine::Engine::addTextViews(const std::vector<TextViewGL*>& textViewArr)
{
	textViews.reserve(textViews.size() + textViewArr.size());
	textViews.insert(textViews.end(),textViewArr.begin(),textViewArr.end());
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void Engine::Engine::startEngine() const
{
	if (mainGame == nullptr)
	{
		throw Exception(ENGINE_NO_GAME_EXCEPTION);
	}
	graphicLib->startMainLoop();
}

#pragma region private_methods

void Engine::Engine::_constructEngine(const GraphicLibraryName& libName, bool showFrame)
{
	GraphicLibraryWrapperFactory gFactory;
	graphicLib = gFactory.getGraphicLibrary(libName);

	mainGame = nullptr;

	if (showFrame)
	{
		textViews.push_back(new FrameTextViewGL(-0.95f, 0.88f));
	}
	_initializeLoopFunctions();
}

bool Engine::Engine::_isCudaAvailable() const
{
	int deviceCount = 0;
	cudaGetDeviceCount(&deviceCount);
	if (deviceCount > 0)
		return true;

	printf("Cuda is not available. Continue without cuda");
	return false;
}

void Engine::Engine::_initializeLoopFunctions()
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
		mainGame->processNextFrame(dst);
	});

	graphicLib->setCleanupFunction([]()
	{
		std::cout << "yo madafaka";
	});
}

template <class T>
void Engine::Engine::_deleteArray(std::vector<T> arr)
{
	for (T obj : arr)
		delete obj;
	arr.clear();
}

#pragma endregion private_methods  
