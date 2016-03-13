#ifndef _MOVEABLETRIANGLE_H_
#define _MOVEABLETRIANGLE_H_
#include "Moveable.h"
#include "../game-objects/Triangle.h"

class MoveableTriangle : public Moveable, public Triangle
{
public:
	MoveableTriangle(Vec3<float> top, Vec3<float> right, Vec3<float> left);
 	void rotate(Angle& moveVector) override;

	void move(Vec3<float>& moveVector) override;
};

#endif
