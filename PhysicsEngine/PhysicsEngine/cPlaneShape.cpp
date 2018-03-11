#include "cPlaneShape.h"

namespace nPhysics
{
	cPlaneShape::cPlaneShape(const glm::vec3& normal, float planeConst) : iShape(SHAPE_TYPE_PLANE)
	{
		this->mNormal = normal;
		this->mPlaneConst = planeConst;
	}
	cPlaneShape::cPlaneShape() : iShape(SHAPE_TYPE_PLANE) {}
	cPlaneShape::cPlaneShape(const cPlaneShape& other) : iShape(SHAPE_TYPE_PLANE) {}
	cPlaneShape& cPlaneShape::operator=(const cPlaneShape& other)
	{
		return *this;
	}
	cPlaneShape::~cPlaneShape() {}

	bool cPlaneShape::GetPlaneNormal(glm::vec3& normalOut)
	{
		normalOut = this->mNormal;
		return true;
	}
	bool cPlaneShape::GetPlaneConst(float& planeConstOut)
	{
		planeConstOut = this->mPlaneConst;
		return true;
	}
}