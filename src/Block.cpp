#include "Block.hpp"

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

void Block::project()
{	
	proj_tris = vector<Triangle>(0);
	for (int i = 0; i < tris.size(); i++)
	{
		Triangle temp1 = tris[i];
		for (int j = 0; j < 3; j++)
		{
			//temp1.coords[j] = mat4x4_mult(temp1.coords[j], rotx_mat);
		}
		Triangle temp2 = temp1;
		for (int j = 0; j < 3; j++)
		{
			temp2.coords[j].z += 1.5;
			temp2.coords[j] = mat4x4_mult(temp2.coords[j], proj_mat);
		}
		proj_tris.push_back(temp2);
	}
}