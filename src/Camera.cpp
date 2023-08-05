#include "Camera.hpp"

void Camera::turn(float& x, float& y)
{
	look_dir = math::mat4x4_mult(look_dir, math::Matrix_MakeRotationY(-x * math::PI * math::sens));
	look_dir = math::mat4x4_mult(look_dir, math::Matrix_MakeRotationX(-y * math::PI * math::sens));
	look_dir.norm();
	x = 0; y = 0;
}