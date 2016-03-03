//
//#include <fstream>
//#include <sstream>
//#include "..\Objects\WorldObjects\Sphere.h"
//#include "Vec3.h"
//#include "..\World.h"
//
//void SetWorld(std::ifstream & file)
//{
//
//	std::string xPos, yPos, zPos;
//	file >> xPos;
//	file >> yPos;
//	file >> zPos;
//	Vec3 max(atoi(xPos.c_str()), atoi(yPos.c_str()), atoi(zPos.c_str()));
//	file >> xPos;
//	file >> yPos;
//	file >> zPos;
//	Vec3 min(atoi(xPos.c_str()), atoi(yPos.c_str()), atoi(zPos.c_str()));
//	//World = new RectWorld(NULL, max, min);
//}
//
//void AddObjects(std::ifstream & file, World* world)
//{
//	std::string line;
//	while (std::getline(file, line))
//	{
//		bool willbeAdd = true;
//		GeometricObject* p = NULL;
//		switch (line[0])
//		{
//		case 's':
//		{
//			Sphere * t = new Sphere(line);
//			willbeAdd = t->shouldExist();
//			p = t;
//			break;
//		}
//		default:
//			break;
//		}
//		if (willbeAdd)
//		{
//			world->AddObject(p);
//		}
//		else
//			delete p;
//	}
//}
//
//bool CreateWorld(std::string fileName,World* world)
//{
//	std::ifstream file(fileName);
//	if (file.is_open())
//	{
//		std::string line;
//		SetWorld(file);
//		file >> line;
//		int supportedObjectNum = atoi(line.c_str());
//		for (int i = 0; i < supportedObjectNum + 1; i++)
//		{
//			std::getline(file, line);
//		}
//		AddObjects(file,world);
//		return true;
//	}
//	return false;
//}