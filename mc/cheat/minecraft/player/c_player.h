#pragma once

#include "../../cheat.h"

class c_context;
class c_player
{
private:
	jobject object;
public:
	c_player(jobject obj);
	~c_player();

	const jobject getObject();
	
	float getRotationYaw(c_context* ctx);
	void setRotationYaw(c_context* ctx, jfloat value);
	float getRotationPitch(c_context* ctx);
	void setRotationPitch(c_context* ctx, jfloat value);
	float getPreviousRotationYaw(c_context* ctx);
	void setPreviousRotationYaw(c_context* ctx, jfloat value);
	float getPreviousRotationPitch(c_context* ctx);
	void setPreviousRotationPitch(c_context* ctx, jfloat value);

	int getEntityId(c_context* ctx);

	jobject getBoundingBox(c_context* ctx);
	std::vector<double> getBoundingBoxVertices(c_context* ctx);
	void setBoundingBoxVertices(c_context* ctx, std::vector<double> vertices);

	double getPositionX(c_context* ctx);
	double getPositionY(c_context* ctx);
	double getPositionZ(c_context* ctx);
	std::vector<double> getPositionVector(c_context* ctx);

	double getPreviousPositionX(c_context* ctx);
	double getPreviousPositionY(c_context* ctx);
	double getPreviousPositionZ(c_context* ctx);
	std::vector<double> getPreviousPositionVector(c_context* ctx);

	double getLastTickPositionX(c_context* ctx);
	double getLastTickPositionY(c_context* ctx);
	double getLastTickPositionZ(c_context* ctx);
	std::vector<double> getLastTickPositionVector(c_context* ctx);

	float getHealth(c_context* ctx);
	bool isEntityAlive(c_context* ctx);

	bool isInvisible(c_context* ctx);

	double getDistanceToEntity(c_context* ctx, c_player* entity);

	std::string getName(c_context* ctx);

	void setSprinting(c_context* ctx, jboolean value);

	bool canEntityBeSeen(c_context* ctx, jobject entity);

	double getMotionX(c_context* ctx);
	double getMotionY(c_context* ctx);
	double getMotionZ(c_context* ctx);
	std::vector<double> getMotionVector(c_context* ctx);

	void setMotionX(c_context* ctx, jdouble value);
	void setMotionY(c_context* ctx, jdouble value);
	void setMotionZ(c_context* ctx, jdouble value);
	void setMotionVector(c_context* ctx, std::vector<jdouble> vector);
};

