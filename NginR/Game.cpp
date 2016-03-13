#include "Game.h"

float eyePosx = -25000;

Vec3<int> ViewPort(eyePosx + 23000, 768, 512);
Vec3<float> eyePos(eyePosx, 0, 0);
Angle ViewPortAngle(0, 0, 0, Angle::DEGREE);


Engine::Game::Game(bool isCudaRequested) : isCudaRequested(isCudaRequested)
{
	
}

Engine::Game::~Game()
{
}

bool Engine::Game::getCudaRequest() const
{
	return this->isCudaRequested;
}

void Engine::Game::setWorld(World* w)
{
	this->world = w;
}

void Engine::Game::addWorld(const World & w)
{
	this->world->addWorld(w);
}

void Engine::Game::addObject(GameObject& object)
{
	world->addObject(&object);
}

void Engine::Game::addRenderingStrategy(RenderOptionNames rType, RenderStrategy* strategy)
{
	mRenderController.AddStrategy(rType, strategy);
}

void Engine::Game::processNextFrame(unsigned int* dst)
{
	world->updateObjects(mRenderController.getProcessorType());
	mRenderController.Apply(*world, ViewPort, dst);
}

void Engine::Game::setProcessType(unsigned char key, void(*fnc)(char*))
{
	if (key == '1' || key == '2' || key == '3')
	{
		if(mRenderController.SetStrategy(RenderOptionNames((int)(key - '1')), fnc));
			world->setUpdateType(RenderOptionNames((int)(key - '1')));
	}
}

void Engine::Game::keyboardEvent(unsigned char key, int _x, int _y)
{
	for (auto keyboardListener: keyboard_functions)
	{
		keyboardListener.second(key, _x, _y);
	}
}

void Engine::Game::addKeyboardListener(std::string uniqueName, keyboard_listener listener)
{
	auto isNameExist = keyboard_functions.find(uniqueName);
	if (isNameExist != keyboard_functions.end())
		throw Exception(KEYBOARD_LISTENER_ALREADY_ADDED);
	keyboard_functions[uniqueName] = listener;
}

void Engine::Game::removeKeyboardListener(std::string uniqueName)
{
	keyboard_functions.erase(uniqueName);
}
