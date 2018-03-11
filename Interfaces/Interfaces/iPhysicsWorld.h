#ifndef _IPHYSICS_WORLD_HG_
#define _IPHYSICS_WORLD_HG_

#include "iRigidBody.h"

namespace nPhysics
{
	class iPhysicsWorld
	{
	public:
		virtual ~iPhysicsWorld() {}

		virtual void TimeStep(float deltaTime) = 0;

		virtual void AddRigidBody(iRigidBody* rigidBody) = 0;
		virtual void RemoveRigidBody(iRigidBody* rigidBody) = 0;
	};
}

#endif