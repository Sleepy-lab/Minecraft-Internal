#include "c_timer.h"
#include "../c_minecraft.h"

c_timer::c_timer(jobject obj)
{
	object = obj;
}

c_timer::~c_timer()
{
	cheat::inst->env->DeleteLocalRef(object);
}

const jobject c_timer::getObject()
{
	return object;
}

float c_timer::getRenderPartialTicks(c_context* ctx)
{
	if (!ctx->mc)
		return 0.f;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_74281_c", "F");
	float res = cheat::inst->env->GetFloatField(object, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

float c_timer::getTimerSpeed(c_context* ctx)
{
	if (!ctx->mc)
		return 0.f;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_74278_d", "F");
	float res = cheat::inst->env->GetFloatField(object, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

void c_timer::setTimerSpeed(c_context* ctx, float value)
{
	if (!ctx->mc)
		return;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_74278_d", "F");
	cheat::inst->env->SetFloatField(object, fld, value);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);
}