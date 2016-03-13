#include "MoveableTriangle.h"


MoveableTriangle::MoveableTriangle(Vec3<float> top, Vec3<float> right, Vec3<float> left) :Triangle(top,right,left)
{
}


void MoveableTriangle::rotate(Angle& moveVector)
{
	Moveable::rotate(moveVector);

	Vec3<float> total = corners[0];
	total += corners[1];
	total += corners[2];

	Vec3<float> center(total.getX() / 3, total.getY() / 3, total.getZ() / 3);
	for (int i = 0; i < 3; i++)
	{
		Vec3<float> centerToPoint = corners[i] - center;
		centerToPoint.rotate(moveVector);
		corners[i] = centerToPoint + center;
	}
}

void MoveableTriangle::move(Vec3<float>& moveVector)
{
	corners[0] += moveVector;
	corners[1] += moveVector;
	corners[2] += moveVector;
}
