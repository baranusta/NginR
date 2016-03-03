#ifndef _GAMEOBJECTFACTORY_H_
#define _GAMEOBJECTFACTORY_H_

#include "GeometricObject.h"
#include "Sphere.h"

class GameObjectFactory
{
public:
	enum objectTypes{sphere};
	GeometricObject* getGameObjectFromLine(std::string line);
	
};

inline GeometricObject* GameObjectFactory::getGameObjectFromLine(std::string line)
{
	bool willbeAdd = true;
	GeometricObject* p = NULL;
	switch (line[0] - '0')
	{
		case sphere:
		{
			Sphere * t = new Sphere(line);
			if (!t->shouldExist())
			{
				delete t;
				t = nullptr;
			}
			return  t;
		}
		default:
			break;
	}

}
#endif
