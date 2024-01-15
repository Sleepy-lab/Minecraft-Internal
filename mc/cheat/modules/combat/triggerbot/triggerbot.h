#pragma once

#include "../../../cheat.h"
#include "../../../minecraft/c_context.h"
#include "../../../minecraft/c_minecraft.h"

namespace triggerbot
{
	extern bool toggle;
	extern bool awaiting_bind;
	extern int bind;
	extern const char* bind_text;

	extern float threshold;
	extern bool rmb;

	void use(c_context* ctx);
}