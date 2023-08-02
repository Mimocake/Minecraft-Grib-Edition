#pragma once
#include "math.hpp"

class Triangle
{
public:
	std::vector<sf::Vector3f> coords;
	sf::Vector3f normal;
	Triangle(sf::Vector3f, sf::Vector3f, sf::Vector3f);
	Triangle() {}
	void project();
};