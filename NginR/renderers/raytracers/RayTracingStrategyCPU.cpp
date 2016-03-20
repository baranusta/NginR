#include "RayTracingStrategyCPU.h"

#include <algorithm>

void RayTracingStrategyCPU::IterateInnerLoop(const World & w, Vec3<int> ViewPort, int i, int k, unsigned int* dst)
{
	for (int j = -ViewPort.getZ() / 2, t = 0; j < ViewPort.getZ() / 2; j++, t++)
	{
		Vec3<float> src(ViewPort.getX(), i, j);
		Vec3<float> ray = Vec3<float>(1, 0, 0);
		/*Vec3 ray = Vec3(ViewPort.getX(), i, j) - eyePos;
		ray.rotate(ViewPortAngle);
		ray.Normalize();*/
		float minDist = 1000000;
		Vec3<float> Normal, hitPoint;
		int objectId = -1;
		std::vector<GameObject*> Objects = w.GetObjects();
		for (int id = 0, size = Objects.size(); id < size; id++)
		{
			float dist;
			Vec3<float> N, hP;
			if (Objects[id]->isRayIntersects(ray, src, hP, dist))
			{
				
				if (dist < minDist)
				{
					minDist = dist;
					Vec3<float> normal = Objects[id]->getNormal(hP);
					Normal = normal;
					hitPoint = hP;
					objectId = id; 
				}
			}
		}


		if (minDist != 1000000)
		{
			float wow = DetermineColor(w.getLight(), ray, Normal, hitPoint, objectId, &Objects);
			dst[t * (int)ViewPort.getY() + k] = wow;
		}
		else
		{
			float ws = w.getAmbient().rgbToInt();
			dst[t * (int)ViewPort.getY() + k] = ws;

		}
		//World->SendRay(collidedObj,size,ray,eyePos,Objects);
		//Color pixelC = DetermineColor(collidedObj,size);
	}
}

int RayTracingStrategyCPU::DetermineColor(Light& light, Vec3<float>& ray, Vec3<float>& Normal, Vec3<float>& hitPoint, int objId, std::vector<GameObject*>* Objects) const
{
	Vec3<float> lightPos = light.getPos();
	Vec3<float> SourceToLight = lightPos - hitPoint;
	SourceToLight.Normalize();
	bool willBeShaded = false;

	if ((ray.dotProduct(Normal)<0 && Normal.dotProduct(SourceToLight)>=0) || (ray.dotProduct(Normal)>=0 && Normal.dotProduct(SourceToLight)<=0))
	{
		for (int id = 0; id < Objects->size(); id++)
		{
			Vec3<float> N, hP;
			float dist;
			if (id != objId && (*Objects)[id]->isRayIntersects(SourceToLight, hitPoint, hP, dist))
			{
				willBeShaded = true;
				break;
			}
		}
	}
	else
	{
		willBeShaded = true;
	}

	GameObject* obj = (*Objects)[objId];
	Color objAmb = obj->getAmbient();
	Color baseColor = objAmb * light.getAmbient();
	if (willBeShaded)
	{
		return baseColor.rgbToInt();
	}
	else{
		float kd = diffuseConst;
		Vec3<float> h = SourceToLight - ray;
		h.Normalize();
		//Diffuse Illumination
		float lDotNormal = SourceToLight.dotProduct(Normal);
		lDotNormal = lDotNormal <=  0 ? SourceToLight.dotProduct(Normal * -1) : lDotNormal;
		baseColor = baseColor + (obj->getDiffuse() * lDotNormal * kd * light.getDiffuse());
		//Specular Lightning
		float phong = pow(std::max(0.f, h.dotProduct(Normal)), phongPower);
		baseColor = baseColor + (obj->getSpecular() * phong * light.getSpec());
		return baseColor.rgbToInt();
	}
}