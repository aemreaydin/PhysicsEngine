#include "cBulletPhysicsWorld.h"
#include "cBulletRK4.h"
#include <algorithm>
#include <glm\ext\collision.h>

namespace nPhysics
{
	cBulletPhysicsWorld::cBulletPhysicsWorld()
	{
		collisionConfiguration = new btDefaultCollisionConfiguration();
		dispatcher = new btCollisionDispatcher(collisionConfiguration);
		overlappingPairCache = new btDbvtBroadphase();
		solver = new btSequentialImpulseConstraintSolver;
		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
		dynamicsWorld->setGravity(btVector3(0, -10.0f, 0));
	}
	cBulletPhysicsWorld::~cBulletPhysicsWorld()
	{
		delete dynamicsWorld;
		delete solver;
		delete overlappingPairCache;
		delete dispatcher;
		delete collisionConfiguration;
	}

	void cBulletPhysicsWorld::TimeStep(float deltaTime)
	{
		this->dynamicsWorld->stepSimulation(deltaTime, 2);
		//for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
		//{
		//	btCollisionObject* obj = this->dynamicsWorld->getCollisionObjectArray()[j];
		//	btRigidBody* body = btRigidBody::upcast(obj);
		//	btTransform trans;
		//	if (body && body->getMotionState())
		//	{
		//		body->getMotionState()->getWorldTransform(trans);
		//	}
		//	else
		//	{
		//		trans = obj->getWorldTransform();
		//	}
		//}
	}

	void cBulletPhysicsWorld::AddRigidBody(iRigidBody* rigidBody)
	{
		cBulletRigidBody* rb = dynamic_cast<cBulletRigidBody*>(rigidBody);
		if (!rb)
			return;

		std::vector<cBulletRigidBody*>::iterator itRigidBody;
		itRigidBody = std::find(mRigidBody.begin(), mRigidBody.end(), rb);
		if (itRigidBody == mRigidBody.end())
		{
			this->dynamicsWorld->addRigidBody(rb->mBody);
			mRigidBody.push_back(rb);
		}
	}

	void cBulletPhysicsWorld::RemoveRigidBody(iRigidBody* rigidBody)
	{
		cBulletRigidBody* rb = dynamic_cast<cBulletRigidBody*>(rigidBody);
		if (!rb)
			return;

		std::vector<cBulletRigidBody*>::iterator itRigidBody;
		itRigidBody = std::remove(mRigidBody.begin(), mRigidBody.end(), rb);
		if (itRigidBody != mRigidBody.end())
		{
			mRigidBody.resize(mRigidBody.size() - 1);
		}
	}

	bool cBulletPhysicsWorld::Collide(cBulletRigidBody* A, cBulletRigidBody* B)
	{
		eShapeType typeA = A->GetShape()->GetShapeType();
		eShapeType typeB = B->GetShape()->GetShapeType();

		switch (typeA)
		{
		case nPhysics::SHAPE_TYPE_SPHERE:
			float radiusA;
			A->mShape->GetSphereRadius(radiusA);
			switch (typeB)
			{
			case nPhysics::SHAPE_TYPE_PLANE:
			{
				glm::vec3 planeNormalB;
				float planeConstB;
				B->mShape->GetPlaneNormal(planeNormalB);
				B->mShape->GetPlaneConst(planeConstB);
				glm::vec3 closestPoint = glm::closest_point_on_plane(A->mPosition, planeNormalB, planeConstB);
				//printf("%f-%f-%f\n", closestPoint.x, closestPoint.y, closestPoint.z);
				float distanceAB = glm::distance(A->mPosition, closestPoint);
				//printf("%f\n", distanceAB);
				if (distanceAB <= radiusA)
				{
					glm::vec3 response = 2.0f * planeNormalB * (planeNormalB * A->mVelocity);
					A->mVelocity -= response * 0.99f;
				}
				break;
			}
			case nPhysics::SHAPE_TYPE_SPHERE:
			{
				float radiusB;
				float bCollide;
				B->mShape->GetSphereRadius(radiusB);
				glm::intersect_moving_sphere_sphere(A->mPosition, radiusA, A->mVelocity, B->mPosition, radiusB, B->mVelocity, bCollide);
				if (!bCollide)
				{
					glm::vec3 posNorm = A->mPosition - B->mPosition;
					posNorm = glm::normalize(posNorm);

					A->mVelocity -= 2.95f * B->mMass * posNorm * glm::dot(A->mVelocity, posNorm) / (A->mMass + B->mMass);
					B->mVelocity -= 2.95f * A->mMass * posNorm * glm::dot(B->mVelocity, posNorm) / (A->mMass + B->mMass);
					//B->mVelocity -= (0.95f * posNorm * glm::dot(B->mVelocity, posNorm) * A->mMass) / (A->mMass + B->mMass);
				}
				break;
			}
			default:
				break;
			}
		default:
			break;
		}
		return true;
	}
}