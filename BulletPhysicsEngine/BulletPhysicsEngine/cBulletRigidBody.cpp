#include "cBulletRigidBody.h"
#include "nConvert.h"

namespace nPhysics
{
	cBulletRigidBody::cBulletRigidBody(const sRigidBodyDesc& desc, iShape* shape)
	{
		this->mShape = shape;
		this->mPosition = desc.Position;
		this->mRotation = desc.Rotation;
		this->mVelocity = desc.Velocity;
		this->mMass = desc.Mass;

		if (this->mShape->GetShapeType() == eShapeType::SHAPE_TYPE_SPHERE)
		{
			float radius;
			this->mShape->GetSphereRadius(radius);
			mCollisionShape = new btSphereShape(radius);
		}
		else
		{
			float planeConst;
			glm::vec3 planeNormal;
			this->mShape->GetPlaneConst(planeConst);
			this->mShape->GetPlaneNormal(planeNormal);
			mCollisionShape = new btStaticPlaneShape(nConvert::ToBullet(planeNormal), planeConst);
		}

		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(nConvert::ToBullet(this->mPosition));

		btScalar mass(this->mMass);

		bool isDynamic = (mass != 0.0f);

		btVector3 localIntertia(0, 0, 0);
		if (isDynamic)
			this->mCollisionShape->calculateLocalInertia(this->mMass, localIntertia);

			// TODO : SHAPE STUFF

		this->mMotionState = new btDefaultMotionState(transform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(this->mMass, this->mMotionState, this->mCollisionShape, localIntertia);

		mBody = new btRigidBody(rbInfo);
		this->mCollisionShape->setUserPointer(this);
		//this->mBody->setFriction(25.0f);
		this->mBody->setRollingFriction(0.01f);
		this->mBody->setRestitution(1.f);

		if (this->mShape->GetShapeType() == SHAPE_TYPE_SPHERE)
		{
			this->mBody->setLinearVelocity(nConvert::ToBullet(desc.Velocity));
			//this->mBody.
		}
		//this->mBody.setOri
		//this->mBody->setCollisionFlags(this->mBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
		//this->mBody->setActivationState(DISABLE_DEACTIVATION);
	}
	cBulletRigidBody::~cBulletRigidBody() {}

	void cBulletRigidBody::GetTransform(glm::mat4& transformOut)
	{
		btTransform transform;
		this->mMotionState->getWorldTransform(transform);
		nConvert::ToGlm(transform, transformOut);
	}
	void cBulletRigidBody::GetPosition(glm::vec3& positionOut)
	{
		positionOut = nConvert::ToGlm(this->mBody->getCenterOfMassPosition());
	}
	void cBulletRigidBody::SetPosition(glm::vec3 position)
	{
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(nConvert::ToBullet(position));
		this->mBody->setWorldTransform(transform);
		this->mMotionState->setWorldTransform(transform);
		//this->mMotionState->
		//this->mBody->setWorldTransform()
	}
	void cBulletRigidBody::GetRotation(glm::vec3& rotationOut)
	{
		rotationOut = nConvert::ToGlm(this->mBody->getOrientation());
	}

	void cBulletRigidBody::ApplyForce(glm::vec3& forceOut)
	{
		btVector3 btForce = nConvert::ToBullet(forceOut);
		this->mBody->activate(true);
		this->mBody->applyCentralForce(btForce);
		this->mForce = nConvert::ToGlm(btForce);
	}

	iShape* cBulletRigidBody::GetShape()
	{
		return this->mShape;
	}
	void cBulletRigidBody::GetVelocity(glm::vec3& velocityOut)
	{
		btVector3 vec = this->mBody->getLinearVelocity();
		velocityOut = nConvert::ToGlm(vec);
	}
	void cBulletRigidBody::SetVelocity(glm::vec3 velocity)
	{
		this->mBody->setLinearVelocity(nConvert::ToBullet(velocity));
	}
}