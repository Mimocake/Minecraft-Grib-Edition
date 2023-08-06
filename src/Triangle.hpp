#pragma once
#include "math.hpp"

class Triangle
{
public:
	math::vec3 coords[3];
	Triangle(math::vec3, math::vec3, math::vec3);
	Triangle() {}
	Triangle project();
};