#pragma once
#include "../include.h"
#include "../vec/vec.h"

__forceinline double pi() { return 3.14159265358979323846; }

#define deg_to_rad(x)  ((float)(x) * (float)(pi()) / 180.f))
#define rad_to_deg(x)  ((float)(x) * (float)(180.f / pi()))

class math_t 
{
public:
	double distance(double x, double y);
	double distance(double x1, double y1, double z1, double x2, double y2, double z2);
	float radiantsToDeg(float x);
	float degToRadiants(float r);
	float wrapTo180(float value);
	std::pair<float, float> getAngles(std::vector<double> pos, std::vector<double> pos1);
	double uniform(double min, double max);
	bool inRange(double x, double y, double z);
}; extern math_t math;