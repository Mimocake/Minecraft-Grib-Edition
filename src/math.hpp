#pragma once
#include <vector>
#include <math.h>

namespace math
{
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

	const float aspect = 9.0 / 16.0;
	const float fNear = 0.1;
	const float fFar = 1000;
	const float FOV = 90;

	const std::vector<std::vector<float>> proj_vec = {
		{aspect / tanf(FOV / 2 / 180 * 3.14159f), 0, 0, 0},
		{0, 1 / tanf(FOV / 2 / 180 * 3.14159f), 0, 0},
		{0, 0, fFar / (fFar - fNear), 1},
		{0, 0, -fFar * fNear / (fFar - fNear), 0}
	};
	const mat4x4 proj_mat(proj_vec);

	class vec3
	{
	public:
		float x, y, z, w;
		vec3() : x(0), y(0), z(0), w(1) {}
		vec3(float xx, float yy, float zz) : x(xx), y(yy), z(zz), w(1) {}
		friend vec3 operator + (vec3 v1, vec3 v2) { return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z); }
		friend vec3 operator - (vec3 v1, vec3 v2) { return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z); }
		friend vec3 operator * (vec3 v, float f) { return vec3(v.x * f, v.y * f, v.z * f); }
		friend vec3 operator / (vec3 v, float f) { return vec3(v.x / f,v. y / f, v.z / f); }
		friend void operator += (vec3 v1, vec3 v2) { v1.x += v2.x; v1.y += v2.y; v1.z += v2.z; }
		friend void operator -= (vec3 v1, vec3 v2) { v1.x -= v2.x; v1.y -= v2.y; v1.z -= v2.z; }
		friend void operator *= (vec3 v, float f) { v.x * f; v.y * f; v.z * f; }
		friend void operator /= (vec3 v, float f) { v.x / f, v.y / f, v.z / f; }
		friend float dot_prod(vec3 v1, vec3 v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }
		friend vec3 cross_prod(vec3 a, vec3 b) { return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }
		friend void norm(vec3& vec) { vec /= sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z); }
	};

	inline math::vec3 proj_mat_mult(math::vec3 p, mat4x4 mat)
	{
		std::vector<float> res(3, 0);
		std::vector<float> vec = { p.x, p.y, p.z };
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				res[i] += vec[i] * mat.m[i][j];
			}
		}
		float w = p.x * mat.m[0][3] + p.y * mat.m[1][3] + p.z * mat.m[2][3] + mat.m[3][3];
		res[0] /= w; res[1] /= w;
		return math::vec3(res[0], res[1], res[2]);
	}

	inline math::vec3 mat4x4_mult(math::vec3 i, mat4x4 m)
	{
		vec3 v;
		v.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + i.w * m.m[3][0];
		v.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + i.w * m.m[3][1];
		v.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + i.w * m.m[3][2];
		v.w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + i.w * m.m[3][3];
		return v;
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

	inline math::mat4x4 mat_pointAt(math::vec3& pos, math::vec3& target, math::vec3& up)
	{
		math::vec3 newFor = target - pos;
		norm(newFor);

		math::vec3 a = newFor * dot_prod(up, newFor);
		math::vec3 newUp = up - a;
		norm(newUp);
		
		math::vec3 newRight = cross_prod(newUp, newFor);

		math::mat4x4 matrix;
		matrix.m[0][0] = newRight.x;	matrix.m[0][1] = newRight.y;	matrix.m[0][2] = newRight.z;	matrix.m[0][3] = 0.0f;
		matrix.m[1][0] = newUp.x;		matrix.m[1][1] = newUp.y;		matrix.m[1][2] = newUp.z;		matrix.m[1][3] = 0.0f;
		matrix.m[2][0] = newFor.x;   	matrix.m[2][1] = newFor.y;   	matrix.m[2][2] = newFor.z;	    matrix.m[2][3] = 0.0f;
		matrix.m[3][0] = pos.x;			matrix.m[3][1] = pos.y;			matrix.m[3][2] = pos.z;			matrix.m[3][3] = 1.0f;
		return matrix;
	}
};