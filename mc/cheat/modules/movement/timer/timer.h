#pragma once

#include "../../../cheat.h"
#include "../../../minecraft/c_context.h"

namespace timer
{
	extern bool toggle;
	extern bool awaiting_bind;
	extern int bind;
	extern const char* bind_text;

	extern float value;
	extern bool block_movement;

	void use(c_context* ctx);
}