#pragma once
#include "Triangle.hpp"

class Block
{
public:
	std::vector<Triangle> tris;
	Block(math::vec3);
	void project(math::mat4x4);
};