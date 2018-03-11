#ifndef _CBULLET_RIGID_BODY_HG_
#define _CBULLET_RIGID_BODY_HG_

#include <Interfaces\iRigidBody.h>
#include <Interfaces\sRigidBodyDesc.h>
#include "../Bullet/btBulletDynamicsCommon.h"

namespace nPhysics
{
	class cBulletPhysicsWorld;
	class cBulletRigidBody : public iRigidBody
	{
	public:
		cBulletRigidBody(const sRigidBodyDesc& desc, iShape* shape);
		virtual ~cBulletRigidBody();

		virtual void GetTransform(glm::mat4& transformOut);
		virtual void GetPosition(glm::vec3& positionOut);
		virtual void SetPosition(glm::vec3 position);
		virtual void GetRotation(glm::vec3& rotationOut);
		virtual void ApplyForce(glm::vec3& forceOut);
		virtual void GetVelocity(glm::vec3& velocityOut);
		virtual void SetVelocity(glm::vec3 velocity);

		virtual iShape* GetShape();
	private:
		friend class cBulletPhysicsWorld;
		iShape* mShape;
		glm::vec3 mPosition;
		glm::quat mRotation;
		glm::vec3 mVelocity;
		glm::vec3 mForce;
		glm::vec3 mAcceleration;
		float mMass;

		btCollisionShape* mCollisionShape;
		btRigidBody* mBody;
		btDefaultMotionState* mMotionState;
	};
}

#endif
