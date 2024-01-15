#include "sprint.h"
#include "../../../minecraft/c_minecraft.h"

bool sprint::toggle = false;
bool sprint::awaiting_bind = false;
int sprint::bind = 0;
const char* sprint::bind_text = "[NONE]##1";

void sprint::use(c_context* ctx)
{	
	if (!ctx->player->getObject() || !ctx->rendermanager->getObject() || !ctx->world->getObject() || !ctx->timer->getObject() || !ctx->gamesettings->getObject())
		return;

	
	
}
