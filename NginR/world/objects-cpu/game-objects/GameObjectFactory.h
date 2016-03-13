#ifndef _GAMEOBJECTFACTORY_H_
#define _GAMEOBJECTFACTORY_H_

#include "GameObject.h"
#include "Sphere.h"

class GameObjectFactory
{
public:
	enum objectTypes{sphere};
	GameObject* getGameObjectFromLine(std::string line);
	
};

inline GameObject* GameObjectFactory::getGameObjectFromLine(std::string line)
{
	bool willbeAdd = true;
	GameObject* p = NULL;
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
