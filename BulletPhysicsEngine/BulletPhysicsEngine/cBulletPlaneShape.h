#ifndef _BULLET_PLANE_SHAPE_HG_
#define _BULLET_PLANE_SHAPE_HG_

#include <glm\game_math.h>
#include <Interfaces\iShape.h>

namespace nPhysics
{
	class cBulletPlaneShape : public iShape
	{
	public:
		cBulletPlaneShape(const glm::vec3& normal, float planeConst);
		virtual ~cBulletPlaneShape();

		virtual bool GetPlaneNormal(glm::vec3& normalOut);
		virtual bool GetPlaneConst(float& planeConstOut);

	private:
		cBulletPlaneShape();
		cBulletPlaneShape(const cBulletPlaneShape& other);
		cBulletPlaneShape& operator=(const cBulletPlaneShape& other);

		glm::vec3 mNormal;
		float mPlaneConst;
	};
}

#endif