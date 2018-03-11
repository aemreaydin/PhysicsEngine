#ifndef _IRIGID_BODY_HG_
#define _IRIGID_BODY_HG_

#include "iShape.h"
#include <glm\game_math.h>

namespace nPhysics
{
	class iRigidBody
	{
	public:
		virtual ~iRigidBody() {}

		virtual void GetTransform(glm::mat4& transformOut) = 0;
		virtual void GetPosition(glm::vec3& positionOut) = 0;
		virtual void SetPosition(glm::vec3 position) = 0;
		virtual void GetRotation(glm::vec3& rotationOut) = 0;
		virtual void ApplyForce(glm::vec3& forceOut) = 0;
		virtual void GetVelocity(glm::vec3& velocityOut) = 0;
		virtual void SetVelocity(glm::vec3 velocity) = 0;

		virtual iShape* GetShape() = 0;
	};
}

#endif