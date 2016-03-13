#ifndef _MOVEABLESPHERE_H_
#define _MOVEABLESPHERE_H_
#include "Moveable.h"
#include "../game-objects/Sphere.h"

class MoveableSphere : public Moveable, public Sphere
{
public:
	MoveableSphere(Vec3<float> p, float r);

	void move(Vec3<float>& moveVector) override;
};


#endif