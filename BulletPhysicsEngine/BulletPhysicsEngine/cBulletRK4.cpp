#include "cBulletRK4.h"

namespace nPhysics
{
	sDerivative cBulletRK4::Evaluate(const sState& initial, float dt, const sDerivative& d)
	{
		sState state;
		state.x = initial.x + d.dx*dt;
		state.v = initial.v + d.dv*dt;

		sDerivative output;
		output.dx = state.v;
		output.dv = initial.a;
		return output;
	}
	void cBulletRK4::Integrate(sState& state, float dt)
	{
		sDerivative a, b, c, d;

		a = Evaluate(state, 0.0f, sDerivative());
		b = Evaluate(state, dt * 0.5f, a);
		c = Evaluate(state, dt * 0.5f, b);
		d = Evaluate(state, dt, c);

		glm::vec3 dxdt = 1.0f / 6.0f * (a.dx + 2.0f * (b.dx + c.dx) + d.dx);
		glm::vec3 dvdt = 1.0f / 6.0f * (a.dv + 2.0f * (b.dv + c.dv) + d.dv);

		state.x = state.x + dxdt * dt;
		state.v = state.v + dvdt * dt;
	}
}