#include "vec.h"

vec3_t::vec3_t(void)
{
	x = y = z = 0.0f;
}

vec3_t::vec3_t(float fx, float fy, float fz)
{
	x = fx;
	y = fy;
	z = fz;
}

vec3_t::vec3_t(vec2_t vec)
{
	x = vec.x;
	y = vec.y;
}

vec3_t::~vec3_t(void){};

vec2_t::vec2_t(void)
{
	x = y = 0.0f;
}

vec2_t::vec2_t(float fx, float fy)
{
	x = fx;
	y = fy;
}

vec2_t::vec2_t(vec3_t vec)
{
	x = vec.x;
	y = vec.y;
}

vec2_t::~vec2_t(void){};

void vec3_t::clamp( void ) {
	x = clipNum(x, -89.0f, 89.0f);
	y = clipNum(std::remainder(y, 360.0f), -180.0f, 180.0f);
	z = clipNum(z, -50.0f, 50.0f);
}

void vec3_t::normalize(void)
{
	auto vec_normalize = [&](vec3_t& v)
	{
		auto l = v.length();

		if (l != 0.0f)
		{
			v.x /= l;
			v.y /= l;
			v.z /= l;
		}
		else { v.x = v.y = 0.0f; v.z = 1.0f; }

		return l;
	};

	vec_normalize( *this );
}

vec3_t vec3_t::normalized(void)
{
	vec3_t vec(*this);

	vec.normalize();

	return vec;
}

float vec3_t::normalizeInPlace(void)
{
	vec3_t& v = *this;

	float iradius = 1.f / (this->length() + 1.192092896e-07F); //FLT_EPSILON

	v.x *= iradius;
	v.y *= iradius;
	v.z *= iradius;

	return 1.f;
}

float vec3_t::length( void ) {
	return sqrt(this->lengthSqr());
}

float vec3_t::lengthSqr(void)
{
	auto sqr = [](float n) { return static_cast< float >( n * n ); };

	return (sqr(x) + sqr(y) + sqr(z));
}

vec3_t vec3_t::cross(vec3_t cross)
{
	vec3_t result;
	result.x = y * cross.z - z * cross.y;
	result.y = z * cross.x - x * cross.z;
	result.z = x * cross.y - y * cross.x;
	return result;
}

void vec2_t::clamp(void)
{
	x = clipNum(x, -89.0f, 89.0f);
	y = clipNum(std::remainderf(y, 360.0f), -180.0f, 180.0f);
}

void vec2_t::normalize(void)
{
	float length = this->length();

	if (length)
	{
		x /= length;
		y /= length;
	}
	else
	{
		x = y = 0.0f;
	}
}

vec2_t vec2_t::normalized(void)
{
	vec2_t vec(*this);

	vec.normalize();

	return vec;
}

float vec2_t::length(void)
{
	return sqrt(this->lengthSqr());
}

float vec2_t::lengthSqr(void)
{
	auto sqr = [](float n)
	{
		return static_cast<float>(n * n);
	};

	return (sqr(x) + sqr(y));
}

bool vec3_t::inRange(double x, double y, double z)
{
	if (y > z) {

		if (x > y) return false;
		if (x < z) return false;
		return true;

	}

	if (z > y) {

		if (x > z) return false;
		if (x < y) return false;
		return true;

	}

	return false;
}