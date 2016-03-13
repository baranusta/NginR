#ifndef _MOVEABLE_H_
#define _MOVEABLE_H_
#include "../../../utils/Utils.h"
#include <functional>

class Moveable
{
public:

	Moveable();
	void update();
	virtual void rotate(Angle& moveVector);

	virtual void move(Vec3<float>& moveVector) = 0;

	void setUpdateFunction(std::function<void(void)> update_function);

	void setSpeed(Vec3<float>);
	Vec3<float> getSpeed() const;

protected:

	std::function<void(void)> updateFunction;

	Vec3<float> speed;
	Angle rotationalSpeed;

	Angle angle;
};

#endif
