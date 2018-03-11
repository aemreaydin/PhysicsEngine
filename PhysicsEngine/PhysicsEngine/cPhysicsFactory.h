#ifndef _CPHYSICS_FACTORY_HG_
#define _CPHYSICS_FACTORY_HG_

#include <Interfaces\iPhysicsFactory.h>
#include "cPhysicsWorld.h"

namespace nPhysics
{
	class cPhysicsFactory : public iPhysicsFactory
	{
	public:
		virtual ~cPhysicsFactory();

		virtual iPhysicsWorld* CreateWorld();

		virtual iRigidBody* CreateRigidBody(const sRigidBodyDesc& desc, iShape* shape);

		virtual iShape* CreateSphere(float radius);
		virtual iShape* CreatePlane(const glm::vec3& normal, float planeConst);
	};
}

#endif