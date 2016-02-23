#ifndef _VEC3_H_
#define _VEC3_H_

class Vec3
{
public:
	Vec3();
	Vec3(float xPos, float yPos, float zPos);
	void Normalize();
	float getX();
	float getY();
	float getZ();
	Vec3 operator-(Vec3 rhs);
	Vec3 operator+(Vec3 rhs);
	void rotate(Vec3 angle);
	float dotProduct(Vec3 vec);

private:
	float x;
	float y;
	float z;
};

typedef Vec3 Angle;

#endif