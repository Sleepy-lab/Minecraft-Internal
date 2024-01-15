#include "fullbright.h"

bool fullbright::toggle = false;
bool fullbright::awaiting_bind = false;
int fullbright::bind = 0;
const char* fullbright::bind_text = "[NONE]##1";
float fullbright::old = 0.f;

void fullbright::use(c_context* ctx)
{
	if (!fullbright::toggle)
		return;

	if (!ctx->player->getObject() || !ctx->rendermanager->getObject() || !ctx->world->getObject() || !ctx->timer->getObject() || !ctx->gamesettings->getObject())
		return;

	ctx->gamesettings->setGammaSetting(ctx, 1000000.f);
}