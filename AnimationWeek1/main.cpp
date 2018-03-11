#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "extern.h"

#include "cGLCalls.h"
#include "Camera.h"
#include "cShader.h"
#include "cModel.h"
#include "cGameObject.h"
#include "cLightManager.h"
#include "cPhysicsScene.h"

#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <gtest\gtest.h>

#include <glm\game_math.h>

cGLCalls* GLCalls;
cShader * Shader, *LampShader;
cGameObject * Nanosuit, *SanFran;
cLightManager * LightManager;
cPhysicsScene * Scene;

std::vector< cGameObject * > GOVec;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

const unsigned int width = 1600;
const unsigned int height = 900;

Camera camera(glm::vec3(0.0f, 50.0f, 50.0f));
float lastX = width / 2.0f;
float lastY = height / 2.0f;
bool firstMouse = true;

int currentLight = 0;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

TEST(TC_INIT, InitializeGLFW)
{
	ASSERT_TRUE(GLCalls->Initialize() == GL_TRUE);
}
TEST(TC_CREATE_WINDOW, CreateGLWindow)
{
	ASSERT_TRUE(GLCalls->CreateGLWindow() == GL_TRUE);
}

int main(int argc, char **argv)
{
	GLCalls = new cGLCalls(width, height, "AssimpImport");

	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	glfwSetFramebufferSizeCallback(GLCalls->GetWindow(), framebuffer_size_callback);
	glfwSetCursorPosCallback(GLCalls->GetWindow(), mouse_callback);
	glfwSetScrollCallback(GLCalls->GetWindow(), scroll_callback);
	glfwSetKeyCallback(GLCalls->GetWindow(), keyCallback);

	glEnable(GL_DEPTH_TEST);

	Shader = new cShader("assets/shaders/simpleVertex.glsl", "assets/shaders/simpleFragment.glsl");
	LampShader = new cShader("assets/shaders/lampShader.glsl", "assets/shaders/lampFragment.glsl");

	LightManager = new cLightManager();
	LightManager->CreateLights();
	LightManager->LoadLampsIntoShader(*LampShader);

	Scene = new cPhysicsScene;

	Nanosuit = new cGameObject("Nanosuit", "assets/models/Ball/NBA BASKETBALL.obj", glm::vec3(7.0f, 0.0f, 0.0f), glm::vec3(0.2), glm::vec3(0.0f), eObjectType::OBJECT_SPHERE);
	GOVec.push_back(Nanosuit);

	if (!InitPhysics())
		std::cout << "You wot m8" << std::endl;

	gPhysicsWorld = gPhysicsFactory->CreateWorld();

	Scene->LoadModelsIntoScene("assets/scene.json");

	double lastFrame = glfwGetTime();

	while (!glfwWindowShouldClose(GLCalls->GetWindow()))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(GLCalls->GetWindow());

		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Shader->Use();
		LampShader->Use();

		glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (float)width / (float)height, 0.1f, 1000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		Shader->SetMatrix4("projection", projection, true);
		Shader->SetMatrix4("view", view, true);
		Shader->SetVector3f("eyePos", camera.GetPosition());
		LampShader->SetMatrix4("projection", projection, true);
		LampShader->SetMatrix4("view", view, true);
		LightManager->LoadLightsIntoShader(*Shader);

		//outsideForce = glm::vec3(0.0f);
		//gPhysicsWorld->TimeStep(deltaTime);
		if (isBullet)
			gBulletPhysicsWorld->TimeStep(deltaTime);
		else
			gPhysicsWorld->TimeStep(deltaTime);

		std::cout << "Using Bullet? " << isBullet << std::endl;
		//for (int i = 0; i < GOVec.size(); i++)
		//{
		//	glm::mat4 model = glm::mat4(1.0f);
		//	model = glm::translate(model, GOVec[i]->Position);
		//	model = glm::rotate(model, glm::radians(GOVec[i]->OrientationEuler.x), glm::vec3(1.0f, 0.0f, 0.0f));
		//	model = glm::rotate(model, glm::radians(GOVec[i]->OrientationEuler.y), glm::vec3(0.0f, 1.0f, 0.0f));
		//	model = glm::rotate(model, glm::radians(GOVec[i]->OrientationEuler.z), glm::vec3(0.0f, 0.0f, 1.0f));
		//	model = glm::scale(model, GOVec[i]->Scale);
		//	Shader->SetMatrix4("model", model, true);
		//	GOVec[i]->Draw(*Shader);
		//}
		for (int i = 0; i < LightManager->NumLights; i++)
		{
			glm::mat4 lightModel = glm::mat4(1.0f);
			lightModel = glm::translate(lightModel, LightManager->Lights[i].position);
			lightModel = glm::scale(lightModel, glm::vec3(0.2f));
			Shader->SetMatrix4("lightModel", lightModel, true);
		}
		LightManager->DrawLightsIntoScene(*LampShader);

		Scene->RenderScene(*Shader);

		glfwPollEvents();
		glfwSwapBuffers(GLCalls->GetWindow());
	}

	glfwTerminate();
	return 0;
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	//if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	//{
	//	glfwSetWindowShouldClose(window, GL_TRUE);
	//}

	//if (GLFW_KEY_SPACE == key && GLFW_PRESS == action)
	//{
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//}

	//if (key >= 0 && key < 1024)
	//{
	//	if (action == GLFW_PRESS)
	//	{
	//		keys[key] = true;
	//	}
	//	else if (action == GLFW_RELEASE)
	//	{
	//		keys[key] = false;
	//	}
	//}
	if (GLFW_KEY_TAB == key && GLFW_PRESS == action)
	{
		currentBall++;
		outsideForce = glm::vec3(0.0f);
		if (currentBall == Scene->numBalls)
			currentBall = 0;
	}
	if (GLFW_KEY_SPACE == key && GLFW_PRESS == action)
	{
		isBullet = !isBullet;
	}
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		outsideForce += glm::vec3(1.0f, 0.0f, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		outsideForce -= glm::vec3(1.0f, 0.0f, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		outsideForce -= glm::vec3(0.0f, 0.0f, 1.0f);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		outsideForce += glm::vec3(0.0f, 0.0f, 1.0f);

	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
	{
		LightManager->Lights[currentLight].position.x += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
	{
		LightManager->Lights[currentLight].position.x -= 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	{
		LightManager->Lights[currentLight].position.z += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		LightManager->Lights[currentLight].position.z -= 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
	{
		LightManager->Lights[currentLight].position.y += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{
		LightManager->Lights[currentLight].position.y -= 0.01f;
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}