#pragma once
#include "Triangle.hpp"

class Block
{
public:
	std::vector<Triangle> tris;
	std::vector<Triangle> proj_tris;
	Block(sf::Vector3f);
	void project(math::mat4x4);
};