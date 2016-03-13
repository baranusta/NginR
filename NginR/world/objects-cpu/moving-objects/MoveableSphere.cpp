#include "MoveableSphere.h"

MoveableSphere::MoveableSphere(Vec3<float> p, float r) :Sphere(p,r)
{

}

void MoveableSphere::move(Vec3<float>& moveVector)
{
	center += moveVector;
}
