#ifndef _BALL_OBJECT_HG
#define _BALL_OBJECT_HG

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\game_math.h>
#include <string>

#include "cModel.h"
#include "extern.h"

class cBall
{
public:
	glm::vec3 Position, Scale, OrientationEuler;
	glm::quat OrientationQuat;
	glm::vec3 Velocity, Acceleration;
	float Mass;
	bool isCurrent;

	cModel* Model;

	nPhysics::iShape* Shape;
	nPhysics::iRigidBody* RigidBody;
	nPhysics::sRigidBodyDesc RBDesc;

	nPhysics::iShape* BulletShape;
	nPhysics::iRigidBody* BulletRigidBody;

	void SetVelocity(glm::vec3);
	void SetMass(float);

	//();
	cBall(std::string modelDir);
	cBall(std::string modelDir, glm::vec3 position, glm::vec3 scale, glm::vec3 orientationEuler);
	cBall(std::string modelDir, glm::vec3 position, glm::vec3 scale, glm::quat orientationQuat);
	cBall(std::string modelDir, glm::vec3 position, glm::vec3 scale, glm::vec3 orientation, glm::vec3 velocity, float mass);

	void Draw(cShader Shader);
};
#endif // !_GAME_OBJECT_
