#pragma once

#include "../../cheat.h"

class c_context;
class c_gamesettings
{
private:
	jobject object;
public:
	c_gamesettings(jobject obj);
	~c_gamesettings();

	const jobject getObject();
	float getGammaSetting(c_context* ctx);
	void setGammaSetting(c_context* ctx, float value);
};