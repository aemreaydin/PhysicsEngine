#ifndef _CONVERT_HG_
#define _CONVERT_HG_

#include <glm\game_math.h>
#include "../Bullet/btBulletDynamicsCommon.h"

namespace nPhysics
{
	namespace nConvert
	{
		inline btVector3 ToBullet(const glm::vec3& v)
		{
			return btVector3(v.x, v.y, v.z);
		}
		inline glm::vec3 ToGlm(const btVector3& v)
		{
			return glm::vec3(v.x(), v.y(), v.z());
		}
		inline void ToGlm(const btTransform& transform, glm::mat4& out)
		{
			transform.getOpenGLMatrix(&out[0][0]);
		}
		inline btTransform ToBullet(const glm::mat4& mat)
		{
			btTransform transform;
			transform.setFromOpenGLMatrix(&mat[0][0]);
			return transform;
		}
		inline glm::vec3 ToGlm(const btQuaternion quat)
		{
			glm::quat quaternion = glm::quat(quat.w(), quat.x(), quat.y(), quat.z());
			return glm::eulerAngles(quaternion);
		}
	}
}

#endif