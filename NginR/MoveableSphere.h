#ifndef _MOVEABLESPHERE_H_
#define _MOVEABLESPHERE_H_
#include "utils/Vec3.h"
#include "world/objects-cpu/moving-objects/Moveable.h"
#include "world/objects-cpu/game-objects/Sphere.h"

class MoveableSphere : public Moveable, public Sphere
{
public:
	MoveableSphere(Vec3<float> top, Vec3<float> right, Vec3<float> left);
	void rotate(Vec3<float>& moveVector) override;

	void move() override;
	void move(Vec3<float>& moveVector) override;
};


#endif