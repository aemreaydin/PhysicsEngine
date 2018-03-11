#include "cPlane.h"
#include "cShader.h"

cPlane::cPlane(std::string modelDir)
{
	this->Model = new cModel(modelDir.c_str());

	this->Position = glm::vec3(0.0f);
	this->Scale = glm::vec3(1.0f);
	this->OrientationQuat = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
	this->OrientationEuler = glm::vec3(0.0f);
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
cPlane::cPlane(std::string modelDir, glm::vec3 position, glm::vec3 scale, glm::vec3 orientationEuler)
{
	this->Model = new cModel(modelDir.c_str());

	this->Position = position;
	this->Scale = scale;
	this->OrientationQuat = glm::quat(orientationEuler);
	this->OrientationEuler = orientationEuler;
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
cPlane::cPlane(std::string modelDir, glm::vec3 position, glm::vec3 scale, glm::quat orientationQuat)
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

cPlane::cPlane(std::string modelDir, glm::vec3 position, glm::vec3 scale, glm::vec3 orientationEuler, glm::vec3 normal, float planeConst)
{
	this->Model = new cModel(modelDir.c_str());

	this->Position = position;
	this->Scale = scale;
	this->OrientationQuat = glm::quat(orientationEuler);
	this->OrientationEuler = orientationEuler;

	RBDesc.Position = this->Position;
	RBDesc.Rotation = this->OrientationEuler;
	RBDesc.Velocity = this->Velocity;
	RBDesc.Mass = this->Mass;

	this->Shape = gPhysicsFactory->CreatePlane(normal, planeConst);
	this->RigidBody = gPhysicsFactory->CreateRigidBody(this->RBDesc, this->Shape);
	gPhysicsWorld->AddRigidBody(this->RigidBody);

	this->BulletShape = gBulletPhysicsFactory->CreatePlane(normal, planeConst);
	this->BulletRigidBody = gBulletPhysicsFactory->CreateRigidBody(this->RBDesc, this->Shape);
	gBulletPhysicsWorld->AddRigidBody(this->BulletRigidBody);

	return;
}

void cPlane::Draw(cShader Shader)
{
	this->Model->Draw(Shader);
}