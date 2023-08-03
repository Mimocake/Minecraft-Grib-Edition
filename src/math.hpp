#pragma once
#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>

namespace math
{
	const float aspect = 9.0 / 16.0;
	const float fNear = 0.1;
	const float fFar = 1000;
	const float FOV = 90;

	class mat4x4
	{
	public:
		float m[4][4] = {0};
		mat4x4() {}
		mat4x4(std::vector<std::vector<float>> v)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m[i][j] = v[i][j];
				}
			}
		}
	};

	inline math::mat4x4 mat_makeProj()
	{
		float fFovRad = 1.0f / tanf(FOV * 0.5f / 180.0f * 3.14159f);
		math::mat4x4 matrix;
		matrix.m[0][0] = aspect * fFovRad;
		matrix.m[1][1] = fFovRad;
		matrix.m[2][2] = fFar / (fFar - fNear);
		matrix.m[3][2] = (-fFar * fNear) / (fFar - fNear);
		matrix.m[2][3] = 1.0f;
		matrix.m[3][3] = 0.0f;
		return matrix;
	}

	inline sf::Vector3f mat4x4_mult(sf::Vector3f p, mat4x4 mat)
	{
		float res[3] = {0, 0, 0};
		float vec[3] = {p.x, p.y, p.z};
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				res[i] += vec[i] * mat.m[i][j];
			}
		}
		float w = p.x * mat.m[0][3] + p.y * mat.m[1][3] + p.z * mat.m[2][3] + mat.m[3][3];
		res[0] /= w; res[1] /= w;
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

	inline mat4x4 mat_inverse(mat4x4& m)
	{
		mat4x4 matrix;
		matrix.m[0][0] = m.m[0][0]; matrix.m[0][1] = m.m[1][0]; matrix.m[0][2] = m.m[2][0]; matrix.m[0][3] = 0.0f;
		matrix.m[1][0] = m.m[0][1]; matrix.m[1][1] = m.m[1][1]; matrix.m[1][2] = m.m[2][1]; matrix.m[1][3] = 0.0f;
		matrix.m[2][0] = m.m[0][2]; matrix.m[2][1] = m.m[1][2]; matrix.m[2][2] = m.m[2][2]; matrix.m[2][3] = 0.0f;
		matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
		matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
		matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
		matrix.m[3][3] = 1.0f;
		return matrix;
	}

	inline math::mat4x4 mat_pointAt(sf::Vector3f& pos, sf::Vector3f& target, sf::Vector3f& up)
	{
		sf::Vector3f newFor = target - pos;
		math::norm(newFor);

		sf::Vector3f a = newFor * math::dot_prod(up, newFor);
		sf::Vector3f newUp = up - a;
		math::norm(newUp);
		
		sf::Vector3f newRight = math::cross_prod(newUp, newFor);

		math::mat4x4 matrix;
		matrix.m[0][0] = newRight.x;	matrix.m[0][1] = newRight.y;	matrix.m[0][2] = newRight.z;	matrix.m[0][3] = 0.0f;
		matrix.m[1][0] = newUp.x;		matrix.m[1][1] = newUp.y;		matrix.m[1][2] = newUp.z;		matrix.m[1][3] = 0.0f;
		matrix.m[2][0] = newFor.x;   	matrix.m[2][1] = newFor.y;   	matrix.m[2][2] = newFor.z;	    matrix.m[2][3] = 0.0f;
		matrix.m[3][0] = pos.x;			matrix.m[3][1] = pos.y;			matrix.m[3][2] = pos.z;			matrix.m[3][3] = 1.0f;
		return matrix;
	}

};