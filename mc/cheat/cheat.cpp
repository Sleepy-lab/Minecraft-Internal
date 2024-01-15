#include "cheat.h"

#include "minecraft/c_context.h"
#include "minecraft/c_minecraft.h"
#include "minecraft/player/c_player.h"
#include "minecraft/world/c_world.h"
#include "minecraft/render/activerenderinfo.h"
#include "minecraft/render/c_rendermanager.h"
#include "minecraft/timer/c_timer.h"

#include "modules/combat/aim/aim.h"
#include "modules/combat/clicker/clicker.h"
#include "modules/combat/triggerbot/triggerbot.h"

#include "modules/movement/timer/timer.h"
#include "modules/movement/blink/blink.h"
#include "modules/movement/sprint/sprint.h"

#include "modules/visual/gui/gui.h"
#include "modules/visual/esp/esp.h"
#include "modules/visual/esp/hud.h"
#include "modules/visual/fullbright/fullbright.h"

#include "modules/threads.h"

std::string cheat::title = "";

bool cheat::c_cheat::init()
{
	jsize count;
	if (JNI_GetCreatedJavaVMs(&cheat::inst->vm, 1, &count) != JNI_OK || count == 0)
	{
		return false;
	}

	jint res = cheat::inst->vm->GetEnv((void**)&cheat::inst->env, JNI_VERSION_1_6);
	if (res == JNI_EDETACHED)
	{
		res = cheat::inst->vm->AttachCurrentThread((void**)&cheat::inst->env, nullptr);
	}

	if (res != JNI_OK)
	{
		return false;
	}

	while (!(cheat::hooks::inst->opengl_dll = GetModuleHandleA("opengl32.dll")))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	while (!(cheat::hooks::inst->ws2_32_dll = GetModuleHandleA("Ws2_32.dll")))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	cheat::hooks::inst->m_wglSwapBuffers = GetProcAddress(cheat::hooks::inst->opengl_dll, "wglSwapBuffers");
	cheat::hooks::inst->m_WSASend = GetProcAddress(cheat::hooks::inst->ws2_32_dll, "WSASend");

	MH_Initialize();

	MH_CreateHook(cheat::hooks::inst->m_wglSwapBuffers, cheat::hooks::wglSwapBuffers_hk, reinterpret_cast<void**>(&og_wglSwapBuffers));
	MH_CreateHook(cheat::hooks::inst->m_WSASend, cheat::hooks::WSASend_hk, reinterpret_cast<void**>(&og_WSASend));

	MH_EnableHook(MH_ALL_HOOKS);

	while (cheat::wnd->hwnd == NULL)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	mc->getLaunchWrapper();

	cheat::hooks::inst->m_wndproc = SetWindowLongPtr(cheat::wnd ->hwnd, GWLP_WNDPROC, (LONG_PTR)cheat::hooks::wndproc_hk);

	cheat::inst->b_running = true;
	return cheat::inst->b_running;
}

void cheat::c_cheat::run()
{
	c_context* ctx = new c_context();

	while (cheat::inst->b_running)
	{

		jobject mc_obj = mc->getMinecraft(ctx);
		ctx->mc = mc_obj;
		if (!ctx->mc)
			break;

		jobject player_obj = mc->getPlayer(ctx);
		c_player* player = new c_player(player_obj);

		jobject world_obj = mc->getWorld(ctx);
		c_world* world = new c_world(world_obj);

		jobject rendermanager_obj = mc->getRenderManager(ctx);
		c_rendermanager* rendermanager = new c_rendermanager(rendermanager_obj);

		jobject timer_obj = mc->getTimer(ctx);
		c_timer* timer = new c_timer(timer_obj);

		jobject gamesettings_obj = mc->getGameSettings(ctx);
		c_gamesettings* gamesettings = new c_gamesettings(gamesettings_obj);

		if (world->getObject() && player->getObject() && rendermanager->getObject() && timer->getObject() && gamesettings->getObject())
		{
			ctx->player = player;
			ctx->world = world;
			ctx->timer = timer;
			ctx->rendermanager = rendermanager;
			ctx->gamesettings = gamesettings;
			
			// menu check
			CURSORINFO m_info = { sizeof(CURSORINFO) };
			GetCursorInfo(&m_info);
			cheat::inst->b_inventory = ((int)m_info.hCursor > 50000 & (int)m_info.hCursor < 100000);


			// left clicker
			if (clicker::left::toggle)
			{
				if (threads::hLeftClicker == INVALID_HANDLE_VALUE)
				{
					threads::hLeftClicker = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&clicker::left::thread, 0, 0, 0);
				}
			}
			else if (!clicker::left::toggle)
			{
				if (threads::hLeftClicker != INVALID_HANDLE_VALUE)
				{
					TerminateThread(threads::hLeftClicker, 0);
					threads::hLeftClicker = INVALID_HANDLE_VALUE;
				}
			}

			// aim
			if (aim::toggle)
				aim::use(ctx);

			// esp
			if (esp::toggle)
			{
				esp::use(ctx);
				activerenderinfo::fetchViewport(ctx);
				activerenderinfo::fetchProjectionMatrix(ctx);
				activerenderinfo::fetchModelviewMatrix(ctx);

				if (esp::draw_hud)
					hud::use(ctx);

				// std::cout << hud::health << " | " << hud::name << std::endl;
			}

			// timer
			if (::timer::toggle)
				::timer::use(ctx);
			else if (!::timer::toggle && ctx->timer->getTimerSpeed(ctx) != 1.f)
				ctx->timer->setTimerSpeed(ctx, 1.f);

			// blink
			if (blink::toggle)
				blink::use(ctx);

			// fullbright
			if (fullbright::toggle)
				fullbright::use(ctx);
			else if (!fullbright::toggle && ctx->gamesettings->getGammaSetting(ctx) > 2.f)
				ctx->gamesettings->setGammaSetting(ctx, 1.f);

			// sprint
			if (sprint::toggle)
				ctx->player->setSprinting(ctx, true);
			
			// triggerbot
			if (triggerbot::toggle)
				triggerbot::use(ctx);
		}
		else
		{
			if (esp::toggle)
			{
				esp::list_n = {};
				esp::list_s = {};
				esp::_3d_list_n = {};
			}
		}

		cheat::inst->env->DeleteLocalRef(mc_obj);
		cheat::inst->env->DeleteLocalRef(player_obj);
		cheat::inst->env->DeleteLocalRef(world_obj);
		cheat::inst->env->DeleteLocalRef(rendermanager_obj);
		cheat::inst->env->DeleteLocalRef(timer_obj);
		cheat::inst->env->DeleteLocalRef(gamesettings_obj);

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
	cheat::inst->b_running = false;
	ctx->gamesettings->setGammaSetting(ctx, 1.f);
	ctx->timer->setTimerSpeed(ctx, 1.f);
}

void cheat::c_cheat::exit()
{
	aim::toggle = false;
	esp::toggle = false;
	timer::toggle = false;
	blink::toggle = false;

	std::this_thread::sleep_for(std::chrono::milliseconds(250));

	FreeConsole();

	SetWindowLongPtrA(cheat::wnd->hwnd, GWLP_WNDPROC, (LONG_PTR)cheat::hooks::inst->m_wndproc);

	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();

	cheat::inst->vm->DetachCurrentThread();
}