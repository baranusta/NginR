#ifndef _ANGLE_H_
#define _ANGLE_H_

#include "Vec3.h"

#define PI 3.141592

class Angle : public Vec3<float>
{
public:
	enum AngleType { RADIAN, DEGREE };
	Angle()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Angle(float xAngle, float yAngle, float zAngle, AngleType type)
	{
		_setAngles(xAngle, yAngle, zAngle, type);
	}
private:
	void _setAngles(float& xAngle, float& yAngle, float& zAngle, AngleType type)
	{
		if (type == RADIAN)
		{
			xAngle = fmod(xAngle, 2);
			yAngle = fmod(yAngle, 2);
			zAngle = fmod(zAngle, 2);
		}
		else
		{
			xAngle = fmod(xAngle, 180);
			yAngle = fmod(yAngle, 180);
			zAngle = fmod(zAngle, 180);
			float val = 3.141592 / 180;
			xAngle *= val;
			yAngle *= val;
			zAngle *= val;
		}

		x = xAngle;
		y = yAngle;
		z = zAngle;
	}
};

#endif