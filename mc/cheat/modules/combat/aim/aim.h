#pragma once

#include "../../../cheat.h"
#include "../../../minecraft/c_context.h"
#include "../../../minecraft/c_minecraft.h"

namespace aim
{
	extern bool toggle;
	extern bool awaiting_bind;
	extern int bind;
	extern const char* bind_text;

	extern float speed;
	extern float fov;
	extern float distance;
	extern bool low_health;

	extern char whitelist[256];

	extern bool require_lmb;
	extern bool require_rmb;

	extern bool visibility_check;
	extern bool smart;
	extern bool predict;
	extern float predict_strength;
	
	void use(c_context* ctx);
}