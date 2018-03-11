#ifndef _CBULLET_PHYSICS_FACTORY_HG_
#define _CBULLET_PHYSICS_FACTORY_HG_

#include <Interfaces\iPhysicsFactory.h>
#include "cBulletPhysicsWorld.h"

namespace nPhysics
{
	class cBulletPhysicsFactory : public iPhysicsFactory
	{
	public:
		virtual ~cBulletPhysicsFactory();

		virtual iPhysicsWorld* CreateWorld();

		virtual iRigidBody* CreateRigidBody(const sRigidBodyDesc& desc, iShape* shape);

		virtual iShape* CreateSphere(float radius);
		virtual iShape* CreatePlane(const glm::vec3& normal, float planeConst);
	};
}

#endif