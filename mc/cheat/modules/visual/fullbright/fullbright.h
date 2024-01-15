#pragma once

#include "../../../cheat.h"
#include "../../../minecraft/c_context.h"

namespace fullbright
{
	extern bool toggle;
	extern bool awaiting_bind;
	extern int bind;
	extern const char* bind_text;

	extern float old;

	void use(c_context* ctx);
}

