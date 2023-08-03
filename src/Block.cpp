#include "Block.hpp"
using namespace math;
using namespace std;

Block::Block(vec3 origin)
{
	tris = {
		// SOUTH
		Triangle(vec3(origin.x, origin.y, origin.z), vec3(origin.x, origin.y + 1, origin.z), vec3(origin.x + 1, origin.y + 1, origin.z)),
		Triangle(vec3(origin.x, origin.y, origin.z), vec3(origin.x + 1, origin.y + 1, origin.z), vec3(origin.x + 1, origin.y, origin.z)),

		// EAST                                                      
		Triangle(vec3(origin.x + 1, origin.y, origin.z), vec3(origin.x + 1, origin.y + 1, origin.z), vec3(origin.x + 1, origin.y + 1, origin.z + 1)),
		Triangle(vec3(origin.x + 1, origin.y, origin.z), vec3(origin.x + 1, origin.y + 1, origin.z + 1), vec3(origin.x + 1, origin.y, origin.z + 1)),

		// NORTH                                                     
		Triangle(vec3(origin.x + 1, origin.y, origin.z + 1), vec3(origin.x + 1, origin.y + 1, origin.z + 1), vec3(origin.x, origin.y + 1, origin.z + 1)),
		Triangle(vec3(origin.x + 1, origin.y, origin.z + 1), vec3(origin.x, origin.y + 1, origin.z + 1), vec3(origin.x, origin.y, origin.z + 1)),

		// WEST                                                      
		Triangle(vec3(origin.x, origin.y, origin.z + 1), vec3(origin.x, origin.y + 1, origin.z + 1), vec3(origin.x, origin.y + 1, origin.z)),
		Triangle(vec3(origin.x, origin.y, origin.z + 1), vec3(origin.x, origin.y + 1, origin.z), vec3(origin.x, origin.y, origin.z)),

		// TOP                                                       
		Triangle(vec3(origin.x, origin.y + 1, origin.z), vec3(origin.x, origin.y + 1, origin.z + 1), vec3(origin.x + 1, origin.y + 1, origin.z + 1)),
		Triangle(vec3(origin.x, origin.y + 1, origin.z), vec3(origin.x + 1, origin.y + 1, origin.z + 1), vec3(origin.x + 1, origin.y + 1, origin.z)),

		// BOTTOM                                                    
		Triangle(vec3(origin.x + 1, origin.y, origin.z + 1), vec3(origin.x, origin.y, origin.z + 1), vec3(origin.x, origin.y, origin.z)),
		Triangle(vec3(origin.x + 1, origin.y, origin.z + 1), vec3(origin.x, origin.y, origin.z), vec3(origin.x + 1, origin.y, origin.z)),
	};
}

void Block::project(math::mat4x4 matView)
{	
	for (int i = 0; i < tris.size(); i++)
	{
		tris[i].project(matView);
	}
}