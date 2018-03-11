#include "cBulletPlaneShape.h"

namespace nPhysics
{
	cBulletPlaneShape::cBulletPlaneShape(const glm::vec3& normal, float planeConst) : iShape(SHAPE_TYPE_PLANE)
	{
		this->mNormal = normal;
		this->mPlaneConst = planeConst;
	}
	cBulletPlaneShape::cBulletPlaneShape() : iShape(SHAPE_TYPE_PLANE) {}
	cBulletPlaneShape::cBulletPlaneShape(const cBulletPlaneShape& other) : iShape(SHAPE_TYPE_PLANE) {}
	cBulletPlaneShape& cBulletPlaneShape::operator=(const cBulletPlaneShape& other)
	{
		return *this;
	}
	cBulletPlaneShape::~cBulletPlaneShape() {}

	bool cBulletPlaneShape::GetPlaneNormal(glm::vec3& normalOut)
	{
		normalOut = this->mNormal;
		return true;
	}
	bool cBulletPlaneShape::GetPlaneConst(float& planeConstOut)
	{
		planeConstOut = this->mPlaneConst;
		return true;
	}
}