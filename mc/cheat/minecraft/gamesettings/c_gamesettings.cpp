#include "c_gamesettings.h"
#include "../c_minecraft.h"

c_gamesettings::c_gamesettings(jobject obj)
{
	object = obj;
}

c_gamesettings::~c_gamesettings()
{
	cheat::inst->env->DeleteLocalRef(object);
}

const jobject c_gamesettings::getObject()
{
	return object;
}

float c_gamesettings::getGammaSetting(c_context* ctx)
{
	if (!ctx->mc)
		return 0;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_74333_Y", "F");
	float res = cheat::inst->env->GetFloatField(object, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

void c_gamesettings::setGammaSetting(c_context* ctx, float value)
{
	if (!ctx->mc)
		return;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_74333_Y", "F");
	cheat::inst->env->SetFloatField(object, fld, value);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);
}