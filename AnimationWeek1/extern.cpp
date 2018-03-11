#include "extern.h"

#include <PhysicsEngine\cPhysicsFactory.h>
#include <BulletPhysicsEngine\cBulletPhysicsFactory.h>

nPhysics::iPhysicsFactory* gPhysicsFactory = 0;
nPhysics::iPhysicsWorld* gPhysicsWorld = 0;
nPhysics::iPhysicsFactory* gBulletPhysicsFactory = 0;
nPhysics::iPhysicsWorld* gBulletPhysicsWorld = 0;

bool isBullet = true;
int currentBall = 0;
glm::vec3 outsideForce = glm::vec3(0.0f);

bool InitPhysics()
{
	gPhysicsFactory = new nPhysics::cPhysicsFactory();
	gPhysicsWorld = new nPhysics::cPhysicsWorld();
	gBulletPhysicsFactory = new nPhysics::cBulletPhysicsFactory();
	gBulletPhysicsWorld = new nPhysics::cBulletPhysicsWorld();
	return true;
}