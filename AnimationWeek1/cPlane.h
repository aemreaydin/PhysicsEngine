#ifndef _PLANE_OBJECT_HG_
#define _PLANE_OBJECT_HG_

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\game_math.h>
#include <string>

#include "cModel.h"
#include "extern.h"

class cPlane
{
public:
	glm::vec3 Position, Scale, OrientationEuler;
	glm::quat OrientationQuat;
	glm::vec3 Velocity;
	float Mass;

	cModel* Model;

	nPhysics::iShape* Shape;
	nPhysics::iRigidBody* RigidBody;
	nPhysics::sRigidBodyDesc RBDesc;

	nPhysics::iShape* BulletShape;
	nPhysics::iRigidBody* BulletRigidBody;

	cPlane(std::string modelDir);
	cPlane(std::string modelDir, glm::vec3 position, glm::vec3 scale, glm::vec3 orientationEuler);
	cPlane(std::string modelDir, glm::vec3 position, glm::vec3 scale, glm::vec3 orientationEuler, glm::vec3 normal, float planeConst);
	cPlane(std::string modelDir, glm::vec3 position, glm::vec3 scale, glm::quat orientationQuat);

	void Draw(cShader Shader);
};
#endif // !_GAME_OBJECT_
