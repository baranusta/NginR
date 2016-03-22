#include "Moveable.h"

Moveable::Moveable()
{
	angle = Angle(0, 0, 0, Angle::DEGREE);
	speed = Vec3<float>(0, 0, 0);
	rotationalSpeed = angle;
	updateFunction = [](void) -> void{};
}

Moveable::~Moveable()
{
}

void Moveable::update()
{
	rotate(rotationalSpeed); 
	if (updateFunction != nullptr)
		updateFunction();
	move(speed);
}

void Moveable::rotate(Angle& moveVector)
{
	angle.rotate(moveVector);
}

void Moveable::setUpdateFunction(std::function<void(void)> update_function)
{
	updateFunction = update_function;
}

void Moveable::setSpeed(Vec3<float> speed)
{
	this->speed = speed;
}

Vec3<float> Moveable::getSpeed() const
{
	return speed;
}
