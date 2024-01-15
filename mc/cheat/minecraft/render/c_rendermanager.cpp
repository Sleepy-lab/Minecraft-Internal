#include "c_rendermanager.h"
#include "../c_minecraft.h"
#include "../c_context.h"

c_rendermanager::c_rendermanager(jobject obj)
{
	object = obj;
}

c_rendermanager::~c_rendermanager()
{
	cheat::inst->env->DeleteLocalRef(object);
}

const jobject c_rendermanager::getObject()
{
	return object;
}

double c_rendermanager::getRenderPositionX(c_context* ctx)
{
	if (!ctx->mc)
		return 0.0;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_78725_b", "D");
	double res = cheat::inst->env->GetDoubleField(object, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

double c_rendermanager::getRenderPositionY(c_context* ctx)
{
	if (!ctx->mc)
		return 0.0;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_78726_c", "D");
	double res = cheat::inst->env->GetDoubleField(object, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

double c_rendermanager::getRenderPositionZ(c_context* ctx)
{
	if (!ctx->mc)
		return 0.0;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_78723_d", "D");
	double res = cheat::inst->env->GetDoubleField(object, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

std::vector<double> c_rendermanager::getRenderPositionVector(c_context* ctx)
{
	if (!ctx->mc)
		return {};

	std::vector<double> vec;
	vec.push_back(getRenderPositionX(ctx));
	vec.push_back(getRenderPositionY(ctx));
	vec.push_back(getRenderPositionZ(ctx));
	return vec;
}