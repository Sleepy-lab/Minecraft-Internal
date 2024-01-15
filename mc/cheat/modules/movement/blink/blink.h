#pragma once

#include "../../../cheat.h"
#include "../../../minecraft/c_context.h"

namespace blink
{
	extern bool toggle;
	extern bool awaiting_bind;
	extern int bind;
	extern const char* bind_text;
	
	extern bool active;
	extern bool was_active;
	extern float limit;
	extern float timer;
	extern std::chrono::steady_clock::time_point start_time;

	void use(c_context* ctx);
	void on_active();
}