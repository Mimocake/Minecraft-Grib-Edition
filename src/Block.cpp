#include "Block.hpp"
using namespace math;
using namespace std;

Block::Block(vec3 o)
{
	tris = {
		// SOUTH
		Triangle(vec3(o.x, o.y, o.z, 1), vec3(o.x, o.y + 1, o.z, 1), vec3(o.x + 1, o.y + 1, o.z, 1), vec2(0, 0), vec2(0, 1), vec2(1, 1)),
		Triangle(vec3(o.x, o.y, o.z), vec3(o.x + 1, o.y + 1, o.z), vec3(o.x + 1, o.y, o.z), vec2(0, 0), vec2(1, 1), vec2(1, 0)),

		// EAST                                                      
		Triangle(vec3(o.x + 1, o.y, o.z, 1), vec3(o.x + 1, o.y + 1, o.z, 1), vec3(o.x + 1, o.y + 1, o.z + 1, 1), vec2(0, 0), vec2(0, 1), vec2(1, 1)),
		Triangle(vec3(o.x + 1, o.y, o.z, 1), vec3(o.x + 1, o.y + 1, o.z + 1, 1), vec3(o.x + 1, o.y, o.z + 1, 1), vec2(0, 0), vec2(1, 1), vec2(1, 0)),

		// NORTH                                                     
		Triangle(vec3(o.x + 1, o.y, o.z + 1, 1), vec3(o.x + 1, o.y + 1, o.z + 1, 1), vec3(o.x, o.y + 1, o.z + 1, 1), vec2(0, 0), vec2(0, 1), vec2(1, 1)),
		Triangle(vec3(o.x + 1, o.y, o.z + 1, 1), vec3(o.x, o.y + 1, o.z + 1, 1), vec3(o.x, o.y, o.z + 1, 1), vec2(0, 0), vec2(1, 1), vec2(1, 0)),

		// WEST                                                      
		Triangle(vec3(o.x, o.y, o.z + 1, 1), vec3(o.x, o.y + 1, o.z + 1, 1), vec3(o.x, o.y + 1, o.z, 1), vec2(0, 0), vec2(0, 1), vec2(1, 1)),
		Triangle(vec3(o.x, o.y, o.z + 1, 1), vec3(o.x, o.y + 1, o.z, 1), vec3(o.x, o.y, o.z, 1), vec2(0, 0), vec2(1, 1), vec2(1, 0)),

		// TOP                                                       
		Triangle(vec3(o.x, o.y + 1, o.z, 1), vec3(o.x, o.y + 1, o.z + 1, 1), vec3(o.x + 1, o.y + 1, o.z + 1, 1), vec2(0, 0), vec2(0, 1), vec2(1, 1)),
		Triangle(vec3(o.x, o.y + 1, o.z, 1), vec3(o.x + 1, o.y + 1, o.z + 1, 1), vec3(o.x + 1, o.y + 1, o.z, 1), vec2(0, 0), vec2(1, 1), vec2(1, 0)),

		// BOTTOM                                                    
		Triangle(vec3(o.x + 1, o.y, o.z + 1, 1), vec3(o.x, o.y, o.z + 1, 1), vec3(o.x, o.y, o.z, 1), vec2(0, 0), vec2(0, 1), vec2(1, 1)),
		Triangle(vec3(o.x + 1, o.y, o.z + 1, 1), vec3(o.x, o.y, o.z, 1), vec3(o.x + 1, o.y, o.z, 1), vec2(0, 0), vec2(1, 1), vec2(1, 0)),
	};
}