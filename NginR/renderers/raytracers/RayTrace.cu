
#include <cuda.h>
#include <cuda_runtime.h>
#include "device_launch_parameters.h"
#include <iostream>

int elmSize;

struct vector3{
	float x;
	float y;
	float z;
	__device__ vector3(float X, float Y, float Z) : x(X), y(Y), z(Z)
	{}

	__device__ vector3()
	{}
	__device__ vector3 operator-(vector3 a)
	{
		vector3 result(x - a.x, y - a.y, z - a.z);
		return result;
	}
	__device__ vector3 operator+(vector3 a)
	{
		vector3 result(x + a.x, y + a.y, z + a.z);
		return result;
	}

	__device__ vector3 Normalize()
	{
		vector3 result;
		float length = sqrt(x*x + y*y + z*z);
		result.x = x / length;
		result.y = y / length;
		result.z = z / length;
		return result;
	}
	__device__ float dotProduct(vector3 t)
	{
		float result = x*t.x + y*t.y + z*t.z;
		return result;
	}
};

__device__ bool isIntersect(vector3 center, float r, vector3 ray, vector3 src, vector3& Normal, vector3 & Point, float &dist)
{
	float a = 1;
	float b = 2 * (ray.x *(src.x - center.x) + ray.y *(src.y - center.y) + ray.z *(src.z - center.z));
	float c = pow(src.x - center.x, 2) + pow(src.y - center.y, 2) + pow(src.z - center.z, 2) - r*r;
	float disc = b*b - 4 * c;
	if (disc<0)
	{
		return false;
	}
	disc = sqrt(disc);
	float t = (0.5f)*(-b - disc);
	if (t > 0)
	{
		dist = sqrt(a) * t;
		vector3 hitd;
		hitd.x = ray.x*t;
		hitd.y = ray.y*t;
		hitd.z = ray.z*t;
		Point.x = src.x + hitd.x;
		Point.y = src.y + hitd.y;
		Point.z = src.z + hitd.z;
		Normal.x = Point.x - center.x;
		Normal.y = Point.y - center.y;
		Normal.z = Point.z - center.z;
		return true;
	}
	else
		return false;
}
__device__
int rgbToInt2(float r, float g, float b)
{
	if (r > 1.0f)
		r = 1.0f;
	if (g > 1.0f)
		g = 1.0f;
	if (b > 1.0f)
		b = 1.0f;
	return (int(r * 255) << 16) | (int(g * 255) << 8) | int(b * 255);
}

__device__
int DetermineColor(float * spheres, vector3 ray, vector3 Normal, vector3 hitPoint, int objId, int size)
{
	float ka = 0.2f;
	vector3 Light;
	Light.x = 0;
	Light.y = 0;
	Light.z = 500;
	vector3 SourceToLight = Light - hitPoint;
	SourceToLight = SourceToLight.Normalize();
	Normal = Normal.Normalize();
	bool willBeShaded = false;

	for (int id = 0; id < size; id++)
	{
		vector3 N, hP;
		vector3 center;
		center.x = spheres[id * 8];
		center.y = spheres[id * 8 + 1];
		center.z = spheres[id * 8 + 2];
		float dist;
		if (id != objId && isIntersect(center, spheres[id * 8 + 3], SourceToLight, hitPoint, N, hP, dist))
		{
			willBeShaded = true;
			break;
		}
	}

	vector3 ambient;
	ambient.x = spheres[objId * 8 + 4];
	ambient.y = spheres[objId * 8 + 5];
	ambient.z = spheres[objId * 8 + 6];
	vector3 baseColor;
	baseColor.x = ambient.x*ka;
	baseColor.y = ambient.y*ka;
	baseColor.z = ambient.z*ka;
	if (willBeShaded)
	{
		return rgbToInt2(baseColor.x, baseColor.y, baseColor.z);
	}
	else{
		float val = SourceToLight.dotProduct(Normal);
		float kd = 0 < val ? val : 0;
		vector3 h = SourceToLight - ray;
		h = h.Normalize();
		val = h.dotProduct(Normal);
		float ks = pow(0< val ? val : 0, 20.0f);
		baseColor = baseColor + vector3(ambient.x*kd, ambient.y*kd, ambient.z*kd);
		baseColor = baseColor + vector3(ambient.x*ks, ambient.y*ks, ambient.z*ks);
		return rgbToInt2(baseColor.x, baseColor.y, baseColor.z);
	}
}

