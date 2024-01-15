#include "aim.h"

bool aim::toggle = false;
bool aim::awaiting_bind = false;
int aim::bind = 0;
const char* aim::bind_text = "[NONE]##1";

float aim::speed = 0.5f;
float aim::fov = 60.0f;
float aim::distance = 5.0f;
bool aim::low_health = false;

char aim::whitelist[256] = "";

bool aim::require_lmb = false;
bool aim::require_rmb = false;

bool aim::visibility_check = true;
bool aim::smart = false;
bool aim::predict = false;
float aim::predict_strength = 30;

double PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;

void aim::use(c_context* ctx)
{
	if (!aim::toggle)
		return;

	if (!ctx->player->getObject() || !ctx->rendermanager->getObject() || !ctx->world->getObject() || !ctx->timer->getObject() || !ctx->gamesettings->getObject())
		return;

	if (aim::require_lmb && !GetAsyncKeyState(VK_LBUTTON))
		return;

	if (aim::require_rmb && !GetAsyncKeyState(VK_RBUTTON))
		return;

	float spd = aim::speed / 10;
	c_player* target = new c_player(0);
	float closest_yaw = 500.0f;
	float lowest_health = 500.f;
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

		std::stringstream ss(whitelist);
		std::string to;

		std::vector<std::string> v;
		if (whitelist != NULL)
		{
			while (std::getline(ss, to, '\n')) {
				v.push_back(to);
			}
		}

		if (std::find(v.begin(),v.end(), player->getName(ctx)) != v.end())
			continue;

		if (aim::visibility_check && !ctx->player->canEntityBeSeen(ctx, player->getObject()))
			continue;

		local_yaw = ctx->player->getRotationYaw(ctx);
		local_pitch = ctx->player->getRotationPitch(ctx);
		local_prevyaw = ctx->player->getPreviousRotationYaw(ctx);
		local_prevpitch = ctx->player->getPreviousRotationPitch(ctx);
		local_pos = ctx->player->getPositionVector(ctx);
		player_pos = player->getPositionVector(ctx);

		double dist = sqrt(pow(player_pos[0] - local_pos[0], 2) + pow(player_pos[1] - local_pos[1], 2) + pow(player_pos[2] - local_pos[2], 2));
		if (dist >= aim::distance)
			continue;

		double dist_x = player_pos[0] - local_pos[0];
		double dist_z = player_pos[2] - local_pos[2];

		float diff = (float)atan2((float)dist_z, (float)dist_x) * 180.00f / PI - 90.00f;
		diff = fmodf(diff - local_yaw, 360.0f);
		if (diff >= 180.0f)
			diff -= 360.0f;
		if (diff < -180.0f)
			diff += 360.0f;

		if (!aim::low_health)
		{
			if (abs(diff) <= aim::fov && abs(diff) < abs(closest_yaw))
			{
				target = player;
				target_pos = player_pos;
				closest_yaw = diff;
			}
		}
		else
		{
			double health = player->getHealth(ctx);
			if (abs(diff) <= aim::fov && health < lowest_health)
			{
				lowest_health = health;
				target = player;
				target_pos = player_pos;
			}
		}
	}

	if (((aim::low_health && lowest_health != 500.f) || (!aim::low_health && closest_yaw != 500.0f)) && target->getObject())
	{
		double dist_x;
		double dist_z;

		if (aim::smart)
		{
			std::vector<std::vector<double>> corners = {
				{ target_pos[0] - 0.30f, target_pos[1], target_pos[2] + 0.30f },
				{ target_pos[0] - 0.30f, target_pos[1], target_pos[2] - 0.30f },
				{ target_pos[0] + 0.30f, target_pos[1], target_pos[2] - 0.30f },
				{ target_pos[0] + 0.30f, target_pos[1], target_pos[2] + 0.30f }
			};

			double dist = sqrt(pow(target_pos[0] - local_pos[0], 2) + pow(target_pos[1] - local_pos[1], 2) + pow(target_pos[2] - local_pos[2], 2));

			std::vector<double> corner_dists = {
				sqrt(pow(corners[0][0] - local_pos[0], 2) + pow(corners[0][1] - local_pos[1], 2) + pow(corners[0][2] - local_pos[2], 2)),
				sqrt(pow(corners[1][0] - local_pos[0], 2) + pow(corners[1][1] - local_pos[1], 2) + pow(corners[1][2] - local_pos[2], 2)),
				sqrt(pow(corners[2][0] - local_pos[0], 2) + pow(corners[2][1] - local_pos[1], 2) + pow(corners[2][2] - local_pos[2], 2)),
				sqrt(pow(corners[3][0] - local_pos[0], 2) + pow(corners[3][1] - local_pos[1], 2) + pow(corners[3][2] - local_pos[2], 2))
			};

			std::vector<double> closest_corners = corner_dists;
			for (size_t i = 0; i < closest_corners.size(); i++)
			{
				for (size_t j = i + 1; j < closest_corners.size(); j++)
				{
					if (closest_corners[i] > closest_corners[j])
					{
						double x = closest_corners[i];
						closest_corners[i] = closest_corners[j];
						closest_corners[j] = x;
					}
				}
			}

			std::vector<double> closest_corner1;
			std::vector<double> closest_corner2;

			for (size_t x = 0; x < 2; ++x)
			{
				if (closest_corners[x] == corner_dists[0])
					if (x == 0)
						closest_corner1 = corners[0];
					else if (x == 1)
						closest_corner2 = corners[0];

				if (closest_corners[x] == corner_dists[1])
					if (x == 0)
						closest_corner1 = corners[1];
					else if (x == 1)
						closest_corner2 = corners[1];

				if (closest_corners[x] == corner_dists[2])
					if (x == 0)
						closest_corner1 = corners[2];
					else if (x == 1)
						closest_corner2 = corners[2];

				if (closest_corners[x] == corner_dists[3])
					if (x == 0)
						closest_corner1 = corners[3];
					else if (x == 1)
						closest_corner2 = corners[3];
			}

			std::vector<double> closest_point = closest_corner1;
			if (closest_corner1[0] == closest_corner2[0])
			{
				closest_point[2] = local_pos[2];
				if (!math.inRange(closest_point[2], closest_corner1[2], closest_corner2[2]))
					closest_point = closest_corner1;
			}

			else
			{
				if (closest_corner2[2] == closest_corner2[2])
				{
					closest_point[0] = local_pos[0];
					if (!math.inRange(closest_point[0], closest_corner1[0], closest_corner2[0]))
						closest_point = closest_corner1;
				}
			}

			dist_x = closest_point[0] - local_pos[0];
			dist_z = closest_point[2] - local_pos[2];
		}
		else
		{
			dist_x = target_pos[0] - local_pos[0];
			dist_z = target_pos[2] - local_pos[2];
		}

		float yaw_diff = math.wrapTo180(fmodf(((float)atan2((float)dist_z, (float)dist_x) * 180.0f / PI - 90.0f) - local_yaw, 360.0f));
		if (abs(yaw_diff) <= 0.1)
			return;

		float new_yaw = local_yaw + (yaw_diff / (40 / aim::speed));
		// std::cout << std::to_string(yaw_diff) << std::endl;

		if (aim::predict)
		{
			std::vector<double> p = target->getPositionVector(ctx);
			std::vector<double> pp = target->getPreviousPositionVector(ctx);

			double x = p[0] - pp[0];
			double y = p[1] - pp[1];
			double z = p[2] - pp[2];

			if (x > 0.0)
				x = 0.1;
			else if (x < 0.0)
				x = -0.1;

			if (z > 0.0)
				z = 0.1;
			else if (z < 0.0)
				z = -0.1;
			
			if (math.wrapTo180(local_yaw) > 0.0)
				new_yaw += x * aim::predict_strength;

			if (math.wrapTo180(local_yaw) < 0.0)
				new_yaw += z * aim::predict_strength;
		}

		ctx->player->setRotationYaw(ctx, new_yaw);

		float pitch_diff = math.wrapTo180(-(ctx->player->getRotationPitch(ctx) - math.getAngles(ctx->player->getPositionVector(ctx), target->getPositionVector(ctx)).second));
		float new_pitch = local_pitch + (pitch_diff / (40 / aim::speed));
		ctx->player->setRotationPitch(ctx, new_pitch);
	}
}