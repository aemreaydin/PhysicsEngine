#ifndef _SPHERE_SHAPE_HG_
#define _SPHERE_SHAPE_HG_

#include <glm\game_math.h>
#include <Interfaces\iShape.h>

namespace nPhysics
{
	class cSphereShape : public iShape
	{
	public:
		cSphereShape(float radius);
		virtual ~cSphereShape();

		virtual bool GetSphereRadius(float& radiusOut);

	private:
		cSphereShape();
		cSphereShape(const cSphereShape& other);
		cSphereShape& operator=(const cSphereShape& other);

		float mRadius;
	};
}

#endif