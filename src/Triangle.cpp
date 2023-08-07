#include "Triangle.hpp"
using namespace std;
using namespace math;

Triangle::Triangle(vec3 p1, vec3 p2, vec3 p3)
{
	coords[0] = p1; coords[1] = p2; coords[2] = p3;
}

Triangle Triangle::project()
{
	Triangle proj;
	for (int j = 0; j < 3; j++)
	{
		proj.coords[j] = mat4x4_mult(coords[j], proj_mat);
		proj.coords[j].x /= proj.coords[j].z; proj.coords[j].y /= proj.coords[j].z;
	}
	return proj;
}

vector<Triangle> Triangle::clip_fun(math::vec3 plane_p, math::vec3 plane_n)
{
	plane_n.norm();

	auto dist = [&](vec3& p)
	{
		vec3 n = p;
		n.norm();
		return (plane_n.x * p.x + plane_n.y * p.y + plane_n.z * p.z - dot_prod(plane_n, plane_p));
	};

	vec3 inside[3];  int inside_count = 0;
	vec3 outside[3]; int outside_count = 0;

	for (int i = 0; i < 3; i++)
	{
		if (dist(this->coords[i]) >= 0) inside[inside_count++] = this->coords[i];
		else outside[outside_count++] = this->coords[i];
	}

	if (inside_count == 0) return vector<Triangle>(0);
	if (inside_count == 3) return vector<Triangle>(1, *this);
	if (inside_count == 1 && outside_count == 2)
	{
		Triangle out;
		out.coords[0] = inside[0];
		out.coords[1] = intersectPlane(plane_p, plane_n, inside[0], outside[0]);
		out.coords[2] = intersectPlane(plane_p, plane_n, inside[0], outside[1]);
		return vector<Triangle>{ out };
	}
	if (inside_count == 2 && outside_count == 1)
	{
		Triangle out1, out2;

		out1.coords[0] = inside[0];
		out1.coords[1] = inside[1];
		out1.coords[2] = intersectPlane(plane_p, plane_n, inside[0], outside[0]);

		out2.coords[0] = inside[1];
		out2.coords[1] = out1.coords[2];
		out2.coords[2] = intersectPlane(plane_p, plane_n, inside[1], outside[0]);

		return vector<Triangle>{ out1, out2 };
	}
}
