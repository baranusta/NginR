#ifndef _GAME_LOOPER_H_
#define _GAME_LOOPER_H_

#include <unordered_map>

#include "world/World.h"
#include "renderers/RenderController.h"
#include "graphic-library-wrappers/GraphicLibraryWrapper.h"
#include "world/objects-cpu/camera/Camera.h"


#include "renderers/raytracers/RayTracingStrategySequential.h"
#include "renderers/raytracers/RayTracingStratingOpenMP.h"
#include "renderers/raytracers/RayTracingStrategyCUDA.h"

typedef std::function<void(unsigned char key, int _x, int _y)> keyboard_listener;


namespace Engine
{

	class Game
	{
	public:

		Game(bool isCudaRequested = false);
		~Game();
		bool getCudaRequest() const;

		void setWorld(World* w);
		void setCamera(Camera* cam);
		void addWorld(const World & w);
		void addObject(GameObject & object);
		void processNextFrame(unsigned int* dst = nullptr);
		void setProcessType(unsigned char key, void(*fnc)(char*));

		void keyboardEvent(unsigned char key, int _x, int _y);
		void addKeyboardListener(std::string uniqueName,keyboard_listener listener);
		void removeKeyboardListener(std::string uniqueName);


	private:

		//World
		friend class GameWrapper;
		World* world;
		Camera* cam;

		bool isCudaRequested;

		std::unordered_map<std::string, keyboard_listener> keyboard_functions;
	};

	class GameWrapper
	{
	public:
		GameWrapper(Game* game)
		{
			world = game->world;
		}
	private:
		World* world;
		friend class Engine;
	};
}

#endif
