#include "cLightManager.h"

#include <string>
#include <sstream>
#include <fstream>

#include "cShader.h"

cLightManager::cLightManager()
{

}

void cLightManager::CreateLights()
{
	std::ifstream lightFile("assets/lighting/Lights.txt");
	std::string temp;
	

	lightFile >> this->NumLights;
	for (int i = 0; i < this->NumLights; i++)
	{
		sLight tempLight;
		lightFile >> temp;
		lightFile >> temp;
		if (temp == "DIRECTIONAL")
			tempLight.lightType = eLightType::DIRECTIONAL_LIGHT;
		else if (temp == "SPOT")
			tempLight.lightType = eLightType::SPOT_LIGHT;
		else if (temp == "POINT")
			tempLight.lightType = eLightType::POINT_LIGHT;
		else
			tempLight.lightType = eLightType::UNKNOWN;

		lightFile >> temp;
		lightFile >> tempLight.ambient.x;
		lightFile >> tempLight.ambient.y;
		lightFile >> tempLight.ambient.z;
		lightFile >> tempLight.ambient.w;

		lightFile >> temp;
		lightFile >> tempLight.diffuse.x;
		lightFile >> tempLight.diffuse.y;
		lightFile >> tempLight.diffuse.z;
		lightFile >> tempLight.diffuse.w;

		lightFile >> temp;
		lightFile >> tempLight.specular.x;
		lightFile >> tempLight.specular.y;
		lightFile >> tempLight.specular.z;
		lightFile >> tempLight.specular.w;

		lightFile >> temp;
		lightFile >> tempLight.attenuation.x;
		lightFile >> tempLight.attenuation.y;
		lightFile >> tempLight.attenuation.z;

		lightFile >> temp;
		lightFile >> tempLight.position.x;
		lightFile >> tempLight.position.y;
		lightFile >> tempLight.position.z;

		this->Lights.push_back(tempLight);
	}

}

void cLightManager::LoadLampsIntoShader(cShader Shader)
{
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};

	for (int i = 0; i < this->NumLights; i++)
	{
		sLightVAO tempVAO;

		GLuint lightVAO, lightVBO;
		glGenVertexArrays(1, &lightVAO);
		glGenBuffers(1, &lightVBO);

		glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray(lightVAO);
		
		GLuint posLoc = glGetAttribLocation(Shader.ID, "lightPosition");
		glEnableVertexAttribArray(posLoc);
		glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glBindVertexArray(0);

		tempVAO.lightVAO = lightVAO;
		tempVAO.lightVBO = lightVBO;
		this->LightVAOs.push_back(tempVAO);
	}
}

void cLightManager::DrawLightsIntoScene(cShader Shader)
{
	for (int i = 0; i < this->NumLights; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, this->Lights[i].position);
		model = glm::scale(model, glm::vec3(0.2f));
		Shader.SetMatrix4("lightModel", model, true);

		glBindVertexArray(this->LightVAOs[i].lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void cLightManager::LoadLightsIntoShader(cShader Shader)
{
	for (int i = 0; i < this->Lights.size(); i++)
	{
		Shader.SetVector4f("AmbientColor", this->Lights[i].ambient, true);
		Shader.SetVector4f("DiffuseColor", this->Lights[i].diffuse, true);
		Shader.SetVector4f("SpecularColor", this->Lights[i].specular, true);
		Shader.SetVector3f("Attenuation", this->Lights[i].attenuation, true);
		if (this->Lights[i].lightType == eLightType::DIRECTIONAL_LIGHT)
			Shader.SetInteger("LightType", 0);
		else if (this->Lights[i].lightType == eLightType::POINT_LIGHT)
			Shader.SetInteger("LightType", 1);
		else if (this->Lights[i].lightType == eLightType::SPOT_LIGHT)
			Shader.SetInteger("LightType", 2);
	}
}