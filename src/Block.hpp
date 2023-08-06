#pragma once
#include "Triangle.hpp"

class Block
{
public:
	std::vector<Triangle> tris;
	std::vector<Triangle> proj_tris;
	Block(math::vec3);
};