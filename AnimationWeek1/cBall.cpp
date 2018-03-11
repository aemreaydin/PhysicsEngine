#include "cBall.h"
#include "cShader.h"

//cBall::cBall()
//{
//	this->Model = new cModel("");
//
//	this->Position = glm::vec3(0.0f);
//	this->Scale = glm::vec3(1.0f);
//	this->OrientationQuat = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
//	this->OrientationEuler = glm::vec3(0.0f);
//	this->Velocity = glm::vec3(0.0f);
//	this->Mass = 1.0f;
//
//	this->ObjectType = eObjectType::OBJECT_SPHERE;
//}

cBall::cBall(std::string modelDir)
{
	this->Model = new cModel(modelDir.c_str());

	this->Position = glm::vec3(0.0f);
	this->Scale = glm::vec3(1.0f);
	this->OrientationQuat = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
	this->OrientationEuler = glm::vec3(0.0f);
	this->Velocity = glm::vec3(0.0f);
	this->Mass = 1.0f;
	RBDesc.Position = this->Position;
	RBDesc.Rotation = this->OrientationEuler;
	RBDesc.Velocity = this->Velocity;
	RBDesc.Mass = this->Mass;

	this->Shape = gPhysicsFactory->CreateSphere(1.0f);
	this->RigidBody = gPhysicsFactory->CreateRigidBody(this->RBDesc, this->Shape);
	gPhysicsWorld->AddRigidBody(this->RigidBody);
	return;
}
cBall::cBall(std::string modelDir, glm::vec3 position, glm::vec3 scale, glm::vec3 orientationEuler)
{
	this->Model = new cModel(modelDir.c_str());

	this->Position = position;
	this->Scale = scale;
	this->OrientationQuat = glm::quat(orientationEuler);
	this->OrientationEuler = orientationEuler;
	this->Velocity = glm::vec3(0.0f);
	this->Mass = 1.0f;

	RBDesc.Position = this->Position;
	RBDesc.Rotation = this->OrientationEuler;
	RBDesc.Velocity = this->Velocity;
	RBDesc.Mass = this->Mass;

	this->Shape = gPhysicsFactory->CreateSphere(1.0f);
	this->RigidBody = gPhysicsFactory->CreateRigidBody(this->RBDesc, this->Shape);
	gPhysicsWorld->AddRigidBody(this->RigidBody);
	return;
}
cBall::cBall(std::string modelDir, glm::vec3 position, glm::vec3 scale, glm::quat orientationQuat)
{
	this->Model = new cModel(modelDir.c_str());

	this->Position = position;
	this->Scale = scale;
	this->OrientationQuat = orientationQuat;
	this->OrientationEuler = glm::eulerAngles(orientationQuat);
	this->Velocity = glm::vec3(0.0f);
	this->Mass = 1.0f;

	//RBDesc.Position = this->Position;
	//RBDesc.Rotation = this->OrientationEuler;
	//RBDesc.Velocity = this->Velocity;
	//RBDesc.Mass = this->Mass;

	//switch (this->ObjectType)
	//{
	//case eObjectType::OBJECT_SPHERE:
	//	this->Shape = gPhysicsFactory->CreateSphere(1.0f);
	//	this->RigidBody = gPhysicsFactory->CreateRigidBody(this->RBDesc, this->Shape);
	//	break;
	//default:
	//	break;
	//}
}
cBall::cBall(std::string modelDir, glm::vec3 position, glm::vec3 scale, glm::vec3 orientation, glm::vec3 velocity, float mass)
{
	this->Model = new cModel(modelDir.c_str());

	this->Position = position;
	this->Scale = scale;
	this->OrientationQuat = glm::quat(orientation);
	this->OrientationEuler = orientation;
	this->Velocity = velocity;
	this->Acceleration = glm::vec3(0.0f);
	this->Mass = scale.x;

	this->isCurrent = false;

	RBDesc.Position = this->Position;
	RBDesc.Rotation = this->OrientationEuler;
	RBDesc.Velocity = this->Velocity;
	RBDesc.Mass = this->Mass;

	this->Shape = gPhysicsFactory->CreateSphere(scale.x / 2.2f);
	this->RigidBody = gPhysicsFactory->CreateRigidBody(this->RBDesc, this->Shape);
	gPhysicsWorld->AddRigidBody(this->RigidBody);

	this->BulletShape = gBulletPhysicsFactory->CreateSphere(scale.x / 2.2f);
	this->BulletRigidBody = gBulletPhysicsFactory->CreateRigidBody(this->RBDesc, this->BulletShape);
	gBulletPhysicsWorld->AddRigidBody(this->BulletRigidBody);

	return;
}

void cBall::Draw(cShader Shader)
{
	this->Model->Draw(Shader);
}
void cBall::SetMass(float mass)
{
	this->Mass = mass;
	this->RBDesc.Mass = mass;
}
void cBall::SetVelocity(glm::vec3 vel)
{
	this->Velocity = vel;
	this->RBDesc.Velocity = vel;
}