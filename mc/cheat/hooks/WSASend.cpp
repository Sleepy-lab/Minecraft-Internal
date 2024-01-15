#include "../cheat.h"

#include "../modules/visual/gui/gui.h"
#include "../modules/visual/esp/esp.h"
#include "../modules/movement/blink/blink.h"
#include "../minecraft/render/activerenderinfo.h"

fn_WSASend og_WSASend;

int __stdcall cheat::hooks::WSASend_hk(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	if (cheat::inst->b_running && blink::toggle)
	{
		blink::on_active();
	}

	return og_WSASend(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, lpOverlapped, lpCompletionRoutine);
}