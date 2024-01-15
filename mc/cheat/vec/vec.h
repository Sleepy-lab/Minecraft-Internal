#pragma once
#include <cmath>
#include <algorithm>

#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))

template <typename T>
T clipNum(const T& n, const T& lower, const T& upper) { return max(lower, min(n, upper)); }

typedef float matrix_t[3][4];

class vec2_t;
class vec3_t 
{
public:
	vec3_t();
	vec3_t(vec2_t);
	vec3_t(float, float, float);
	~vec3_t();

	float x, y, z; // 12 bytes

	vec3_t& operator+=(const vec3_t& v)
	{
		x += v.x; y += v.y; z += v.z; return *this;
	}

	vec3_t& operator-=(const vec3_t& v)
	{
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}

	vec3_t& operator*=(float v)
	{
		x *= v; y *= v; z *= v; return *this;
	}

	vec3_t& operator/=(float v) 
	{
		x /= v; y /= v; z /= v; return *this;
	}

	vec3_t operator/(const vec3_t& v)
	{
		return vec3_t{ x / v.x, y / v.y, z / v.z };
	}

	vec3_t operator-(const vec3_t& v)
	{
		return vec3_t{ x - v.x, y - v.y, z - v.z };
	}

	vec3_t operator+(const vec3_t& v) 
	{
		return vec3_t{ x + v.x, y + v.y, z + v.z };
	}

	vec3_t operator*( float v ) const 
	{
		return vec3_t { x * v, y * v, z * v };
	}

	void clamp();
	vec3_t normalized();
	float normalizeInPlace();
	void normalize();
	float length();
	float lengthSqr();
	vec3_t cross(vec3_t cross);
	bool inRange(double x, double y, double z);
};

class vec2_t 
{
public:
	vec2_t();
	vec2_t(vec3_t);
	vec2_t(float, float);
	~vec2_t();

	float x, y; // 8 bytes

	vec2_t& operator+=(const vec2_t& v)
	{
		x += v.x; y += v.y; return *this;
	}

	vec2_t& operator-=(const vec2_t& v)
	{
		x -= v.x; y -= v.y; return *this;
	}

	vec2_t& operator*=(float v)
	{
		x *= v; y *= v; return *this;
	}

	vec2_t operator-(const vec2_t& v)
	{
		return vec2_t{ x - v.x, y - v.y };
	}

	vec2_t operator+(const vec2_t& v)
	{
		return vec2_t{ x + v.x, y + v.y };
	}

	vec2_t operator*(float v) const
	{
		return vec2_t{ x * v, y * v };
	}

	void clamp();
	vec2_t normalized();
	void normalize();
	float length();
	float lengthSqr();
};

extern vec3_t* vec3_o;
extern vec2_t* vec2_o;