#ifndef _BULLET_SPHERE_SHAPE_HG_
#define _BULLET_SPHERE_SHAPE_HG_

#include <glm\game_math.h>
#include <Interfaces\iShape.h>
#include "../Bullet/btBulletDynamicsCommon.h"

namespace nPhysics
{
	class cBulletSphereShape : public iShape
	{
	public:
		cBulletSphereShape(float radius);
		virtual ~cBulletSphereShape();

		virtual bool GetSphereRadius(float& radiusOut);

	private:
		cBulletSphereShape();
		cBulletSphereShape(const cBulletSphereShape& other);
		cBulletSphereShape& operator=(const cBulletSphereShape& other);

		float mRadius;
		btCollisionShape* mShape;
	};
}

#endif