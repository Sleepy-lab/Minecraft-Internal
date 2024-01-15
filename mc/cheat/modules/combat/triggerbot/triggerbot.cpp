#include "triggerbot.h"
#include "../aim/aim.h"

bool triggerbot::toggle = false;
bool triggerbot::awaiting_bind = false;
int triggerbot::bind = 0;
const char* triggerbot::bind_text = "[NONE]##1";

float triggerbot::threshold = 1.5;
bool triggerbot::rmb = false;


double PI_ = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;

bool clicked = false;

void triggerbot::use(c_context* ctx)
{
	if (!triggerbot::toggle)
		return;

	if (!ctx->player->getObject() || !ctx->rendermanager->getObject() || !ctx->world->getObject() || !ctx->timer->getObject() || !ctx->gamesettings->getObject())
		return;

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

		std::stringstream ss(aim::whitelist);
		std::string to;

		std::vector<std::string> v;
		if (aim::whitelist != NULL)
		{
			while (std::getline(ss, to, '\n')) {
				v.push_back(to);
			}
		}

		if (std::find(v.begin(), v.end(), player->getName(ctx)) != v.end())
			continue;

		if (!ctx->player->canEntityBeSeen(ctx, player->getObject()))
			continue;

		local_yaw = ctx->player->getRotationYaw(ctx);
		local_pitch = ctx->player->getRotationPitch(ctx);
		local_prevyaw = ctx->player->getPreviousRotationYaw(ctx);
		local_prevpitch = ctx->player->getPreviousRotationPitch(ctx);
		local_pos = ctx->player->getPositionVector(ctx);
		player_pos = player->getPositionVector(ctx);

		double dist_x = player_pos[0] - local_pos[0];
		double dist_z = player_pos[2] - local_pos[2];

		float diff = (float)atan2((float)dist_z, (float)dist_x) * 180.00f / PI_ - 90.00f;
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

		POINT clicker_mouse1;
		GetCursorPos(&clicker_mouse1);
		HWND clicker_window = WindowFromPoint(clicker_mouse1);

		if (ScreenToClient(clicker_window, &clicker_mouse1))
		{
			if (clicker_mouse1.y > 20)
			{
				float yaw_diff = math.wrapTo180(fmodf(((float)atan2((float)dist_z, (float)dist_x) * 180.0f / PI_ - 90.0f) - local_yaw, 360.0f));
				float pitch_diff = math.wrapTo180(-(ctx->player->getRotationPitch(ctx) - math.getAngles(ctx->player->getPositionVector(ctx), target->getPositionVector(ctx)).second));
				if ((yaw_diff <= threshold && yaw_diff >= -threshold) && (pitch_diff <= threshold && pitch_diff >= -threshold))
				{
					if (!triggerbot::rmb)
					{
						if (!clicked)
							PostMessage(clicker_window, WM_LBUTTONDOWN, 10, MAKELPARAM(clicker_mouse1.x, clicker_mouse1.y));
						clicked = true;
					}
					else
					{
						if (!clicked)
							PostMessage(clicker_window, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(clicker_mouse1.x, clicker_mouse1.y));
						clicked = true;
					}
				}
				else
				{
					if (!triggerbot::rmb)
					{
						PostMessage(clicker_window, WM_LBUTTONUP, 11, MAKELPARAM(clicker_mouse1.x, clicker_mouse1.y));
						clicked = false;
					}
					else
					{
						PostMessage(clicker_window, WM_RBUTTONUP, MK_RBUTTON, MAKELPARAM(clicker_mouse1.x, clicker_mouse1.y));
						clicked = false;
					}
				}
			}
		}
	}
}