#pragma once

#include "../cheat.h"
#include "player/c_player.h"
#include "world/c_world.h"
#include "render/c_rendermanager.h"
#include "timer/c_timer.h"
#include "gamesettings/c_gamesettings.h"

class c_context
{
public:
	c_player* player;
	c_world* world;
	c_rendermanager* rendermanager;
	c_timer* timer;
	c_gamesettings* gamesettings;
	jobject mc;
};