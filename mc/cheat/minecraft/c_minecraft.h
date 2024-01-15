#pragma once

#include "../cheat.h"
#include "../minecraft/c_context.h"

class c_minecraft
{
public:
	std::string ctx_player_held_item = "";
	bool ctx_objectmouseover_isblock = false;
	bool getLaunchWrapper();
	jclass FFindClass(const char* name);
	jobject getMinecraft(c_context* ctx);
	jobject getPlayer(c_context* ctx);
	jobject getWorld(c_context* ctx);
	jobject getRenderManager(c_context* ctx);
	jobject getTimer(c_context* ctx);
	jobject getGameSettings(c_context* ctx);
};

extern c_minecraft* mc;