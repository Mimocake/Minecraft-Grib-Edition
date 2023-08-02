#include "Triangle.hpp"
using namespace math;

Triangle::Triangle(sf::Vector3f p1, sf::Vector3f p2, sf::Vector3f p3) : coords(3)
{
	coords[0] = p1; coords[1] = p2; coords[2] = p3;
	normal = cross_prod(p2 - p1, p3 - p1);
}

void Triangle::project()
{
	for (int j = 0; j < 3; j++)
	{
		coords[j].z += 1.5;
		coords[j] = mat4x4_mult(coords[j], proj_mat);
	}
}