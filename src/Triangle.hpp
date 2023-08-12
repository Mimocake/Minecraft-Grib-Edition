#pragma once
#include "math.hpp"

class Triangle
{
public:
	math::vec3 coords[3];
	math::vec2 t_coords[3];
	Triangle(math::vec3, math::vec3, math::vec3, math::vec2, math::vec2, math::vec2);
	Triangle() {}
	Triangle project();
	std::vector<Triangle> clip_fun(math::vec3, math::vec3);
};