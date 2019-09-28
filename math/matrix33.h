#pragma once

#include "vector2.h"

struct matrix33
{
public:
	float m[3][3];

public:
	matrix33() {}

	void set_identity()
	{
		m[0][0] = 1.0f; m[1][0] = 0.0f; m[2][0] = 0.0f;
		m[0][1] = 0.0f; m[1][1] = 1.0f; m[2][1] = 0.0f;
		m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = 1.0f;
	}

	void scale(float s)
	{
		m[0][0] = s;	m[1][0] = 0.0f; m[2][0] = 0.0f;
		m[0][1] = 0.0f; m[1][1] = s;	m[2][1] = 0.0f;
		m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = 1.0f;
	}

	void scale(const vector2& s)
	{
		m[0][0] = s.x;	m[1][0] = 0.0f; m[2][0] = 0.0f;
		m[0][1] = 0.0f; m[1][1] = s.y;	m[2][1] = 0.0f;
		m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = 1.0f;
	}

	void rotate(float angle)
	{
		m[0][0] =  cos(angle); m[1][0] = sin(angle); m[2][0] = 0.0f;
		m[0][1] = -sin(angle); m[1][1] = cos(angle); m[2][1] = 0.0f;
		m[0][2] =        0.0f; m[1][2] =       0.0f; m[2][2] = 1.0f;
	}

	void translate(const vector2& v)
	{
		m[0][0] = 1.0f; m[1][0] = 0.0f; m[2][0] = 0.0f;
		m[0][1] = 0.0f; m[1][1] = 1.0f; m[2][1] = 0.0f;
		m[0][2] =  v.x; m[1][2] =  v.y; m[2][2] = 1.0f;
	}

	matrix33 operator * (const matrix33& mx) const
	{
		matrix33 result;

		result.m[0][0] = m[0][0] * mx.m[0][0] + m[1][0] * mx.m[0][1] + m[2][0] * mx.m[0][2];
		result.m[0][1] = m[0][1] * mx.m[0][0] + m[1][1] * mx.m[0][1] + m[2][1] * mx.m[0][2];
		result.m[0][2] = m[0][2] * mx.m[0][0] + m[1][2] * mx.m[0][1] + m[2][2] * mx.m[0][2];

		result.m[1][0] = m[0][0] * mx.m[1][0] + m[1][0] * mx.m[1][1] + m[2][0] * mx.m[1][2];
		result.m[1][1] = m[0][1] * mx.m[1][0] + m[1][1] * mx.m[1][1] + m[2][1] * mx.m[1][2];
		result.m[1][2] = m[0][2] * mx.m[1][0] + m[1][2] * mx.m[1][1] + m[2][2] * mx.m[1][2];

		result.m[2][0] = m[0][0] * mx.m[2][0] + m[1][0] * mx.m[2][1] + m[2][0] * mx.m[2][2];
		result.m[2][1] = m[0][1] * mx.m[2][0] + m[1][1] * mx.m[2][1] + m[2][1] * mx.m[2][2];
		result.m[2][2] = m[0][2] * mx.m[2][0] + m[1][2] * mx.m[2][1] + m[2][2] * mx.m[2][2];

		return result;
	}
	
	friend vector2 operator * (const vector2& v, const matrix33& mx)
	{
		vector2 result;

		result.x = v.x * mx.m[0][0] + v.y * mx.m[0][1] + mx.m[0][2];
		result.y = v.x * mx.m[1][0] + v.y * mx.m[1][1] + mx.m[1][2];

		return result;
	}
};