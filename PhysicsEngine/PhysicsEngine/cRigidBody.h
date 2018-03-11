#ifndef _CRIGID_BODY_HG_
#define _CRIGID_BODY_HG_

#include <Interfaces\iRigidBody.h>
#include <Interfaces\sRigidBodyDesc.h>

namespace nPhysics
{
	class cPhysicsWorld;
	class cRigidBody : public iRigidBody
	{
	public:
		cRigidBody(const sRigidBodyDesc& desc, iShape* shape);
		virtual ~cRigidBody();

		virtual void GetTransform(glm::mat4& transformOut);
		virtual void GetPosition(glm::vec3& positionOut);
		virtual void SetPosition(glm::vec3 position);
		virtual void GetRotation(glm::vec3& rotationOut);
		virtual void ApplyForce(glm::vec3& forceOut);
		virtual void GetVelocity(glm::vec3& velocityOut);
		virtual void SetVelocity(glm::vec3 velocity);

		virtual iShape* GetShape();

	private:
		friend class cPhysicsWorld;
		iShape* mShape;
		glm::vec3 mPosition;
		glm::quat mRotation;
		glm::vec3 mVelocity;
		glm::vec3 mForce;
		glm::vec3 mAcceleration;
		float mMass;
	};
}

#endif
