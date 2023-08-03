#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>

namespace math
{
	const float a = 9.0 / 16.0;
	const float fNear = 0.1;
	const float fFar = 1000;
	const float FOV = 90;

	const std::vector<std::vector<float>> proj_mat = {
		{a / tanf(FOV / 2 / 180 * 3.14159f), 0, 0, 0},
		{0, 1 / tanf(FOV / 2 / 180 * 3.14159f), 0, 0},
		{0, 0, fFar / (fFar - fNear), 1},
		{0, 0, -fFar * fNear / (fFar - fNear), 0}
	};

	inline sf::Vector3f mat4x4_mult(sf::Vector3f p, std::vector<std::vector<float>> mat)
	{
		std::vector<float> res(3, 0);
		std::vector<float> vec = { p.x, p.y, p.z };
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				res[i] += vec[i] * mat[i][j];
			}
		}
		float w = p.x * mat[0][3] + p.y * mat[1][3] + p.z * mat[2][3] + mat[3][3];
		res[0] /= w; res[1] /= w;
		return sf::Vector3f(res[0], res[1], res[2]);
	}

	inline sf::Vector3f mat3x3_mult(sf::Vector3f p, std::vector<std::vector<float>> mat)
	{
		std::vector<float> res(3, 0);
		std::vector<float> vec = { p.x, p.y, p.z };
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				res[i] += vec[i] * mat[i][j];
			}
		}
		return sf::Vector3f(res[0], res[1], res[2]);
	}

	inline sf::Vector3f cross_prod(sf::Vector3f a, sf::Vector3f b)
	{
		return sf::Vector3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}

	inline float dot_prod(sf::Vector3f a, sf::Vector3f b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	inline void norm(sf::Vector3f& vec)
	{
		vec /= sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}
};