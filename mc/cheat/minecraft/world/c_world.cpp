#include "c_world.h"
#include "../c_minecraft.h"

c_world::c_world(jobject obj)
{
	object = obj;
}

c_world::~c_world()
{
	cheat::inst->env->DeleteLocalRef(object);
}

const jobject c_world::getObject()
{
	return object;
}

std::vector<jobject> c_world::getPlayers(c_context* ctx)
{
	if (!ctx->mc)
		return {};

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID player_entities = cheat::inst->env->GetFieldID(cls, "field_73010_i", "Ljava/util/List;");
	jclass list_cls = mc->FFindClass("java.util.List");
	jmethodID to_array_mtd = cheat::inst->env->GetMethodID(list_cls, "toArray", "()[Ljava/lang/Object;");
	jobject obj_player_entities = cheat::inst->env->GetObjectField(object, player_entities);
	jobjectArray array_player_list = reinterpret_cast<jobjectArray>(cheat::inst->env->CallObjectMethod(obj_player_entities, to_array_mtd));
	size_t len = cheat::inst->env->GetArrayLength(array_player_list);
	
	std::vector<jobject> res;
	for (int i = 0; i < len; ++i)
		res.push_back(cheat::inst->env->GetObjectArrayElement(array_player_list, i));

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	if (list_cls)
		cheat::inst->env->DeleteLocalRef(list_cls);

	if (obj_player_entities)
		cheat::inst->env->DeleteLocalRef(obj_player_entities);

	return res;
}