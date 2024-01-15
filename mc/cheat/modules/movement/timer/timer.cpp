#include "timer.h"
#include "../../../minecraft/c_minecraft.h"

bool timer::toggle = false;
bool timer::awaiting_bind = false;
int timer::bind = 0;
const char* timer::bind_text = "[NONE]##1";

float timer::value = 1.f;
bool timer::block_movement = false;

void timer::use(c_context* ctx)
{	
	if (!ctx->player->getObject() || !ctx->rendermanager->getObject() || !ctx->world->getObject() || !ctx->timer->getObject() || !ctx->gamesettings->getObject())
		return;

	if (!timer::toggle)
	{
		if (ctx->timer->getTimerSpeed(ctx) != 1.f)
			ctx->timer->setTimerSpeed(ctx, 1.f);
		return;
	}
	
	ctx->timer->setTimerSpeed(ctx, timer::value);
}
