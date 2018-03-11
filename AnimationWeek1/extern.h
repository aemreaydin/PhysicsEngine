#ifndef _EXTERN_HG_
#define _EXTERN_HG_

#include <Interfaces\iPhysicsFactory.h>

extern nPhysics::iPhysicsFactory* gPhysicsFactory;
extern nPhysics::iPhysicsWorld* gPhysicsWorld;
extern nPhysics::iPhysicsFactory* gBulletPhysicsFactory;
extern nPhysics::iPhysicsWorld* gBulletPhysicsWorld;

bool InitPhysics();

extern int currentBall;
extern bool isBullet;
extern glm::vec3 outsideForce;

#endif