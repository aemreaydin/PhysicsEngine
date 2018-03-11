#ifndef _PLANE_SHAPE_HG_
#define _PLANE_SHAPE_HG_

#include <glm\game_math.h>
#include <Interfaces\iShape.h>

namespace nPhysics
{
	class cPlaneShape : public iShape
	{
	public:
		cPlaneShape(const glm::vec3& normal, float planeConst);
		virtual ~cPlaneShape();

		virtual bool GetPlaneNormal(glm::vec3& normalOut);
		virtual bool GetPlaneConst(float& planeConstOut);

	private:
		cPlaneShape();
		cPlaneShape(const cPlaneShape& other);
		cPlaneShape& operator=(const cPlaneShape& other);

		glm::vec3 mNormal;
		float mPlaneConst;
	};
}

#endif