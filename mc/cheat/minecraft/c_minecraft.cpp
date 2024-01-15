#include "c_minecraft.h"

c_minecraft* mc = new c_minecraft();

bool c_minecraft::getLaunchWrapper()
{
	jclass launchwrapper_cls = cheat::inst->env->FindClass("net/minecraft/launchwrapper/LaunchClassLoader");
	if (!launchwrapper_cls)
		return false;

	jclass launch_cls = cheat::inst->env->FindClass("net/minecraft/launchwrapper/Launch");
	if (!launch_cls)
		return false;

	jfieldID classloader_fld = cheat::inst->env->GetStaticFieldID(launch_cls, "classLoader", "Lnet/minecraft/launchwrapper/LaunchClassLoader;");
	if (!classloader_fld)
		return false;

	cheat::inst->findclass_mtd = cheat::inst->env->GetMethodID(launchwrapper_cls, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");
	cheat::inst->classloader_obj = cheat::inst->env->NewGlobalRef(cheat::inst->env->GetStaticObjectField(launch_cls, classloader_fld));

	cheat::inst->env->DeleteLocalRef(launchwrapper_cls);
	cheat::inst->env->DeleteLocalRef(launch_cls);

	if (cheat::inst->findclass_mtd != NULL && cheat::inst->classloader_obj != NULL)
		return true;
	return false;
}

jclass c_minecraft::FFindClass(const char* name)
{
	jstring jname = cheat::inst->env->NewStringUTF(name);
	return reinterpret_cast<jclass>(cheat::inst->env->CallObjectMethod(cheat::inst->classloader_obj, cheat::inst->findclass_mtd, jname));
}

jobject c_minecraft::getMinecraft(c_context* ctx)
{
	jclass cls = mc->FFindClass("net/minecraft/client/Minecraft");
	jmethodID mtd = cheat::inst->env->GetStaticMethodID(cls, "func_71410_x", "()Lnet/minecraft/client/Minecraft;");
	jobject res = cheat::inst->env->CallStaticObjectMethod(cls, mtd);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

jobject c_minecraft::getPlayer(c_context* ctx)
{
	if (!ctx->mc)
		return 0;

	jclass cls = cheat::inst->env->GetObjectClass(ctx->mc);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_71439_g", "Lnet/minecraft/client/entity/EntityPlayerSP;");
	jobject res = cheat::inst->env->GetObjectField(ctx->mc, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

jobject c_minecraft::getWorld(c_context* ctx)
{
	if (!ctx->mc)
		return 0;

	jclass cls = cheat::inst->env->GetObjectClass(ctx->mc);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_71441_e", "Lnet/minecraft/client/multiplayer/WorldClient;");
	jobject res = cheat::inst->env->GetObjectField(ctx->mc, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

jobject c_minecraft::getRenderManager(c_context* ctx)
{
	if (!ctx->mc)
		return 0;

	jclass cls = cheat::inst->env->GetObjectClass(ctx->mc);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_175616_W", "Lnet/minecraft/client/renderer/entity/RenderManager;");
	jobject res = cheat::inst->env->GetObjectField(ctx->mc, fld);
	
	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

jobject c_minecraft::getTimer(c_context* ctx)
{
	if (!ctx->mc)
		return 0;

	jclass cls = cheat::inst->env->GetObjectClass(ctx->mc);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_71428_T", "Lnet/minecraft/util/Timer;");
	jobject ret = cheat::inst->env->GetObjectField(ctx->mc, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return ret;
}

jobject c_minecraft::getGameSettings(c_context* ctx)
{
	if (!ctx->mc)
		return 0;

	jclass cls = cheat::inst->env->GetObjectClass(ctx->mc);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_71474_y", "Lnet/minecraft/client/settings/GameSettings;");
	jobject ret = cheat::inst->env->GetObjectField(ctx->mc, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return ret;
}

