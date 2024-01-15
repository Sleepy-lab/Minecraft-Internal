#include "../cheat.h"
#include "../modules/visual/gui/gui.h"
#include "../modules/visual/esp/esp.h"
#include "../modules/combat/aim/aim.h"
#include "../minecraft/render/activerenderinfo.h"

fn_wglSwapBuffers og_wglSwapBuffers;

bool __stdcall cheat::hooks::wglSwapBuffers_hk(_In_ HDC hdc)
{
	cheat::wnd->hwnd = WindowFromDC(hdc);
	gui::drawMenu(hdc);

	if ((esp::toggle) && ((gui::draw_ui && cheat::inst->b_inventory) || (!cheat::inst->b_inventory)) && sizeof(activerenderinfo::viewport) > 0 && sizeof(activerenderinfo::projection) > 0 && sizeof(activerenderinfo::modelview) > 0)
	{
		glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(activerenderinfo::projection);
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(activerenderinfo::modelview);
		glPushMatrix();
		glEnable(GL_LINE_SMOOTH);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);
		glDepthMask(false);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glLineWidth(1.f);

		if (esp::toggle && esp::_3d && esp::list_n.size() > 0 && esp::_3d_list_n.size() > 0 && esp::list_s.size() > 0)
		{
			auto box = [](std::vector<double> v)
			{
				glBegin(3);
				glVertex3f(v[0], v[1], v[2]);
				glVertex3f(v[3], v[1], v[2]);
				glVertex3f(v[3], v[1], v[5]);
				glVertex3f(v[0], v[1], v[5]);
				glVertex3f(v[0], v[1], v[2]);
				glEnd();

				glBegin(3);
				glVertex3f(v[0], v[4], v[2]);
				glVertex3f(v[3], v[4], v[2]);
				glVertex3f(v[3], v[4], v[5]);
				glVertex3f(v[0], v[4], v[5]);
				glVertex3f(v[0], v[4], v[2]);
				glEnd();

				glBegin(1);
				glVertex3f(v[0], v[1], v[2]);
				glVertex3f(v[0], v[4], v[2]);
				glVertex3f(v[3], v[1], v[2]);
				glVertex3f(v[3], v[4], v[2]);
				glVertex3f(v[3], v[1], v[5]);
				glVertex3f(v[3], v[4], v[5]);
				glVertex3f(v[0], v[1], v[5]);
				glVertex3f(v[0], v[4], v[5]);
				glEnd();
			};
			auto boxf = [](std::vector<double> v)
			{
				glBegin(7);
				glVertex3f(v[0], v[1], v[2]);
				glVertex3f(v[0], v[4], v[2]);
				glVertex3f(v[0], v[1], v[2]);
				glVertex3f(v[3], v[4], v[2]);
				glVertex3f(v[3], v[1], v[5]);
				glVertex3f(v[3], v[4], v[5]);
				glVertex3f(v[0], v[1], v[5]);
				glVertex3f(v[0], v[4], v[5]);
				glEnd();
				glBegin(7);
				glVertex3f(v[3], v[4], v[2]);
				glVertex3f(v[3], v[1], v[2]);
				glVertex3f(v[0], v[4], v[2]);
				glVertex3f(v[0], v[1], v[2]);
				glVertex3f(v[0], v[4], v[5]);
				glVertex3f(v[0], v[1], v[5]);
				glVertex3f(v[3], v[4], v[5]);
				glVertex3f(v[3], v[1], v[5]);
				glEnd();
				glBegin(7);
				glVertex3f(v[0], v[1], v[2]);
				glVertex3f(v[0], v[4], v[2]);
				glVertex3f(v[3], v[1], v[2]);
				glVertex3f(v[3], v[4], v[2]);
				glEnd();
				glBegin(7);
				glVertex3f(v[0], v[4], v[2]);
				glVertex3f(v[3], v[4], v[2]);
				glVertex3f(v[3], v[4], v[5]);
				glVertex3f(v[0], v[4], v[5]);
				glVertex3f(v[0], v[4], v[2]);
				glVertex3f(v[0], v[4], v[5]);
				glVertex3f(v[3], v[4], v[5]);
				glVertex3f(v[3], v[4], v[2]);
				glEnd();
				glBegin(7);
				glVertex3f(v[0], v[1], v[2]);
				glVertex3f(v[3], v[1], v[2]);
				glVertex3f(v[3], v[1], v[5]);
				glVertex3f(v[0], v[1], v[5]);
				glVertex3f(v[0], v[1], v[2]);
				glVertex3f(v[0], v[1], v[5]);
				glVertex3f(v[3], v[1], v[5]);
				glVertex3f(v[3], v[1], v[2]);
				glEnd();
				glBegin(7);
				glVertex3f(v[0], v[1], v[2]);
				glVertex3f(v[0], v[4], v[2]);
				glVertex3f(v[0], v[1], v[5]);
				glVertex3f(v[0], v[4], v[5]);
				glVertex3f(v[3], v[1], v[5]);
				glVertex3f(v[3], v[4], v[5]);
				glVertex3f(v[3], v[1], v[2]);
				glVertex3f(v[3], v[4], v[2]);
				glEnd();
				glBegin(7);
				glVertex3f(v[0], v[4], v[5]);
				glVertex3f(v[0], v[1], v[5]);
				glVertex3f(v[0], v[4], v[2]);
				glVertex3f(v[0], v[1], v[2]);
				glVertex3f(v[3], v[4], v[2]);
				glVertex3f(v[3], v[1], v[2]);
				glVertex3f(v[3], v[4], v[5]);
				glVertex3f(v[3], v[1], v[5]);
				glEnd();
			};

			int size = esp::_3d_list_n.size();
			if (size == esp::list_n.size())
			{
				for (int i = 0; i < size; i++)
				{
					if (size > esp::_3d_list_n.size() || size > esp::list_n.size())
						break;

					std::vector<double> v = esp::_3d_list_n[i];
					std::vector<std::string> vs = esp::list_s[i];

					std::stringstream ss(aim::whitelist);
					std::string to;

					std::vector<std::string> vvvv;
					if (aim::whitelist != NULL)
					{
						while (std::getline(ss, to, '\n')) {
							vvvv.push_back(to);
						}
					}

					if (esp::draw_box && !esp::draw_box_filled)
					{
						if (std::find(vvvv.begin(), vvvv.end(), vs[0]) != vvvv.end())
							glColor4f(0, 255, 0, esp::color[3]);
						else
							glColor4f(esp::color[0], esp::color[1], esp::color[2], esp::color[3]);
						box(v);
					}
					else if (!esp::draw_box && esp::draw_box_filled)
					{
						if (std::find(vvvv.begin(), vvvv.end(), vs[0]) != vvvv.end())
							glColor4f(0, 255, 0, esp::color[3]);
						else
							glColor4f(esp::color[0], esp::color[1], esp::color[2], esp::color[3]);
						boxf(v);
					}
					else if (esp::draw_box && esp::draw_box_filled)
					{
						if (std::find(vvvv.begin(), vvvv.end(), vs[0]) != vvvv.end())
							glColor4f(0, 255, 0, esp::color[3]);
						else
							glColor4f(esp::color[0], esp::color[1], esp::color[2], esp::color[3]);
						boxf(v);
						if (std::find(vvvv.begin(), vvvv.end(), vs[0]) != vvvv.end())
							glColor4f(0, 255, 0, 255);
						else
							glColor4f(esp::color[0], esp::color[1], esp::color[2], 255);
						box(v);
					}
				}
			}
		}

		glDisable(GL_BLEND);
		glDepthMask(true);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_LINE_SMOOTH);
		glPopMatrix();
		glPopMatrix();
	}

	return og_wglSwapBuffers(hdc);
}