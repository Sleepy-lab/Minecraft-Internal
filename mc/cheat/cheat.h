#pragma once

#include "include.h"

namespace cheat
{
	extern std::string title;
	class c_cheat
	{
	public:
		JNIEnv* env;
		JavaVM* vm;

		jmethodID findclass_mtd;
		jobject classloader_obj;

		bool init();
		void run();
		void exit();

		bool b_running = false;
		bool b_menu = false;
		bool b_inventory = false;
	};

	class c_hooks
	{
	public:
		HMODULE opengl_dll = nullptr;
		HMODULE ws2_32_dll = nullptr;

		LONG_PTR m_wndproc;
		void* m_wglSwapBuffers;
		void* m_WSASend;
	};

	namespace hooks
	{
		extern c_hooks* inst;

		LRESULT __stdcall wndproc_hk(HWND, UINT, WPARAM, LPARAM);
		bool __stdcall wglSwapBuffers_hk(_In_ HDC hdc);
		int __stdcall WSASend_hk(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
	}

	class c_window
	{
	public:
		HWND hwnd;
	};

	extern c_cheat* inst;
	extern c_window* wnd;
}

using fn_wglSwapBuffers = bool(__stdcall*)(_In_ HDC);
extern fn_wglSwapBuffers og_wglSwapBuffers;

using fn_WSASend = int(__stdcall*)(SOCKET, LPWSABUF, DWORD, LPDWORD, DWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
extern fn_WSASend og_WSASend;