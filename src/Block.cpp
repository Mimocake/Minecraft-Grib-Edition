#include "Block.hpp"
using namespace sf;
using namespace std;

Block::Block(Vector3f origin)
{
	tris = {
		// SOUTH
		Triangle(Vector3f(origin.x, origin.y, origin.z), Vector3f(origin.x, origin.y + 1, origin.z), Vector3f(origin.x + 1, origin.y + 1, origin.z)),
		Triangle(Vector3f(origin.x, origin.y, origin.z), Vector3f(origin.x + 1, origin.y + 1, origin.z), Vector3f(origin.x + 1, origin.y, origin.z)),

		// EAST                                                      
		Triangle(Vector3f(origin.x + 1, origin.y, origin.z), Vector3f(origin.x + 1, origin.y + 1, origin.z), Vector3f(origin.x + 1, origin.y + 1, origin.z + 1)),
		Triangle(Vector3f(origin.x + 1, origin.y, origin.z), Vector3f(origin.x + 1, origin.y + 1, origin.z + 1), Vector3f(origin.x + 1, origin.y, origin.z + 1)),

		// NORTH                                                     
		Triangle(Vector3f(origin.x + 1, origin.y, origin.z + 1), Vector3f(origin.x + 1, origin.y + 1, origin.z + 1), Vector3f(origin.x, origin.y + 1, origin.z + 1)),
		Triangle(Vector3f(origin.x + 1, origin.y, origin.z + 1), Vector3f(origin.x, origin.y + 1, origin.z + 1), Vector3f(origin.x, origin.y, origin.z + 1)),

		// WEST                                                      
		Triangle(Vector3f(origin.x, origin.y, origin.z + 1), Vector3f(origin.x, origin.y + 1, origin.z + 1), Vector3f(origin.x, origin.y + 1, origin.z)),
		Triangle(Vector3f(origin.x, origin.y, origin.z + 1), Vector3f(origin.x, origin.y + 1, origin.z), Vector3f(origin.x, origin.y, origin.z)),

		// TOP                                                       
		Triangle(Vector3f(origin.x, origin.y + 1, origin.z), Vector3f(origin.x, origin.y + 1, origin.z + 1), Vector3f(origin.x + 1, origin.y + 1, origin.z + 1)),
		Triangle(Vector3f(origin.x, origin.y + 1, origin.z), Vector3f(origin.x + 1, origin.y + 1, origin.z + 1), Vector3f(origin.x + 1, origin.y + 1, origin.z)),

		// BOTTOM                                                    
		Triangle(Vector3f(origin.x + 1, origin.y, origin.z + 1), Vector3f(origin.x, origin.y, origin.z + 1), Vector3f(origin.x, origin.y, origin.z)),
		Triangle(Vector3f(origin.x + 1, origin.y, origin.z + 1), Vector3f(origin.x, origin.y, origin.z), Vector3f(origin.x + 1, origin.y, origin.z)),
	};
	proj_tris = {};
}

void Block::project(math::mat4x4 matView)
{	
	proj_tris = vector<Triangle>(0);
	for (int i = 0; i < tris.size(); i++)
	{
		tris[i].project(matView);
		proj_tris.push_back(tris[i]);
	}
}