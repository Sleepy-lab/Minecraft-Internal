#pragma once

#include "../../../cheat.h"
#include "../../../minecraft/c_context.h"

namespace sprint
{
	extern bool toggle;
	extern bool awaiting_bind;
	extern int bind;
	extern const char* bind_text;

	void use(c_context* ctx);
}