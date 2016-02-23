#include "RayTracingStrategyCPU.h"

#include <algorithm>

void RayTracingStrategyCPU::IterateInnerLoop(World w, Vec3 ViewPort, int i, int k, unsigned int* dst)
{
	for (int j = -ViewPort.getZ() / 2, t = 0; j < ViewPort.getZ() / 2; j++, t++)
	{
		Vec3 src(ViewPort.getX(), i, j);
		Vec3 ray = Vec3(1, 0, 0);
		/*Vec3 ray = Vec3(ViewPort.getX(), i, j) - eyePos;
		ray.rotate(ViewPortAngle);
		ray.Normalize();*/
		float minDist = 1000000;
		Vec3 Normal, hitPoint;
		int objectId;
		std::vector<GeometricObject*> Objects = w.GetObjects();
		for (int id = 0,size = Objects.size(); id < size; id++)
		{
			float dist;
			Vec3 N, hP;
			if (Objects[id]->isRayIntersects(ray, src, N, hP, dist))
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
			dst[t * (int)ViewPort.getY() + k] = DetermineColor(w.GetLight(), ray, Normal, hitPoint, objectId, &Objects);
		else
		{
			float ws = w.GetAmbient().rgbToInt();
			dst[t * (int)ViewPort.getY() + k] = ws;

		}
		//World->SendRay(collidedObj,size,ray,eyePos,Objects);
		//Color pixelC = DetermineColor(collidedObj,size);
	}

}

int RayTracingStrategyCPU::DetermineColor(Light light, Vec3 ray, Vec3 Normal, Vec3 hitPoint, int objId, std::vector<GeometricObject*>* Objects)
{
	Vec3 lightPos = light.getPos();
	Vec3 SourceToLight = lightPos - hitPoint;
	SourceToLight.Normalize();
	bool willBeShaded = false;

	for (int id = 0; id < Objects->size(); id++)
	{
		Vec3 N, hP;
		float dist;
		if (id != objId && (*Objects)[id]->isRayIntersects(SourceToLight, hitPoint, N, hP, dist))
		{
			willBeShaded = true;
			break;
		}
	}

	GeometricObject* obj = (*Objects)[objId];
	Color objAmb = obj->getAmbient();
	Color baseColor = objAmb * light.getAmbient();
	if (willBeShaded)
	{
		return baseColor.rgbToInt();
	}
	else{
		float kd = diffuseConst;
		Vec3 h = SourceToLight - ray;
		Normal.Normalize();
		h.Normalize();
		//Diffuse Illumination
		float lDotNormal = std::max(0.f, SourceToLight.dotProduct(Normal));
		baseColor = baseColor + (obj->getDiffuse() * lDotNormal * kd * light.getDiffuse());
		//Specular Lightning
		float phong = pow(std::max(0.f, h.dotProduct(Normal)), phongPower);
		baseColor = baseColor + (obj->getSpecular() * phong * light.getSpec());
		return baseColor.rgbToInt();
	}
}