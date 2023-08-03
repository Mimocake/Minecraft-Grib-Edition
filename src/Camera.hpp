#pragma once
#include "math.hpp"

class Camera
{
public:
	sf::Vector3f loc;
	sf::Vector3f look_dir;
	Camera() : loc(sf::Vector3f(0, 0, 0)), look_dir(sf::Vector3f(0, 0, 1)) {}
	Camera(sf::Vector3f& loc_, sf::Vector3f& look_dir_) : loc(loc_) , look_dir(look_dir_) {}
};
