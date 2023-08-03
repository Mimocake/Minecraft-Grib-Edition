#include "Triangle.hpp"
using namespace math;

Triangle::Triangle(vec3 p1, vec3 p2, vec3 p3)
{
	coords[0] = p1; coords[1] = p2; coords[2] = p3;
	normal = cross_prod(p2 - p1, p3 - p1);
}

void Triangle::project(mat4x4 matView)
{
	for (int j = 0; j < 3; j++)
	{
		viewed_coords[j] = mat4x4_mult(coords[j], matView);
		proj_coords[j] = proj_mat_mult(viewed_coords[j], proj_mat);
	}
}