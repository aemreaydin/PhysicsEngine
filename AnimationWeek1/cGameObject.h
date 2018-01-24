#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_

#include <glm\vec3.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>

class cGameObject
{
public:
	glm::vec3 Position, Scale;
	glm::quat Orientation;

};
#endif // !_GAME_OBJECT_