__global__
void cudaProcess(float * spheres, unsigned int *g_odata, int imgw, int imgh, int size)
{
	int tx = threadIdx.x;
	int bw = blockDim.x;
	int gx = gridDim.x;
	int x = blockIdx.x;
	for (int i = x; i < imgh; i += gx)
	{
		vector3 src;
		src.x = -5000;
		src.y = -(imgw / 2) + tx;
		src.z = -(imgh / 2) + i;

		vector3 dir;
		dir.x = 1;
		dir.y = 0;
		dir.z = 0;
		float minDist = 1000000;
		vector3 Normal, hitPoint;
		int objectId;
		for (int id = 0; id < size; id++)
		{
			float dist;
			vector3 N, hP;
			vector3 center;
			center.x = spheres[id * 8];
			center.y = spheres[id * 8 + 1];
			center.z = spheres[id * 8 + 2];

			float r = spheres[id * 8 + 3];
			if (isIntersect(center, r, dir, src, N, hP, dist))
			{
				if (dist < minDist)
				{
					minDist = dist;
					Normal = N;
					hitPoint = hP;
					objectId = id;
				}
			}
		}

		if (minDist != 1000000)
			g_odata[i*bw + tx] = DetermineColor(spheres, dir, Normal, hitPoint, objectId, size);
		else
			g_odata[i*bw + tx] = (int(0.4f * 255) << 16) | (int(0.4f * 255) << 8) | int(0.4f * 255);
	}
}

#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort = true)
{
	if (code != cudaSuccess)
	{
		fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
		if (abort) exit(code);
	}
}
__global__
void cudaMoveObjects(float* spheres, int size)
{
	int id = threadIdx.x;
	if (id < size)
	{
		float dir = spheres[id * 8 + 7];
		if (spheres[id * 8 + 1] > 300 || spheres[id * 8 + 1] < -300)
		{
			dir *= -1;
			spheres[id * 8 + 7] = dir;
		}
		float velocity = 2.f * dir;
		if (id == 2)
		{
			spheres[id * 8 + 0] += velocity / 2;
			spheres[id * 8 + 2] += velocity / 2;
		}
		spheres[id * 8 + 1] += velocity;
	}
}

extern "C" void CudaUpdateObjects(float* SphereOnGpu,int elmSize)
{
	cudaMoveObjects << <1, 32 >> >(SphereOnGpu, elmSize);
}

extern "C" void CudaRayTrace(float* SphereOnGpu, unsigned int* out_data, int window_height2, int window_width2,int elmSize)
{
	cudaProcess << <256, window_width2 >> >(SphereOnGpu, out_data, window_width2, window_height2, elmSize);
	gpuErrchk(cudaPeekAtLastError());
	gpuErrchk(cudaDeviceSynchronize());
}


//extern "C" void CopyToGPU(SphereForGpu * SphereArr)
//{
//	cudaMemcpy(SphereOnGpu, SphereArr, elmSize * sizeof(SphereForGpu), cudaMemcpyHostToDevice);
//} 
//
//extern "C" void SetMemoryOnGPU(int size, SphereForGpu * SphereArr)
//{
//
//	elmSize = size;
//	cudaMalloc((void**)&SphereOnGpu, size * sizeof(SphereForGpu));
//	CopyToGPU(SphereArr);
//}
//
//
//
//extern "C" void CopyToCpu(SphereForGpu * SphereArr)
//{
//	cudaMemcpy(SphereArr, SphereOnGpu, elmSize * sizeof(SphereForGpu), cudaMemcpyDeviceToHost);
//}
//
//extern "C" void FreeMemoryOnGPU()
//{
//	free(SphereOnGpu);
//}