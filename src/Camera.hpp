#pragma once
#include "math.hpp"

class Camera
{
public:
	math::vec3 loc;
	math::vec3 look_dir;
	Camera() : loc(math::vec3(0, 0, 0)), look_dir(math::vec3(0, 0, 1)) {}
	Camera(math::vec3& loc_, math::vec3& look_dir_) : loc(loc_) , look_dir(look_dir_) {}
	void turn(float&, float&);
};
