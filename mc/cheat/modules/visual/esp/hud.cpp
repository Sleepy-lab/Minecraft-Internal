#include "hud.h"
#include "esp.h"
#include "../../combat/triggerbot/triggerbot.h"
#include "../../../minecraft/render/activerenderinfo.h"

double hud::health = 0;
std::string hud::name = "";

double PI__ = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;

void hud::use(c_context* ctx)
{
	if (!esp::draw_hud)
		return;

	if (!ctx->player->getObject() || !ctx->rendermanager->getObject() || !ctx->world->getObject() || !ctx->timer->getObject() || !ctx->gamesettings->getObject())
		return;

	double temp_health;
	std::string temp_name;

	c_player* target = new c_player(0);
	float closest_yaw = 500.0f;
	std::vector<double> target_pos;

	float local_yaw;
	float local_pitch;
	float local_prevyaw;
	float local_prevpitch;
	std::vector<double> local_pos;
	std::vector<double> player_pos;

	std::vector<jobject> entity_list = ctx->world->getPlayers(ctx);
	for (jobject object : entity_list)
	{
		if (!object)
			continue;

		c_player* player = new c_player(object);

		if (player->getEntityId(ctx) == ctx->player->getEntityId(ctx) || !player->getObject())
			continue;

		if (!player->isEntityAlive(ctx))
			continue;

		if (player->isInvisible(ctx))
			continue;

		local_yaw = ctx->player->getRotationYaw(ctx);
		local_pitch = ctx->player->getRotationPitch(ctx);
		local_prevyaw = ctx->player->getPreviousRotationYaw(ctx);
		local_prevpitch = ctx->player->getPreviousRotationPitch(ctx);
		local_pos = ctx->player->getPositionVector(ctx);
		player_pos = player->getPositionVector(ctx);

		double dist_x = player_pos[0] - local_pos[0];
		double dist_z = player_pos[2] - local_pos[2];

		float diff = (float)atan2((float)dist_z, (float)dist_x) * 180.00f / PI__ - 90.00f;
		diff = fmodf(diff - local_yaw, 360.0f);
		if (diff >= 180.0f)
			diff -= 360.0f;
		if (diff < -180.0f)
			diff += 360.0f;

		if (abs(diff) <= 10 && abs(diff) < abs(closest_yaw))
		{
			target = player;
			target_pos = player_pos;
			closest_yaw = diff;
		}
	}

	if (closest_yaw != 500.0f && target->getObject())
	{
		double dist_x;
		double dist_z;

		dist_x = target_pos[0] - local_pos[0];
		dist_z = target_pos[2] - local_pos[2];

		float yaw_diff = math.wrapTo180(fmodf(((float)atan2((float)dist_z, (float)dist_x) * 180.0f / PI__ - 90.0f) - local_yaw, 360.0f));
		float pitch_diff = math.wrapTo180(-(ctx->player->getRotationPitch(ctx) - math.getAngles(ctx->player->getPositionVector(ctx), target->getPositionVector(ctx)).second));
		if ((yaw_diff <= triggerbot::threshold && yaw_diff >= -triggerbot::threshold) && (pitch_diff <= triggerbot::threshold && pitch_diff >= -triggerbot::threshold))
		{
			temp_health = target->getHealth(ctx);
			temp_name = target->getName(ctx);
		}
		else
		{
			temp_health = 0;
			temp_name = "";
		}
	}
	else
	{
		temp_health = 0;
		temp_name = "";
	}
	health = temp_health;
	name = temp_name;
}