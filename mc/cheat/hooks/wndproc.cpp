#include "../cheat.h"

#include "../modules/combat/aim/aim.h"

#include "../modules/movement/timer/timer.h"
#include "../modules/movement/blink/blink.h"
#include "../modules/movement/sprint/sprint.h"

#include "../modules/visual/gui/gui.h"
#include "../modules/visual/esp/esp.h"
#include "../modules/visual/fullbright/fullbright.h"

#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_win32.h"
#include "../../imgui/imgui_impl_opengl3.h"
#include "../../imgui/imgui_internal.h"
#include "../../imgui/imstb_rectpack.h"
#include "../../imgui/imstb_truetype.h"
#include "../../imgui/imstb_textedit.h"
#include "../../imgui/imgui_impl_win32.h"

const char* keyString(size_t hex) {
	const char* const key_str[] = {
		"Unknown",
		"LButton",
		"RButton",
		"CANCEL",
		"MButton",
		"MButton2",
		"MButton3",
		"Unknown",
		"Back",
		"Tab",
		"Unknown",
		"Unknown",
		"Clear",
		"Return",
		"Unknown",
		"Unknown",
		"Shift",
		"Control",
		"Menu",
		"Pause",
		"Capital",
		"Unknown",
		"Unknown",
		"Unknown",
		"Final",
		"Unknown",
		"Unknown",
		"Escape",
		"Convert",
		"NonConvert",
		"Accept",
		"ModeChange",
		"Space",
		"Prior",
		"Next",
		"End",
		"Home",
		"Left",
		"Up",
		"Right",
		"Down",
		"Select",
		"Print",
		"Execute",
		"SnpShot",
		"Insert",
		"Delete",
		"Help",
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"Lwin",
		"Rwin",
		"Apps",
		"Unknown",
		"Sleep",
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"*",
		"+",
		"Separator",
		"-",
		"Decimal",
		"/",
		"F1",
		"F2",
		"F3",
		"F4",
		"F5",
		"F6",
		"F7",
		"F8",
		"F9",
		"F10",
		"F11",
		"F12",
		"F13",
		"F14",
		"F15",
		"F16",
		"F17",
		"F18",
		"F19",
		"F20",
		"F21",
		"F22",
		"F23",
		"F24",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Numlock",
		"Scroll",
		"Equal",
		"Masshou",
		"Touroku",
		"Loya",
		"Roya",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"LShift",
		"RShift",
		"Control",
		"Control",
		"Menu",
		"RMenu"
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Semicolon",
		"Plus",
		"Comma",
		"Minus",
		"Dot",
		"Slash",
		"Tilde",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Brackets",
		"Backslash",
		"Brackets",
		"Apostrophe",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
	};
	return key_str[hex];
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT __stdcall cheat::hooks::wndproc_hk(const HWND window_handle, UINT user_msg, WPARAM wparam, LPARAM lparam)
{
	if (GetAsyncKeyState(VK_INSERT) & 1)
		gui::draw_ui = !gui::draw_ui;

	if (GetAsyncKeyState(VK_END) & 1)
		cheat::inst->b_running = false;

	if (GetAsyncKeyState(VK_HOME) & 1)
		gui::draw_hud = !gui::draw_hud;

	// key bind handlers
	if (user_msg == WM_KEYDOWN && ((gui::draw_ui && cheat::inst->b_inventory) || (!cheat::inst->b_inventory)))
	{
		// aim
		if (aim::awaiting_bind)
		{
			aim::awaiting_bind = false;
			if (wparam == VK_ESCAPE)
			{
				aim::bind = NULL;
				aim::bind_text = "[NONE]##1";
			}
			else if (wparam != VK_ESCAPE)
			{
				aim::bind = wparam;
				aim::bind_text = keyString(wparam);
			}

		}
		else if (!aim::awaiting_bind && wparam == aim::bind)
		{
			aim::toggle = !aim::toggle;
		}

		// blink
		if (blink::awaiting_bind)
		{
			blink::awaiting_bind = false;
			if (wparam == VK_ESCAPE)
			{
				blink::bind = NULL;
				blink::bind_text = "[NONE]##1";
			}
			else if (wparam != VK_ESCAPE)
			{
				blink::bind = wparam;
				blink::bind_text = keyString(wparam);
			}

		}
		else if (!blink::awaiting_bind && blink::toggle && wparam == blink::bind)
		{
			blink::active = !blink::active;
		}

		// timer
		if (timer::awaiting_bind)
		{
			timer::awaiting_bind = false;
			if (wparam == VK_ESCAPE)
			{
				timer::bind = NULL;
				timer::bind_text = "[NONE]##1";
			}
			else if (wparam != VK_ESCAPE)
			{
				timer::bind = wparam;
				timer::bind_text = keyString(wparam);
			}

		}
		else if (!timer::awaiting_bind && wparam == timer::bind)
		{
			timer::toggle = !timer::toggle;
		}

		// esp
		if (esp::awaiting_bind)
		{
			esp::awaiting_bind = false;
			if (wparam == VK_ESCAPE)
			{
				esp::bind = NULL;
				esp::bind_text = "[NONE]##1";
			}
			else if (wparam != VK_ESCAPE)
			{
				esp::bind = wparam;
				esp::bind_text = keyString(wparam);
			}

		}
		else if (!esp::awaiting_bind && wparam == esp::bind)
		{
			esp::toggle = !esp::toggle;
		}

		// fullbright
		if (fullbright::awaiting_bind)
		{
			fullbright::awaiting_bind = false;
			if (wparam == VK_ESCAPE)
			{
				fullbright::bind = NULL;
				fullbright::bind_text = "[NONE]##1";
			}
			else if (wparam != VK_ESCAPE)
			{
				fullbright::bind = wparam;
				fullbright::bind_text = keyString(wparam);
			}

		}
		else if (!fullbright::awaiting_bind && wparam == fullbright::bind)
		{
			fullbright::toggle = !fullbright::toggle;
		}

		// sprint
		if (sprint::awaiting_bind)
		{
			sprint::awaiting_bind = false;
			if (wparam == VK_ESCAPE)
			{
				sprint::bind = NULL;
				sprint::bind_text = "[NONE]##1";
			}
			else if (wparam != VK_ESCAPE)
			{
				sprint::bind = wparam;
				sprint::bind_text = keyString(wparam);
			}

		}
		else if (!sprint::awaiting_bind && wparam == sprint::bind)
		{
			sprint::toggle = !sprint::toggle;
		}
	}

	if (timer::toggle && timer::block_movement && user_msg == WM_KEYDOWN && (wparam == 0x57 || wparam == 0x41 || wparam == 0x53 || wparam == 0x44 || wparam == 0x20))
		return 1l;

	// imgui handler for menu
	if (gui::draw_ui)
	{
		ImGui_ImplWin32_WndProcHandler(window_handle, user_msg, wparam, lparam);
		return 1l;
	}

	return CallWindowProcW((WNDPROC)cheat::hooks::inst->m_wndproc, window_handle, user_msg, wparam, lparam);
}