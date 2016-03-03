#ifndef _OPENGL_H_
#define _OPENGL_H_

#include "../GraphicLibraryWrapper.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cuda_runtime_api.h>
#include <cuda_gl_interop.h>
#include <helper_cuda.h>

namespace Engine
{
	class OpenGLWrapper :public GraphicLibraryWrapper
	{
	public:

		explicit OpenGLWrapper(int window_width_i = 1024, int window_heigt_i = 768);


		void initializeCuda() override;
		void initializeCudaMemory(int size) override;
		void copyObjectsFromCuda(float* objectArr, int size) override;
		void copyObjectsToCuda(float* objectArr, int size) override;
		void updateObjectsAtCudaMemory(std::function<void(float*)>cudaUpdate) override;
		void unMapObjects();

		void changeProcessorType(ProcessorType) override;
		void startMainLoop() override;

		void setMainLoop(void(*fnc)(unsigned int*)) override;
		void setKeyboardEvents(void(*fnc)(unsigned char key, int _x, int _y)) override;
		void setCleanupFunction(void(*fnc)()) override;
		void setTextDisplayFunction(void(*fnc)()) override;
	private:
		int window_width, window_height;

	};

}

#endif 