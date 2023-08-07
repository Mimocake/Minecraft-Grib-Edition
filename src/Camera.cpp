#include "Camera.hpp"
#include <iostream>
using namespace math;

void Camera::turn(float& x, float& y)
{
	look_dir = mat4x4_mult(look_dir, rot_y(-x * PI * sens));

	float prev_angle_y = angle_y;
	angle_y = angle_y + (y * sens); 
	if (prev_angle_y >= -0.5 && angle_y <= -0.5)
	{
		y = -0.5 - prev_angle_y; angle_y = -0.5;
	}
	else if (prev_angle_y <= 0.5 && angle_y >= 0.5)
	{
		y = 0.5 - prev_angle_y; angle_y = 0.5;
	}
	else y *= sens;

	vec3 hor_dir(look_dir.x, 0, look_dir.z);
	hor_dir.norm();
	float phi = acos(dot_prod(hor_dir, math::vec3(0, 0, 1)));
	phi = (hor_dir.x < 0) ? -phi : phi;
	vec3 temp_dir = mat4x4_mult(look_dir, rot_y(phi));
	temp_dir = mat4x4_mult(temp_dir, rot_x(-y * PI));
	look_dir = mat4x4_mult(temp_dir, rot_y(-phi));
	
	look_dir.norm();
	x = 0; y = 0;
}