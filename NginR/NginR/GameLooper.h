#ifndef _GAME_LOOPER_H_
#define _GAME_LOOPER_H_
#include "world/World.h"
#include "renderers/RenderController.h"
#include "graphic-library-wrappers/GraphicLibraryWrapper.h"


#include "renderers/raytracers/RayTracingStrategySequential.h"
#include "renderers/raytracers/RayTracingStratingOpenMP.h"
#include "renderers/raytracers/RayTracingStrategyCUDA.h"

namespace Engine
{
	class GameLooper
	{
	public:
		GameLooper();
		GameLooper(bool withCuda, GraphicLibraryWrapper* gLibrary);
		~GameLooper();
		void setWorld(const World & w);
		void addWorld(const World & w);
		void addRenderingStrategy(RenderOptionNames rType, RenderStrategy* strategy);
		void processNextFrame(unsigned int* dst = nullptr);
		void setProcessType(unsigned char key, void(*fnc)(char*));

	private:

		bool isCudaEnabled;

		//RayTracers
		RenderController mRenderController;
		//World
		World world;

		GraphicLibraryWrapper* gLibrary;
	};
}

#endif
