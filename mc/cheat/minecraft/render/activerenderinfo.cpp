#include "activerenderinfo.h"
#include "../c_minecraft.h"

GLint activerenderinfo::viewport[16];
GLfloat activerenderinfo::modelview[16];
GLfloat activerenderinfo::projection[16];

void activerenderinfo::fetchViewport(c_context* ctx)
{
	if (!ctx->mc)
		return;

	jclass cls = mc->FFindClass("net.minecraft.client.renderer.ActiveRenderInfo");
	jfieldID fld = cheat::inst->env->GetStaticFieldID(cls, "field_178814_a", "Ljava/nio/IntBuffer;");
	jclass ib_cls = mc->FFindClass("java.nio.IntBuffer");
	jobject obj = cheat::inst->env->GetStaticObjectField(cls, fld);
	jmethodID get = cheat::inst->env->GetMethodID(ib_cls, "get", "(I)I");

	for (int i = 0; i < 16; i++)
		viewport[i] = cheat::inst->env->CallIntMethod(obj, get, i);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	if (ib_cls)
		cheat::inst->env->DeleteLocalRef(ib_cls);

	if (obj)
		cheat::inst->env->DeleteLocalRef(obj);
}

void activerenderinfo::fetchModelviewMatrix(c_context* ctx)
{
	if (!ctx->mc)
		return;

	jclass cls = mc->FFindClass("net.minecraft.client.renderer.ActiveRenderInfo");
	jfieldID fld = cheat::inst->env->GetStaticFieldID(cls, "field_178812_b", "Ljava/nio/FloatBuffer;");
	jclass fb_cls = mc->FFindClass("java.nio.FloatBuffer");
	jobject obj = cheat::inst->env->GetStaticObjectField(cls, fld);
	jmethodID get = cheat::inst->env->GetMethodID(fb_cls, "get", "(I)F");

	for (int i = 0; i < 16; i++)
		modelview[i] = cheat::inst->env->CallFloatMethod(obj, get, i);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	if (fb_cls)
		cheat::inst->env->DeleteLocalRef(fb_cls);

	if (obj)
		cheat::inst->env->DeleteLocalRef(obj);
}

void activerenderinfo::fetchProjectionMatrix(c_context* ctx)
{
	if (!ctx->mc)
		return;

	jclass cls = mc->FFindClass("net.minecraft.client.renderer.ActiveRenderInfo");
	jfieldID fld = cheat::inst->env->GetStaticFieldID(cls, "field_178813_c", "Ljava/nio/FloatBuffer;");
	jclass fb_cls = mc->FFindClass("java.nio.FloatBuffer");
	jobject obj = cheat::inst->env->GetStaticObjectField(cls, fld);
	jmethodID get = cheat::inst->env->GetMethodID(fb_cls, "get", "(I)F");

	for (int i = 0; i < 16; i++)
		projection[i] = cheat::inst->env->CallFloatMethod(obj, get, i);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	if (fb_cls)
		cheat::inst->env->DeleteLocalRef(fb_cls);

	if (obj)
		cheat::inst->env->DeleteLocalRef(obj);
}