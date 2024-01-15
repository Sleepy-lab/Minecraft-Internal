#include "clicker.h"

bool clicker::left::toggle = false;
bool clicker::left::awaiting_bind = false;
int clicker::left::bind = 0;
const char* clicker::left::bind_text = "[NONE]##1";

float clicker::left::value = 0.0f;

void clicker::left::thread()
{
	while (cheat::inst->b_running)
	{
		while (clicker::left::toggle && clicker::left::value != 0 && GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			POINT clicker_mouse1;
			GetCursorPos(&clicker_mouse1);
			HWND clicker_window = WindowFromPoint(clicker_mouse1);

			if (FindWindow(("LWJGL"), nullptr) == GetForegroundWindow())
			{
				if (ScreenToClient(clicker_window, &clicker_mouse1))
				{
					if (clicker_mouse1.y > 20)
					{
						int delay = (2000 / clicker::left::value) / 1;

						PostMessage(clicker_window, WM_LBUTTONDOWN, 10, MAKELPARAM(clicker_mouse1.x, clicker_mouse1.y));
						PostMessage(clicker_window, WM_LBUTTONUP, 11, MAKELPARAM(clicker_mouse1.x, clicker_mouse1.y));

						Sleep(rand() % delay);
					}
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}
}