#include "Functions.hpp"

Vector3f mat4x4_mult(Vector3f p, vector<vector<float>> mat)
{
	vector<float> res(3, 0);
	vector<float> vec = { p.x, p.y, p.z };
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			res[i] += vec[i] * mat[i][j];
		}
	}
	float w = p.x * mat[0][3] + p.y * mat[1][3] + p.z * mat[2][3] + mat[3][3];
	res[0] /= w; res[1] /= w;
	return Vector3f(res[0], res[1], res[2]);
}