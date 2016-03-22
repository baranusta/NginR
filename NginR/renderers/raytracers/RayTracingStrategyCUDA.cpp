#include "RayTracingStrategyCUDA.h"

int window_width2 = 5;
int window_height2 = 5;



extern "C" void CudaRayTrace(float*, unsigned int*, int, int,int);
extern "C" void FreeMemoryOnGPU();


void RayTracingStrategyCUDA::DrawNextFrame(const Light & light,
	const std::vector<GameObject*>& objects,
	unsigned int* src,
	unsigned int* dst,
	const Vec3<float>& camPos,
	int distance,
	int width,
	int height)
{
	//CudaRayTrace(w.getCudaObjects(), dst, screenSizeX, screenSizeY, w.getObjectSize());
	//w.unmapCUDAObjects();
}
