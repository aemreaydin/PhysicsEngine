#ifndef _ISHAPE_HG_
#define _ISHAPE_HG_

#include "eShapeType.h"
#define GLM_EXPERIMENTAL_ENABLE
#include <glm\game_math.h>

namespace nPhysics
{
	class iShape
	{
	public:
		virtual ~iShape() {}

		virtual bool GetSphereRadius(float& radiusOut) { return false; }
		virtual bool GetPlaneNormal(glm::vec3& normalOut) { return false; }
		virtual bool GetPlaneConst(float& planeConstOut) { return false; }

		eShapeType GetShapeType() { return this->mShapeType; }

	protected:
		iShape(eShapeType shapeType) : mShapeType(shapeType) {}
		iShape() {}
		iShape(const iShape& other) {}
		iShape& operator=(const iShape& other) { return *this; }
	private:
		eShapeType mShapeType;
	};
}

#endif
