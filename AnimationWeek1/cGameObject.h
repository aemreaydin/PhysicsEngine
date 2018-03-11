#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\game_math.h>
#include <string>

#include "cModel.h"
#include "extern.h"

enum eObjectType
{
	OBJECT_SPHERE,
	OBJECT_PLANE
};

class cGameObject
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

	eObjectType ObjectType;

	cGameObject(std::string modelName, std::string modelDir, eObjectType objectType);
	cGameObject(std::string modelName, std::string modelDir, glm::vec3 position, glm::vec3 scale, glm::vec3 orientationEuler, eObjectType objectType);
	cGameObject(std::string modelName, std::string modelDir, glm::vec3 position, glm::vec3 scale, glm::quat orientationQuat, eObjectType objectType);

	void Draw(cShader Shader);
};
#endif // !_GAME_OBJECT_
