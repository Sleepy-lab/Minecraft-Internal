#pragma once

#include "../../cheat.h"
#include "../player/c_player.h"

class c_context;
class c_world
{
private:
	jobject object;
public:
	c_world(jobject obj);
	~c_world();

	const jobject getObject();

	std::vector<jobject> getPlayers(c_context* ctx);
};

