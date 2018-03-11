#include "cSphereShape.h"

namespace nPhysics
{
	cSphereShape::cSphereShape(float radius) : iShape(SHAPE_TYPE_SPHERE)
	{
		this->mRadius = radius;
	}
	cSphereShape::cSphereShape() : iShape(SHAPE_TYPE_SPHERE) {}
	cSphereShape::cSphereShape(const cSphereShape& other) : iShape(SHAPE_TYPE_SPHERE) {}
	cSphereShape& cSphereShape::operator=(const cSphereShape& other)
	{
		return *this;
	}
	cSphereShape::~cSphereShape() {}

	bool cSphereShape::GetSphereRadius(float& radiusOut)
	{
		radiusOut = this->mRadius;
		return true;
	}
}