#include "c_player.h"
#include "../c_minecraft.h"

c_player::c_player(jobject obj)
{
	object = obj;
}

c_player::~c_player()
{
	cheat::inst->env->DeleteLocalRef(object);
}

const jobject c_player::getObject()
{
	return object;
}

float c_player::getRotationYaw(c_context* ctx)
{
	if (!ctx->mc)
		return 0.f;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_70177_z", "F");
	float res = cheat::inst->env->GetFloatField(object, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

void c_player::setRotationYaw(c_context* ctx, jfloat value)
{
	if (!ctx->mc)
		return;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_70177_z", "F");
	cheat::inst->env->SetFloatField(object, fld, value);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);
}

float c_player::getRotationPitch(c_context* ctx)
{
	if (!ctx->mc)
		return 0.f;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_70125_A", "F");
	float res = cheat::inst->env->GetFloatField(object, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

void c_player::setRotationPitch(c_context* ctx, jfloat value)
{
	if (!ctx->mc)
		return;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_70125_A", "F");
	cheat::inst->env->SetFloatField(object, fld, value);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);
}

float c_player::getPreviousRotationYaw(c_context* ctx)
{
	if (!ctx->mc)
		return 0.f;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_70126_B", "F");
	float res = cheat::inst->env->GetFloatField(object, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

void c_player::setPreviousRotationYaw(c_context* ctx, jfloat value)
{
	if (!ctx->mc)
		return;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_70126_B", "F");
	cheat::inst->env->SetFloatField(object, fld, value);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);
}

float c_player::getPreviousRotationPitch(c_context* ctx)
{
	if (!ctx->mc)
		return 0.f;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_70127_C", "F");
	float res = cheat::inst->env->GetFloatField(object, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

void c_player::setPreviousRotationPitch(c_context* ctx, jfloat value)
{
	if (!ctx->mc)
		return;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_70127_C", "F");
	cheat::inst->env->SetFloatField(object, fld, value);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);
}

int c_player::getEntityId(c_context* ctx)
{
	if (!ctx->mc)
		return 0;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jmethodID mtd = cheat::inst->env->GetMethodID(cls, "func_145782_y", "()I");
	int res = cheat::inst->env->CallIntMethod(object, mtd);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

jobject c_player::getBoundingBox(c_context* ctx)
{
	if (!ctx->mc)
		return 0;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_70121_D", "Lnet/minecraft/util/AxisAlignedBB;");
	jobject res = cheat::inst->env->GetObjectField(object, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

std::vector<double> c_player::getBoundingBoxVertices(c_context* ctx)
{
	if (!ctx->mc)
		return {};

	jobject boundingbox = getBoundingBox(ctx);
	jclass cls = cheat::inst->env->GetObjectClass(boundingbox);
	jfieldID minX_fld = cheat::inst->env->GetFieldID(cls, "field_72340_a", "D");
	jfieldID minY_fld = cheat::inst->env->GetFieldID(cls, "field_72338_b", "D");
	jfieldID minZ_fld = cheat::inst->env->GetFieldID(cls, "field_72339_c", "D");
	jfieldID maxX_fld = cheat::inst->env->GetFieldID(cls, "field_72336_d", "D");
	jfieldID maxY_fld = cheat::inst->env->GetFieldID(cls, "field_72337_e", "D");
	jfieldID maxZ_fld = cheat::inst->env->GetFieldID(cls, "field_72334_f", "D");
	double minX = cheat::inst->env->GetDoubleField(boundingbox, minX_fld);
	double minY = cheat::inst->env->GetDoubleField(boundingbox, minY_fld);
	double minZ = cheat::inst->env->GetDoubleField(boundingbox, minZ_fld);
	double maxX = cheat::inst->env->GetDoubleField(boundingbox, maxX_fld);
	double maxY = cheat::inst->env->GetDoubleField(boundingbox, maxY_fld);
	double maxZ = cheat::inst->env->GetDoubleField(boundingbox, maxZ_fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	if (boundingbox)
		cheat::inst->env->DeleteLocalRef(boundingbox);

	return { minX, minY, minZ, maxX, maxY, maxZ };
}

void c_player::setBoundingBoxVertices(c_context* ctx, std::vector<double> vertices)
{
	if (!ctx->mc)
		return;

	jobject boundingbox = getBoundingBox(ctx);
	jclass cls = cheat::inst->env->GetObjectClass(boundingbox);
	jfieldID minX_fld = cheat::inst->env->GetFieldID(cls, "field_72340_a", "D");
	jfieldID minY_fld = cheat::inst->env->GetFieldID(cls, "field_72338_b", "D");
	jfieldID minZ_fld = cheat::inst->env->GetFieldID(cls, "field_72339_c", "D");
	jfieldID maxX_fld = cheat::inst->env->GetFieldID(cls, "field_72336_d", "D");
	jfieldID maxY_fld = cheat::inst->env->GetFieldID(cls, "field_72337_e", "D");
	jfieldID maxZ_fld = cheat::inst->env->GetFieldID(cls, "field_72334_f", "D");
	cheat::inst->env->SetDoubleField(boundingbox, minX_fld, vertices[0]);
	cheat::inst->env->SetDoubleField(boundingbox, minY_fld, vertices[1]);
	cheat::inst->env->SetDoubleField(boundingbox, minZ_fld, vertices[2]);
	cheat::inst->env->SetDoubleField(boundingbox, maxX_fld, vertices[3]);
	cheat::inst->env->SetDoubleField(boundingbox, maxY_fld, vertices[4]);
	cheat::inst->env->SetDoubleField(boundingbox, maxZ_fld, vertices[5]);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	if (boundingbox)
		cheat::inst->env->DeleteLocalRef(boundingbox);
}

double c_player::getPositionX(c_context* ctx)
{
	if (!ctx->mc)
		return 0.0;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_70165_t", "D");
	double res = cheat::inst->env->GetDoubleField(object, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

double c_player::getPositionY(c_context* ctx)
{
	if (!ctx->mc)
		return 0.0;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_70163_u", "D");
	double res = cheat::inst->env->GetDoubleField(object, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

double c_player::getPositionZ(c_context* ctx)
{
	if (!ctx->mc)
		return 0.0;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_70161_v", "D");
	double res = cheat::inst->env->GetDoubleField(object, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

std::vector<double> c_player::getPositionVector(c_context* ctx)
{
	if (!ctx->mc)
		return {};

	std::vector<double> pos;
	pos.push_back(getPositionX(ctx));
	pos.push_back(getPositionY(ctx));
	pos.push_back(getPositionZ(ctx));
	return pos;
}

double c_player::getPreviousPositionX(c_context* ctx)
{
	if (!ctx->mc)
		return 0.0;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_70169_q", "D");
	double res = cheat::inst->env->GetDoubleField(object, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

double c_player::getPreviousPositionY(c_context* ctx)
{
	if (!ctx->mc)
		return 0.0;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_70167_r", "D");
	double res = cheat::inst->env->GetDoubleField(object, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

double c_player::getPreviousPositionZ(c_context* ctx)
{
	if (!ctx->mc)
		return 0.0;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_70166_s", "D");
	double res = cheat::inst->env->GetDoubleField(object, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

std::vector<double> c_player::getPreviousPositionVector(c_context* ctx)
{
	if (!ctx->mc)
		return {};

	std::vector<double> pos;
	pos.push_back(getPreviousPositionX(ctx));
	pos.push_back(getPreviousPositionY(ctx));
	pos.push_back(getPreviousPositionZ(ctx));
	return pos;
}

double c_player::getLastTickPositionX(c_context* ctx)
{
	if (!ctx->mc)
		return 0.0;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_70142_S", "D");
	double res = cheat::inst->env->GetDoubleField(object, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

double c_player::getLastTickPositionY(c_context* ctx)
{
	if (!ctx->mc)
		return 0.0;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_70137_T", "D");
	double res = cheat::inst->env->GetDoubleField(object, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

double c_player::getLastTickPositionZ(c_context* ctx)
{
	if (!ctx->mc)
		return 0.0;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_70136_U", "D");
	double res = cheat::inst->env->GetDoubleField(object, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

std::vector<double> c_player::getLastTickPositionVector(c_context* ctx)
{
	if (!ctx->mc)
		return {};

	std::vector<double> pos;
	pos.push_back(getLastTickPositionX(ctx));
	pos.push_back(getLastTickPositionY(ctx));
	pos.push_back(getLastTickPositionZ(ctx));
	return pos;
}

float c_player::getHealth(c_context* ctx)
{
	if (!ctx->mc)
		return 0.f;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jmethodID mtd = cheat::inst->env->GetMethodID(cls, "func_110143_aJ", "()F");
	float res = cheat::inst->env->CallFloatMethod(object, mtd);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

bool c_player::isEntityAlive(c_context* ctx)
{
	if (!ctx->mc)
		return false;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jmethodID mtd = cheat::inst->env->GetMethodID(cls, "func_70089_S", "()Z");
	bool res = cheat::inst->env->CallBooleanMethod(object, mtd);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

bool c_player::isInvisible(c_context* ctx)
{
	if (!ctx->mc)
		return false;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jmethodID mtd = cheat::inst->env->GetMethodID(cls, "func_82150_aj", "()Z");
	bool res = cheat::inst->env->CallBooleanMethod(object, mtd);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

double c_player::getDistanceToEntity(c_context* ctx, c_player* entity)
{
	if (!ctx->mc)
		return 0.0;

	std::vector<double> pos = getPositionVector(ctx);
	std::vector<double> entity_pos = entity->getPositionVector(ctx);

	return math.distance(pos[0], pos[1], pos[2], entity_pos[0], entity_pos[1], entity_pos[2]);
}

std::string c_player::getName(c_context* ctx)
{
	if (!ctx->mc)
		return "";

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jmethodID mtd = cheat::inst->env->GetMethodID(cls, "func_70005_c_", "()Ljava/lang/String;");
	jstring jstr = (jstring)cheat::inst->env->CallObjectMethod(object, mtd);
	if (!jstr)
		return "";

	jclass string_cls = cheat::inst->env->GetObjectClass(jstr);
	jmethodID getbytes_mtd = cheat::inst->env->GetMethodID(string_cls, "getBytes", "(Ljava/lang/String;)[B");
	jbyteArray string_bytes = (jbyteArray)cheat::inst->env->CallObjectMethod(jstr, getbytes_mtd, cheat::inst->env->NewStringUTF("UTF-8"));
	size_t length = (size_t)cheat::inst->env->GetArrayLength(string_bytes);
	jbyte* pbytes = cheat::inst->env->GetByteArrayElements(string_bytes, NULL);
	std::string ret = std::string((char*)pbytes, length);

	cheat::inst->env->ReleaseByteArrayElements(string_bytes, pbytes, JNI_ABORT);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	if (string_cls)
		cheat::inst->env->DeleteLocalRef(string_cls);

	auto getLastIndex = [](char* s, char c)
	{
		std::vector<int> indexes;
		int length;
		int i;

		length = (int)strlen(s);

		for (i = (length - 1); i >= 0; i--)
		{
			if (s[i] == c)
				indexes.push_back(i);
		}

		return indexes;
	};
	for (auto index : getLastIndex(ret.data(), '\u00A7'))
		ret.erase(index - 1, 3);

	return ret;
}

void c_player::setSprinting(c_context* ctx, jboolean value)
{
	if (!ctx->mc)
		return;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jmethodID set_sprint = cheat::inst->env->GetMethodID(cls, "func_70031_b", "(Z)V");
	cheat::inst->env->CallVoidMethod(object, set_sprint, value);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);
}

bool c_player::canEntityBeSeen(c_context* ctx, jobject entity)
{
	if (!ctx->mc)
		return false;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jmethodID mtd = cheat::inst->env->GetMethodID(cls, "func_70685_l", "(Lnet/minecraft/entity/Entity;)Z");
	bool res = cheat::inst->env->CallBooleanMethod(object, mtd, entity);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

double c_player::getMotionX(c_context* ctx)
{
	if (!ctx->mc)
		return 0.0;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_70159_w", "D");
	double res = cheat::inst->env->GetDoubleField(object, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

double c_player::getMotionY(c_context* ctx)
{
	if (!ctx->mc)
		return 0.0;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_70181_x", "D");
	double res = cheat::inst->env->GetDoubleField(object, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

double c_player::getMotionZ(c_context* ctx)
{
	if (!ctx->mc)
		return 0.0;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_70179_y", "D");
	double res = cheat::inst->env->GetDoubleField(object, fld);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);

	return res;
}

std::vector<double> c_player::getMotionVector(c_context* ctx)
{
	return { getMotionX(ctx), getMotionY(ctx), getMotionZ(ctx) };
}

void c_player::setMotionX(c_context* ctx, jdouble value)
{
	if (!ctx->mc)
		return;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_70159_w", "D");
	cheat::inst->env->SetDoubleField(object, fld, value);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);
}

void c_player::setMotionY(c_context* ctx, jdouble value)
{
	if (!ctx->mc)
		return;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_70181_x", "D");
	cheat::inst->env->SetDoubleField(object, fld, value);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);
}

void c_player::setMotionZ(c_context* ctx, jdouble value)
{
	if (!ctx->mc)
		return;

	jclass cls = cheat::inst->env->GetObjectClass(object);
	jfieldID fld = cheat::inst->env->GetFieldID(cls, "field_70179_y", "D");
	cheat::inst->env->SetDoubleField(object, fld, value);

	if (cls)
		cheat::inst->env->DeleteLocalRef(cls);
}

void c_player::setMotionVector(c_context* ctx, std::vector<jdouble> vector)
{
	this->setMotionX(ctx, vector[0]);
	this->setMotionY(ctx, vector[1]);
	this->setMotionZ(ctx, vector[2]);
}
