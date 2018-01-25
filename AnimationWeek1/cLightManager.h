#ifndef _LIGHT_MANAGER_
#define _LIGHT_MANAGER_

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm\vec3.hpp>
#include <glm\vec4.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\glm.hpp>

#include <vector>

class cShader;


enum eLightType
{
	DIRECTIONAL_LIGHT,
	POINT_LIGHT,
	SPOT_LIGHT,	
	UNKNOWN
};

struct sLight
{
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	glm::vec3 position;
	eLightType lightType;

	sLight()
	{
		this->ambient = glm::vec4(1.0f);
		this->diffuse = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		this->specular = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		this->position = glm::vec3(0.0f);
		this->lightType = eLightType::UNKNOWN;
	}
};
struct sLightVAO
{
	GLuint lightVAO;
	GLuint lightVBO;

	sLightVAO()
	{
		this->lightVAO = 0;
		this->lightVBO = 0;
	}
};


class cLightManager
{
public:
	cLightManager();

	void CreateLights();
	void LoadLampsIntoShader(cShader Shader);
	void LoadLightsIntoShader(cShader Shader);
	void DrawLightsIntoScene(cShader Shader);

	int NumLights;
	std::vector<sLight> Lights;
	std::vector<sLightVAO> LightVAOs;
};
#endif // !_LIGHT_MANAGER_
