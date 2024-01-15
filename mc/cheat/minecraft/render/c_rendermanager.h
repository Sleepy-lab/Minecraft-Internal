#pragma once

#include "../../cheat.h"

class c_context;
class c_rendermanager
{
private:
	jobject object;
public:
	c_rendermanager(jobject obj);
	~c_rendermanager();

	const jobject getObject();

	double getRenderPositionX(c_context* ctx);
	double getRenderPositionY(c_context* ctx);
	double getRenderPositionZ(c_context* ctx);
	std::vector<double> getRenderPositionVector(c_context* ctx);
};

