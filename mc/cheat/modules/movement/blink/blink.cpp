#include "blink.h"
#include "../../../minecraft/c_minecraft.h"

bool blink::toggle = false;
bool blink::awaiting_bind = false;
int blink::bind = 0;
const char* blink::bind_text = "[NONE]##1";

bool blink::active = false;
bool blink::was_active = false;
float blink::limit = 5;
float blink::timer = 1;
std::chrono::steady_clock::time_point blink::start_time = std::chrono::steady_clock::now();

void blink::use(c_context* ctx)
{	
	if (!blink::toggle)
		return;

	if (!ctx->player->getObject() || !ctx->rendermanager->getObject() || !ctx->world->getObject() || !ctx->timer->getObject() || !ctx->gamesettings->getObject())
		return;
}

void blink::on_active()
{
	if (!blink::toggle || !blink::active)
		return;

	blink::timer = 0;
	int max = blink::limit * 10;
	blink::start_time = std::chrono::steady_clock::now();
	while (blink::active)
	{
		if (blink::timer > max)
			break;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		blink::timer++;
	}
	blink::was_active = true;
	blink::active = false;
}