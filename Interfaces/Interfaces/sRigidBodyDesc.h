#ifndef _SRIGID_BODY_DESC_HG_
#define _SRIGID_BODY_DESC_HG_

#include <glm\game_math.h>

namespace nPhysics
{
	struct sRigidBodyDesc
	{
		sRigidBodyDesc()
		{
			Position = glm::vec3(0.0f);
			Velocity = glm::vec3(0.0f);
			Rotation = glm::vec3(0.0f);
			Mass = 1.0f;
		}
		glm::vec3 Position;
		glm::vec3 Velocity;
		glm::vec3 Rotation;
		float Mass;
	};
}
#endif
