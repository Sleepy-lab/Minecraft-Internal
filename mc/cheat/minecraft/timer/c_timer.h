#pragma once

#include "../../cheat.h"

class c_context;
class c_timer
{
private:
	jobject object;
public:
	c_timer(jobject obj);
	~c_timer();

	const jobject getObject();

	float getRenderPartialTicks(c_context* ctx);
	float getTimerSpeed(c_context* ctx);
	void setTimerSpeed(c_context* ctx, float value);
};

