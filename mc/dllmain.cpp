#include "cheat/cheat.h"

HINSTANCE inst;
HWND hwnd;

cheat::c_cheat* cheat::inst = new cheat::c_cheat();
cheat::c_hooks* cheat::hooks::inst = new cheat::c_hooks();
cheat::c_window* cheat::wnd = new cheat::c_window();

void init()
{
    AllocConsole();
    SetConsoleCtrlHandler(NULL, true);
    FILE* fIn;
    FILE* fOut;
    freopen_s(&fIn, "conin$", "r", stdin);
    freopen_s(&fOut, "conout$", "w", stdout);
    freopen_s(&fOut, "conout$", "w", stderr);

    if (cheat::inst->init())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        cheat::inst->run();
    }
   
    cheat::inst->exit();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    FreeLibraryAndExitThread(inst, 0);
}

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam) 
{
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, msg, param, lparam);
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        srand(time(NULL));

        inst = hModule;
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&init, 0, 0, 0);
        break;
    default:
        break;
    }
    return TRUE;
}