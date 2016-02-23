#ifndef _GRAPHICLIBRARY_H_
#define _GRAPHICLIBRARY_H_

#include <functional>
#include "../utils/Utils.h"

namespace Engine
{
	class GraphicLibraryWrapper
	{
	public:
		virtual ~GraphicLibraryWrapper()
		{
		}

		virtual void initializeCuda(int window_width, int window_height) = 0;
		virtual void initializeCudaMemory(int size) = 0;
		virtual void copyObjectsToCuda(float* objectArr,int size) = 0;
		virtual void copyObjectsFromCuda(float* objectArr, int size) = 0;
		virtual void updateObjectsAtCudaMemory(std::function<void(float*)>cudaUpdate) = 0;


		virtual void changeProcessorType(ProcessorType) = 0;
		virtual void setMainLoop(void(*fnc)(unsigned int*)) = 0;
		virtual void setKeyboardEvents(void(*fnc)(unsigned char key, int _x, int _y)) = 0;
		virtual void setCleanupFunction(void(*fnc)()) = 0;
		virtual void setTextDisplayFunction(void(*fnc)()) = 0;
		virtual void startMainLoop() = 0;
	};
}

#endif