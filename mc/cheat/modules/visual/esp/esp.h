#pragma once

#include "../../../cheat.h"
#include "../../../minecraft/c_context.h"

namespace esp
{
	extern bool toggle;
	extern bool awaiting_bind;
	extern int bind;
	extern const char* bind_text;

	extern std::vector<std::vector<double>> list_n;
	extern std::vector<std::vector<std::string>> list_s;
	extern std::vector<std::vector<double>> _3d_list_n;

	extern bool draw_box;
	extern bool draw_box_filled;
	extern bool draw_outline;

	extern bool draw_nametags;
	extern bool draw_hp;
	extern bool draw_hud;

	extern bool _3d;

	extern float color[4];
	extern float outline_color[4];

	void use(c_context* ctx);
}

