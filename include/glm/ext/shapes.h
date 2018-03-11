#pragma once
#include "../vec3.hpp"

namespace glm
{
	struct sphere
	{
		float r;
		sphere() : r(1.f) {}
		sphere(float _r) : r(_r) {}
	};

	struct plane
	{
		float d;
		vec3 n;
		plane() : n(0.f, 1.f, 0.f), d(0.f) { }
		plane(float nx, float ny, float nz, float _d) : n(nx, ny, nz), d(_d) { }
	};
}