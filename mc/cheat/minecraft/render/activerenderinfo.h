#pragma once

#include "../../cheat.h"

class c_context;
namespace activerenderinfo
{
	void fetchViewport(c_context* ctx);
	void fetchModelviewMatrix(c_context* ctx);
	void fetchProjectionMatrix(c_context* ctx);

	extern GLint viewport[16];
	extern GLfloat modelview[16];
	extern GLfloat projection[16];
};