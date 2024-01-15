#include "math.h"

math_t math;

void __forceinline sin_cos(float r, float* s, float* c) { *s = sin( r ); *c = cos( r ); }

float math_t::wrapTo180(float value)
{
	if (value >= 180.f)
		value -= 360.f;
	if (value < -180.f)
		value += 360.f;
	return value;
}

float math_t::radiantsToDeg(float x)
{
	return x * 180.f / 3.14159265359;
}

float math_t::degToRadiants(float r)
{
	return r * 3.14159265359 / 180;
}

double math_t::distance(double x, double y)
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

double math_t::distance(double x1, double y1, double z1, double x2, double y2, double z2)
{
	return distance(y1 - y2, distance(x1 - x2, z1 - z2));
}

std::pair<float, float> math_t::getAngles(std::vector<double> pos, std::vector<double> pos1)
{
	double d_x = pos1[0] - pos[0];
	double d_y = pos1[1] - pos[1];
	double d_z = pos1[2] - pos[2];

	double hypothenuse = sqrt(d_x * d_x + d_z * d_z);
	float yaw = rad_to_deg(atan2(d_z, d_x)) - 90.f;
	float pitch = rad_to_deg(-atan2(d_y, hypothenuse));

	return std::make_pair(yaw, pitch);
}

float wrap_to_180(float value)
{
	if (value >= 180.f)
		value -= 360.f;
	if (value < -180.f)
		value += 360.f;
	return value;
}

double math_t::uniform(double min, double max)
{
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

bool math_t::inRange(double x, double y, double z)
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