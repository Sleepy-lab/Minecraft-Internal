#pragma once

#include "../../../cheat.h"
#include <variant>

namespace gui
{
	extern HWND hwnd;
	extern HDC old_dc;
	
	extern float menu_color[3];
	extern float item_alpha;

	void drawMenu(HDC dc);
	extern bool draw_ui;
	extern bool draw_hud;
}