#ifndef _CPHYSICS_WORLD_HG_
#define _CPHYSICS_WORLD_HG_

#include <Interfaces\iPhysicsWorld.h>
#include <vector>
#include "cRigidBody.h"

namespace nPhysics
{
	class cPhysicsWorld : public iPhysicsWorld
	{
	public:
		virtual ~cPhysicsWorld();

		virtual void TimeStep(float deltaTime);

		virtual void AddRigidBody(iRigidBody* rigidBody);
		virtual void RemoveRigidBody(iRigidBody* rigidBody);

		bool Collide(cRigidBody* A, cRigidBody *B);

	private:
		std::vector<cRigidBody*> mRigidBody;
	};
}

#endif
