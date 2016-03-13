#ifndef _MOVEABLE_H_
#define _MOVEABLE_H_
#include "../../../utils/Vec3.h"
#include <functional>

class Moveable
{
public:
	Moveable();

	void update();
	virtual void rotate(Vec3<float>& moveVector);
	virtual void move() = 0;
	virtual void move(Vec3<float>& moveVector) = 0;


	Vec3<float> getSpeed();
	void setSpeed(Vec3<float>);

protected:

	std::function<void(void)> updateFunction;

	Vec3<float> speed;
	Vec3<float> rotationalSpeed;

	Angle<float> angle;
};

#endif
