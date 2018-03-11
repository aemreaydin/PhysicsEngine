#ifndef _PHYSICS_SCENE_HG_
#define _PHYSICS_SCENE_HG_

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\game_math.h>
#include <string>
#include <vector>

#include "cShader.h"
#include "extern.h"

class cBall;
class cPlane;

class cPhysicsScene
{
public:
	bool LoadModelsIntoScene(std::string fileName);

	void RenderScene(cShader shader);

	std::vector<cBall*> Balls;
	std::vector<cPlane*> Planes;
	int numBalls;
private:
	int numPlanes;
};

#endif