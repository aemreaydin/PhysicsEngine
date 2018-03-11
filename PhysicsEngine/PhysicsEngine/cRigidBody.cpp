#include "cRigidBody.h"

namespace nPhysics
{
	cRigidBody::cRigidBody(const sRigidBodyDesc& desc, iShape* shape)
	{
		this->mShape = shape;
		this->mPosition = desc.Position;
		this->mRotation = desc.Rotation;
		this->mVelocity = desc.Velocity;
		this->mMass = desc.Mass;
	}
	cRigidBody::~cRigidBody() {}

	void cRigidBody::GetTransform(glm::mat4& transformOut)
	{
		transformOut = glm::mat4_cast(this->mRotation);
		transformOut[3][0] = this->mPosition.x;
		transformOut[3][1] = this->mPosition.y;
		transformOut[3][2] = this->mPosition.z;
		transformOut[3][3] = 1.0f;
	}
	void cRigidBody::GetPosition(glm::vec3& positionOut)
	{
		positionOut = this->mPosition;
	}
	void cRigidBody::SetPosition(glm::vec3 position)
	{
		this->mPosition = position;
	}
	void cRigidBody::GetRotation(glm::vec3& rotationOut)
	{
		rotationOut = glm::eulerAngles(this->mRotation);
	}

	void cRigidBody::ApplyForce(glm::vec3& forceOut)
	{
		this->mForce = forceOut;
	}

	iShape* cRigidBody::GetShape()
	{
		return this->mShape;
	}
	void cRigidBody::GetVelocity(glm::vec3& velocityOut)
	{
		velocityOut = this->mVelocity;
	}

	void cRigidBody::SetVelocity(glm::vec3 velocity)
	{
		this->mVelocity = velocity;
	}
}