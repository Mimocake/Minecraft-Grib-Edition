#include "Triangle.hpp"

const float a = 9.0 / 16.0;
const float fNear = 0.1;
const float fFar = 1000;
const float FOV = 90;

const vector<vector<float>> proj_mat = {
	{a / tanf(FOV / 2 / 180 * 3.14159f), 0, 0, 0},
	{0, 1 / tanf(FOV / 2 / 180 * 3.14159f), 0, 0},
	{0, 0, fFar / (fFar - fNear), 1},
    {0, 0, -fFar * fNear / (fFar - fNear), 0}
};

const vector<vector<float>> rotx_mat = {
	{1, 0, 0, 0},
	{0, cos(45.0f), sin(45.0f), 0},
	{0, -sin(45.0f), cos(45.0f), 0},
	{0, 0, 0, 1}
};

const vector<vector<float>> rotz_mat = {
	{cos(45.0f), sin(45.0f), 0, 0},
	{-sin(45.0f), cos(45.0f), 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1}
};

class Block
{
public:
	vector<Triangle> tris;
	vector<Triangle> proj_tris;
	Block(Vector3f);
	void project();
};