#include "cPhysicsScene.h"
#include "cBall.h"
#include "cPlane.h"

#include <rapidjson\document.h>
#include <rapidjson\writer.h>
#include <rapidjson\stringbuffer.h>
#include <rapidjson\filereadstream.h>
#include <cstdio>

#include <iostream>
#include "Utilities.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\game_math.h>

bool cPhysicsScene::LoadModelsIntoScene(std::string fileName)
{
	FILE *fp;
	fopen_s(&fp, fileName.c_str(), "rb");
	char readBuffer[65536];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	rapidjson::Document doc;
	doc.ParseStream(is);
	const rapidjson::Value& sphere = doc["Ball"];
	const rapidjson::Value& planeFloor = doc["PlaneFloor"];
	const rapidjson::Value& planeLeft = doc["PlaneLeft"];
	const rapidjson::Value& planeRight = doc["PlaneRight"];
	const rapidjson::Value& planeFront = doc["PlaneFront"];
	const rapidjson::Value& planeBack = doc["PlaneBack"];

	this->numBalls = sphere["numObjects"].GetInt();
	this->numPlanes = 5;

	for (int i = 0; i != this->numBalls; i++)
	{
		glm::vec3 position = glm::vec3(getRandInRange<float>(sphere["positionMin"].GetFloat(), sphere["positionMax"].GetFloat()),
			getRandInRange<float>(sphere["positionyMin"].GetFloat(), sphere["positionyMax"].GetFloat()),
			getRandInRange<float>(sphere["positionMin"].GetFloat(), sphere["positionMax"].GetFloat()));
		glm::vec3 scale = glm::vec3(getRandInRange<float>(sphere["scaleMin"].GetFloat(), sphere["scaleMax"].GetFloat()));
		glm::vec3 orientation = glm::vec3(getRandInRange<float>(sphere["rotationMin"].GetFloat(), sphere["rotationMax"].GetFloat()),
			getRandInRange<float>(sphere["rotationMin"].GetFloat(), sphere["rotationMax"].GetFloat()),
			getRandInRange<float>(sphere["rotationMin"].GetFloat(), sphere["rotationMax"].GetFloat()));
		glm::vec3 velocity = glm::vec3(getRandInRange<float>(sphere["velocityMin"].GetFloat(), sphere["velocityMax"].GetFloat()));
		float mass = sphere["Mass"].GetFloat();
		cBall* newBall = new cBall(sphere["objectModel"].GetString(), position, scale, orientation, velocity, mass);

		this->Balls.push_back(newBall);
	}

	glm::vec3 position = glm::vec3(planeFloor["position"].GetFloat());
	glm::vec3 orientation = glm::vec3(planeFloor["rotation"].GetFloat());
	glm::vec3 scale = glm::vec3(planeFloor["scale"].GetFloat());
	glm::vec3 normal = glm::vec3(planeFloor["normalx"].GetFloat(), planeFloor["normaly"].GetFloat(), planeFloor["normalz"].GetFloat());
	float planeConst = planeFloor["planeConstant"].GetFloat();
	cPlane* pFloor = new cPlane(planeFloor["objectModel"].GetString(), position, scale, orientation, normal, planeConst);
	this->Planes.push_back(pFloor);

	position = glm::vec3(planeRight["position"].GetFloat());
	orientation = glm::vec3(planeRight["rotation"].GetFloat());
	scale = glm::vec3(planeRight["scale"].GetFloat());
	normal = glm::vec3(planeRight["normalx"].GetFloat(), planeRight["normaly"].GetFloat(), planeRight["normalz"].GetFloat());
	planeConst = planeRight["planeConstant"].GetFloat();
	cPlane* pRight = new cPlane(planeRight["objectModel"].GetString(), position, scale, orientation, normal, planeConst);
	this->Planes.push_back(pRight);

	position = glm::vec3(planeLeft["position"].GetFloat());
	orientation = glm::vec3(planeLeft["rotation"].GetFloat());
	scale = glm::vec3(planeLeft["scale"].GetFloat());
	normal = glm::vec3(planeLeft["normalx"].GetFloat(), planeLeft["normaly"].GetFloat(), planeLeft["normalz"].GetFloat());
	planeConst = planeLeft["planeConstant"].GetFloat();
	cPlane* pLeft = new cPlane(planeLeft["objectModel"].GetString(), position, scale, orientation, normal, planeConst);
	this->Planes.push_back(pLeft);

	position = glm::vec3(planeFront["position"].GetFloat());
	orientation = glm::vec3(planeFront["rotation"].GetFloat());
	scale = glm::vec3(planeFront["scale"].GetFloat());
	normal = glm::vec3(planeFront["normalx"].GetFloat(), planeFront["normaly"].GetFloat(), planeFront["normalz"].GetFloat());
	planeConst = planeFront["planeConstant"].GetFloat();
	cPlane* pFront = new cPlane(planeFront["objectModel"].GetString(), position, scale, orientation, normal, planeConst);
	this->Planes.push_back(pFront);

	position = glm::vec3(planeBack["position"].GetFloat());
	orientation = glm::vec3(planeBack["rotation"].GetFloat());
	scale = glm::vec3(planeBack["scale"].GetFloat());
	normal = glm::vec3(planeBack["normalx"].GetFloat(), planeBack["normaly"].GetFloat(), planeBack["normalz"].GetFloat());
	planeConst = planeBack["planeConstant"].GetFloat();
	cPlane* pBack = new cPlane(planeBack["objectModel"].GetString(), position, scale, orientation, normal, planeConst);
	this->Planes.push_back(pBack);

	return true;
}

void cPhysicsScene::RenderScene(cShader shader)
{
	for (int i = 0; i != this->Balls.size(); i++)
	{
		if (i == currentBall)
		{
			Balls[i]->RigidBody->ApplyForce(outsideForce);
			Balls[i]->BulletRigidBody->ApplyForce(outsideForce);
			Balls[i]->isCurrent = true;
		}
		else
		{
			glm::vec3 zeroForce = glm::vec3(0.0f);
			Balls[i]->RigidBody->ApplyForce(zeroForce);
			Balls[i]->isCurrent = false;
		}
		glm::mat4 model = glm::mat4(1.0f);
		glm::vec3 rotation, position, velocity;
		Balls[i]->BulletRigidBody->GetRotation(rotation);
		if (isBullet)
		{
			Balls[i]->BulletRigidBody->GetPosition(position);
			Balls[i]->BulletRigidBody->GetVelocity(velocity);
			Balls[i]->RigidBody->SetPosition(position);
			Balls[i]->RigidBody->SetVelocity(velocity);
		}
		else
		{
			Balls[i]->RigidBody->GetPosition(position);
			Balls[i]->RigidBody->GetVelocity(velocity);
			Balls[i]->BulletRigidBody->SetPosition(position);
			Balls[i]->BulletRigidBody->SetVelocity(velocity);
		}


		model = glm::translate(model, position);
		model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, Balls[i]->Scale);
		shader.SetMatrix4("model", model, true);
		shader.SetFloat("isCurrent", Balls[i]->isCurrent, true);
		Balls[i]->Draw(shader);
	}
	for (int i = 0; i != this->Planes.size(); i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, Planes[i]->Position);
		model = glm::rotate(model, glm::radians(Planes[i]->OrientationEuler.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(Planes[i]->OrientationEuler.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(Planes[i]->OrientationEuler.z), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, Planes[i]->Scale);
		shader.SetMatrix4("model", model, true);
		Planes[i]->Draw(shader);
	}
}