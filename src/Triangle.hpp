#pragma once
#include "math.hpp"

class Triangle
{
public:
	math::vec3 coords[3];
	math::vec3 viewed_coords[3];
	math::vec3 proj_coords[3];
	math::vec3 normal;
	Triangle(math::vec3, math::vec3, math::vec3);
	Triangle() {}
	void project(math::mat4x4);
};