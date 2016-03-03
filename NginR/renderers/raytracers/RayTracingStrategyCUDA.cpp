#include "RayTracingStrategyCUDA.h"

int window_width2 = 5;
int window_height2 = 5;



extern "C" void CudaRayTrace(float*, unsigned int*, int, int,int);
extern "C" void FreeMemoryOnGPU();


void RayTracingStrategyCUDA::DrawNextFrame(World& w, Vec3<int> ViewPort, unsigned int* dst)
{
	CudaRayTrace(w.getCudaObjects(), dst, ViewPort.getY(), ViewPort.getX(), w.getObjectSize());
	w.unmapCUDAObjects();
}
