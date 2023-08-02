#pragma once
#include "math.hpp"

class Triangle
{
public:
	std::vector<sf::Vector3f> coords;
	Triangle(sf::Vector3f, sf::Vector3f, sf::Vector3f);
	Triangle() {}
	void project();
};