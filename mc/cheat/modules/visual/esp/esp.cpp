#include "esp.h"
#include "../../../minecraft/render/activerenderinfo.h"

bool esp::toggle = false;
bool esp::awaiting_bind = false;
int esp::bind = 0;
const char* esp::bind_text = "[NONE]##1";

std::vector<std::vector<double>> esp::list_n = {};
std::vector<std::vector<std::string>> esp::list_s = {};
std::vector<std::vector<double>> esp::_3d_list_n = {};

bool esp::draw_box = false;
bool esp::draw_box_filled = false;
bool esp::draw_outline = true;

bool esp::draw_nametags = true;
bool esp::draw_hp = true;
bool esp::draw_hud = true;

bool esp::_3d = false;

float esp::color[4] = { 1, 1, 1, 1 };
float esp::outline_color[4] = { 0, 0, 0, 1 };


std::vector<double> multiplication(std::vector<double> vec, GLfloat mat[16])
{
	return {
		vec[0] * mat[0] + vec[1] * mat[4] + vec[2] * mat[8] + vec[3] * mat[12],
		vec[0] * mat[1] + vec[1] * mat[5] + vec[2] * mat[9] + vec[3] * mat[13],
		vec[0] * mat[2] + vec[1] * mat[6] + vec[2] * mat[10] + vec[3] * mat[14],
		vec[0] * mat[3] + vec[1] * mat[7] + vec[2] * mat[11] + vec[3] * mat[15]
	};
}

bool worldToScreen(std::vector<double> point_in_world, std::vector<float>& screen, GLfloat modelview[16], GLfloat projection[16], GLint viewport[16])
{
	std::vector<double> clipSpacePos = multiplication(multiplication({ point_in_world[0], point_in_world[1], point_in_world[2], 1.0f }, modelview), projection);

	std::vector<double> ndcSpacePos = {clipSpacePos[0] / clipSpacePos[3], clipSpacePos[1] / clipSpacePos[3], clipSpacePos[2] / clipSpacePos[3]};

	if (ndcSpacePos[2] < -1.0 || ndcSpacePos[2] > 1.0)
		return false;

	screen[0] = ((ndcSpacePos[0] + 1.0f) / 2.0f) * viewport[2];
	screen[1] = ((1.0f - ndcSpacePos[1]) / 2.0f) * viewport[3];

	return true;
}

void esp::use(c_context* ctx)
{
    if (!esp::toggle)
        return;

    if (!ctx->player->getObject() || !ctx->rendermanager->getObject() || !ctx->world->getObject() || !ctx->timer->getObject() || !ctx->gamesettings->getObject())
        return;

    std::vector<std::vector<double>> temp_list_n = {};
    std::vector<std::vector<std::string>> temp_list_s = {};
    std::vector<std::vector<double>> temp_list_3d = {};

    std::vector<jobject> players = ctx->world->getPlayers(ctx);
    if (players.size() <= 0)
    {
        esp::list_n = temp_list_n;
        esp::list_s = temp_list_s;
        esp::_3d_list_n = temp_list_3d;
        return;
    }

    for (int j = 0; j < players.size(); j++)
    {
        jobject obj = players[j];
        if (!obj)
            continue;

        c_player* player = new c_player(obj);
        if (!player->getObject())
            continue;

        if (!player->isEntityAlive(ctx))
            continue;

        if (player->getEntityId(ctx) == ctx->player->getEntityId(ctx))
            continue;

        if (!player->getBoundingBox(ctx))
            continue;

        float renderpartialticks = ctx->timer->getRenderPartialTicks(ctx);
        std::vector<double> renderpos = ctx->rendermanager->getRenderPositionVector(ctx);
        std::vector<double> playerpos = player->getPositionVector(ctx);
        std::vector<double> playerlasttickpos = player->getLastTickPositionVector(ctx);

        std::vector<double> bb = {
            (playerpos[0] - 0.4f) - renderpos[0] + -playerpos[0] + playerlasttickpos[0] + (playerpos[0] - playerlasttickpos[0]) * renderpartialticks,
            (playerpos[1] - 0.1f) - renderpos[1] + -playerpos[1] + playerlasttickpos[1] + (playerpos[1] - playerlasttickpos[1]) * renderpartialticks,
            (playerpos[2] - 0.4f) - renderpos[2] + -playerpos[2] + playerlasttickpos[2] + (playerpos[2] - playerlasttickpos[2]) * renderpartialticks,
            (playerpos[0] + 0.4f) - renderpos[0] + -playerpos[0] + playerlasttickpos[0] + (playerpos[0] - playerlasttickpos[0]) * renderpartialticks,
            (playerpos[1] + 2.f) - renderpos[1] + -playerpos[1] + playerlasttickpos[1] + (playerpos[1] - playerlasttickpos[1]) * renderpartialticks,
            (playerpos[2] + 0.4f) - renderpos[2] + -playerpos[2] + playerlasttickpos[2] + (playerpos[2] - playerlasttickpos[2]) * renderpartialticks
        };

        double box[8][3]
        {
            {bb[0], bb[1], bb[2]},
            {bb[0], bb[4], bb[2]},
            {bb[3], bb[4], bb[2]},
            {bb[3], bb[1], bb[2]},
            {bb[3], bb[4], bb[5]},
            {bb[0], bb[4], bb[5]},
            {bb[0], bb[1], bb[5]},
            {bb[3], bb[1], bb[5]},
        };

        std::vector<double> rect = { FLT_MAX, FLT_MAX, -1.f, -1.f };
        for (int i = 0; i < 8; i++)
        {
            std::vector<float> screen = { 0, 0 };
            if (!worldToScreen({ box[i][0], box[i][1], box[i][2] }, screen, activerenderinfo::modelview, activerenderinfo::projection, activerenderinfo::viewport))
                continue;

            rect[0] = std::fmin(screen[0], rect[0]);
            rect[1] = std::fmin(screen[1], rect[1]);
            rect[2] = std::fmax(screen[0], rect[2]);
            rect[3] = std::fmax(screen[1], rect[3]);
        }

        if (rect[0] == FLT_MAX && rect[1] == FLT_MAX && rect[2] == -1.f && rect[3] == -1.f)
            continue;

        if (rect[0] >= 0 || rect[1] >= 0 || rect[2] <= activerenderinfo::viewport[2] || rect[3] <= activerenderinfo::viewport[3])
        {
            float health = player->getHealth(ctx);
            double distance = player->getDistanceToEntity(ctx, ctx->player); // assuming getDistanceToEntity returns distance in meters or units used in your game

            temp_list_n.push_back(rect);
            temp_list_s.push_back({
                player->getName(ctx),
                std::to_string(health),
                std::to_string(static_cast<int>(distance)) + "m"
                });

            if (esp::_3d)
                temp_list_3d.push_back(bb);
        }

        if (obj)
            cheat::inst->env->DeleteLocalRef(obj);

        delete player;
    }

    esp::list_n = temp_list_n;
    esp::list_s = temp_list_s;
    esp::_3d_list_n = temp_list_3d;
}
