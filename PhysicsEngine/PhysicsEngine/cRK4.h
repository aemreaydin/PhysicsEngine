#ifndef _RK4_HG_
#define _RK4_HG_

#include <glm\game_math.h>

namespace nPhysics
{
	struct sState
	{
		glm::vec3 x;
		glm::vec3 v;
		glm::vec3 a;
	};
	struct sDerivative
	{
		glm::vec3 dx;
		glm::vec3 dv;
	};

	class cRK4
	{
	public:
		sDerivative Evaluate(const sState& initial, float dt, const sDerivative& d);
		void Integrate(sState& state, float dt);
	};
}
#endif