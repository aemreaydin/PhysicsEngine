#include "cPhysicsWorld.h"
#include "cRK4.h"
#include <algorithm>
#include <glm\ext\collision.h>

namespace nPhysics
{
	cPhysicsWorld::~cPhysicsWorld()
	{
	}

	void cPhysicsWorld::TimeStep(float deltaTime)
	{
		glm::vec3 GRAVITY = glm::vec3(0.0f, -5.0f, 0.0f);
		for (int i = 0; i != mRigidBody.size(); i++)
		{
			nPhysics::cRK4 integrator;
			cRigidBody* rb = mRigidBody[i];
			if (rb->mShape->GetShapeType() == eShapeType::SHAPE_TYPE_SPHERE)
			{
				sState state;
				state.x = rb->mPosition;
				state.v = rb->mVelocity;
				state.a = rb->mAcceleration + deltaTime * GRAVITY + rb->mForce * deltaTime;
				integrator.Integrate(state, deltaTime);
				rb->mPosition = state.x;
				rb->mVelocity = state.v;
				rb->mAcceleration = state.a;
			}
			//mRigidBody[i]->mForce = glm::vec3(0.0f);
		}
		size_t numBodies = mRigidBody.size();
		for (size_t iA = 0; iA < numBodies - 1; iA++)
		{
			for (size_t iB = iA + 1; iB < numBodies; iB++)
			{
				Collide(mRigidBody[iA], mRigidBody[iB]);
			}
		}
	}

	void cPhysicsWorld::AddRigidBody(iRigidBody* rigidBody)
	{
		cRigidBody* rb = dynamic_cast<cRigidBody*>(rigidBody);
		if (!rb)
			return;

		std::vector<cRigidBody*>::iterator itRigidBody;
		itRigidBody = std::find(mRigidBody.begin(), mRigidBody.end(), rb);
		if (itRigidBody == mRigidBody.end())
		{
			mRigidBody.push_back(rb);
		}
	}

	void cPhysicsWorld::RemoveRigidBody(iRigidBody* rigidBody)
	{
		cRigidBody* rb = dynamic_cast<cRigidBody*>(rigidBody);
		if (!rb)
			return;

		std::vector<cRigidBody*>::iterator itRigidBody;
		itRigidBody = std::remove(mRigidBody.begin(), mRigidBody.end(), rb);
		if (itRigidBody != mRigidBody.end())
		{
			mRigidBody.resize(mRigidBody.size() - 1);
		}
	}

	bool cPhysicsWorld::Collide(cRigidBody* A, cRigidBody* B)
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