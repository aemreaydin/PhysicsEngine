#include "cBulletSphereShape.h"

namespace nPhysics
{
	cBulletSphereShape::cBulletSphereShape(float radius) : iShape(SHAPE_TYPE_SPHERE)
	{
		//this->mShape = new btSphereShape(radius);
		this->mRadius = radius;
	}
	cBulletSphereShape::cBulletSphereShape() : iShape(SHAPE_TYPE_SPHERE) {}
	cBulletSphereShape::cBulletSphereShape(const cBulletSphereShape& other) : iShape(SHAPE_TYPE_SPHERE) {}
	cBulletSphereShape& cBulletSphereShape::operator=(const cBulletSphereShape& other)
	{
		return *this;
	}
	cBulletSphereShape::~cBulletSphereShape() {}

	bool cBulletSphereShape::GetSphereRadius(float& radiusOut)
	{
		radiusOut = this->mRadius;
		return true;
	}
}