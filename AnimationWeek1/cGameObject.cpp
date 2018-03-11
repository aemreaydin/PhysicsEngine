#include "cGameObject.h"
#include "cShader.h"

cGameObject::cGameObject(std::string modelName, std::string modelDir, eObjectType objectType)
{
	this->Model = new cModel(modelDir.c_str());

	this->Position = glm::vec3(0.0f);
	this->Scale = glm::vec3(1.0f);
	this->OrientationQuat = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
	this->OrientationEuler = glm::vec3(0.0f);
	this->Velocity = glm::vec3(0.0f);
	this->Mass = 1.0f;

	this->ObjectType = objectType;

	RBDesc.Position = this->Position;
	RBDesc.Rotation = this->OrientationEuler;
	RBDesc.Velocity = this->Velocity;
	RBDesc.Mass = this->Mass;

	switch (this->ObjectType)
	{
	case eObjectType::OBJECT_SPHERE:
		this->Shape = gPhysicsFactory->CreateSphere(1.0f);
		this->RigidBody = gPhysicsFactory->CreateRigidBody(this->RBDesc, this->Shape);
		gPhysicsWorld->AddRigidBody(this->RigidBody);
		break;
	default:
		break;
	}
}
cGameObject::cGameObject(std::string modelName, std::string modelDir, glm::vec3 position, glm::vec3 scale, glm::vec3 orientationEuler, eObjectType objectType)
{
	this->Model = new cModel(modelDir.c_str());

	this->Position = position;
	this->Scale = scale;
	this->OrientationQuat = glm::quat(orientationEuler);
	this->OrientationEuler = orientationEuler;
	this->Velocity = glm::vec3(0.0f);
	this->Mass = 1.0f;

	this->ObjectType = objectType;

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
cGameObject::cGameObject(std::string modelName, std::string modelDir, glm::vec3 position, glm::vec3 scale, glm::quat orientationQuat, eObjectType objectType)
{
	this->Model = new cModel(modelDir.c_str());

	this->Position = position;
	this->Scale = scale;
	this->OrientationQuat = orientationQuat;
	this->OrientationEuler = glm::eulerAngles(orientationQuat);
	this->Velocity = glm::vec3(0.0f);
	this->Mass = 1.0f;

	this->ObjectType = objectType;

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

void cGameObject::Draw(cShader Shader)
{
	this->Model->Draw(Shader);
}