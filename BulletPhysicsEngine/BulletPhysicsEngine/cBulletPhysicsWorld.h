#ifndef _CBULLET_PHYSICS_WORLD_HG_
#define _CBULLET_PHYSICS_WORLD_HG_

#include <Interfaces\iPhysicsWorld.h>
#include <vector>
#include "cBulletRigidBody.h"

namespace nPhysics
{
	class cBulletPhysicsWorld : public iPhysicsWorld
	{
	public:
		cBulletPhysicsWorld();
		virtual ~cBulletPhysicsWorld();

		virtual void TimeStep(float deltaTime);

		virtual void AddRigidBody(iRigidBody* rigidBody);
		virtual void RemoveRigidBody(iRigidBody* rigidBody);

		bool Collide(cBulletRigidBody* A, cBulletRigidBody *B);

	private:
		std::vector<cBulletRigidBody*> mRigidBody;

		btDefaultCollisionConfiguration* collisionConfiguration;// = new btDefaultCollisionConfiguration();

		///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
		btCollisionDispatcher* dispatcher;// = new btCollisionDispatcher(collisionConfiguration);

		///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
		btBroadphaseInterface* overlappingPairCache;// = new btDbvtBroadphase();

		///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
		btSequentialImpulseConstraintSolver* solver;// = new btSequentialImpulseConstraintSolver;

		btDiscreteDynamicsWorld* dynamicsWorld;// = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	};
}

#endif
