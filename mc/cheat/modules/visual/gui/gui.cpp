#include "gui.h"
#include <tchar.h>
#include <iomanip>
#include <sstream>

#include "../../../../imgui/imgui.h"
#include "../../../../imgui/imgui_impl_win32.h"
#include "../../../../imgui/imgui_impl_opengl3.h"
#include "../../../../imgui/imgui_internal.h"
#include "../../../../imgui/imstb_rectpack.h"
#include "../../../../imgui/imstb_truetype.h"
#include "../../../../imgui/imstb_textedit.h"
#include "../../../../imgui/imgui_impl_win32.h"

#include "../../combat/aim/aim.h"
#include "../../combat/clicker/clicker.h"
#include "../../combat/triggerbot/triggerbot.h"

#include "../../movement/blink/blink.h"
#include "../../movement/timer/timer.h"
#include "../../movement/sprint/sprint.h"

#include "../../visual/esp/esp.h"
#include "../../visual/esp/hud.h"
#include "../../visual/gui/gui.h"
#include "../../visual/fullbright/fullbright.h"

#include "../../../minecraft/render/activerenderinfo.h"

#define IMGUI_DEFINE_MATH_OPERATORS

float gui::menu_color[3] = { 1, 1, 1 };

HWND gui::hwnd = 0;
HDC gui::old_dc = 0;

float gui::item_alpha = 0;

bool gui::draw_ui = false;
bool gui::draw_hud = true;

std::vector<std::string> hud_modules = { "", "", "", "", "" };


void gui::drawMenu(HDC dc)
{
	for (static bool first = true; first; first = false)
	{
		hwnd = WindowFromDC(dc);
		old_dc = dc;

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.DeltaTime = 1000;

		ImGui_ImplWin32_Init(hwnd);
		ImGui_ImplOpenGL3_Init();

		ImGui::StyleColorsDark();
	}

	if (old_dc != dc)
	{
		hwnd = WindowFromDC(dc);
		old_dc = dc;
		cheat::wnd->hwnd = hwnd;

		SetWindowLongPtrA(cheat::wnd->hwnd, GWLP_WNDPROC, (LONG_PTR)cheat::hooks::inst->m_wndproc);
		cheat::hooks::inst->m_wndproc = SetWindowLongPtr(cheat::wnd->hwnd, GWLP_WNDPROC, (LONG_PTR)cheat::hooks::wndproc_hk);

		ImGui_ImplWin32_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();

		ImGui_ImplWin32_Init(hwnd);
		ImGui_ImplOpenGL3_Init();
	}

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	{
		ImGuiStyle* style = &ImGui::GetStyle();

		style->WindowBorderSize = 0.f;
		style->ChildBorderSize = 1.f;
		style->WindowBorderSize = 0.f;
		style->FrameBorderSize = 2.f;

		if (gui::draw_ui)
		{
			ImGui::SetNextWindowSize(ImVec2(700, 500));
			ImGui::Begin("xan", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
			{
				ImGui::BeginTabBar("tabbar");
				{
					if (ImGui::BeginTabItem("Aimbot"))
					{
						ImGui::Text("Aimbot");
						
						ImGui::SameLine(); ImGui::Checkbox("##1", &aim::toggle);
						ImGui::SameLine(); if (ImGui::Button(aim::bind_text, ImVec2(100, 20)))
						{
							aim::bind_text = "[...]";
							aim::awaiting_bind = true;
						}

						ImGui::SliderFloat("Speed", &aim::speed, 1, 30);
						ImGui::SliderFloat("FOV", &aim::fov, 1, 180);
						ImGui::SliderFloat("Distance", &aim::distance, 1, 100);
						
						ImGui::Text("\nWhitelist");
						ImGui::InputTextMultiline("##2", aim::whitelist, IM_ARRAYSIZE(aim::whitelist));

						ImGui::Checkbox("Prioritize Low Health", &aim::low_health);

						ImGui::Text("");

						ImGui::Checkbox("Require LMB", &aim::require_lmb);
						if (aim::require_lmb && aim::require_rmb)
							aim::require_rmb = false;

						ImGui::Checkbox("Require RMB", &aim::require_rmb);
						if (aim::require_rmb && aim::require_lmb)
							aim::require_lmb = false;

						ImGui::Text("");

						ImGui::Checkbox("Visibility Check", &aim::visibility_check);
						ImGui::Checkbox("Smart", &aim::smart);
						ImGui::Checkbox("Prediction", &aim::predict);
						ImGui::SliderFloat("Strength", &aim::predict_strength, 1, 100);

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Blink"))
					{
						ImGui::Text("Blink");

						ImGui::SameLine(); ImGui::Checkbox("##1", &blink::toggle);
						ImGui::SameLine(); if (ImGui::Button(blink::bind_text, ImVec2(100, 20)))
						{
							blink::bind_text = "[...]";
							blink::awaiting_bind = true;
						}

						ImGui::SliderFloat("Limit", &blink::limit, 1, 10);

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Timer"))
					{
						ImGui::Text("Timer");

						ImGui::SameLine(); ImGui::Checkbox("##1", &timer::toggle);
						ImGui::SameLine(); if (ImGui::Button(timer::bind_text, ImVec2(100, 20)))
						{
							timer::bind_text = "[...]";
							timer::awaiting_bind = true;
						}

						ImGui::SliderFloat("Speed", &timer::value, 1, 10);
						ImGui::Checkbox("Prevent Movement", &timer::block_movement);

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("ESP"))
					{
						ImGui::Text("ESP");

						ImGui::SameLine(); ImGui::Checkbox("##1", &esp::toggle);
						ImGui::SameLine(); if (ImGui::Button(esp::bind_text, ImVec2(100, 20)))
						{
							esp::bind_text = "[...]";
							esp::awaiting_bind = true;
						}

						ImGui::Checkbox("Box##1", &esp::draw_box);
						ImGui::Checkbox("Filled box##1", &esp::draw_box_filled);
						ImGui::Checkbox("Outlines##1", &esp::draw_outline);

						ImGui::ColorEdit4("Color##1", esp::color);
						ImGui::ColorEdit4("Outlines color##1", esp::outline_color);

						ImGui::Text("");
						ImGui::Checkbox("Nametags##1", &esp::draw_nametags);
						ImGui::Checkbox("HP##1", &esp::draw_hp);
						ImGui::Checkbox("HUD", &esp::draw_hud);
						
						ImGui::Text("");

						ImGui::Checkbox("3D", &esp::_3d);

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Fullbright"))
					{
						ImGui::Text("Fullbright");

						ImGui::SameLine(); ImGui::Checkbox("##1", &fullbright::toggle);
						ImGui::SameLine(); if (ImGui::Button(fullbright::bind_text, ImVec2(100, 20)))
						{
							fullbright::bind_text = "[...]";
							fullbright::awaiting_bind = true;
						}

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Sprint"))
					{
						ImGui::Text("Sprint");

						ImGui::SameLine(); ImGui::Checkbox("##1", &sprint::toggle);
						ImGui::SameLine(); if (ImGui::Button(sprint::bind_text, ImVec2(100, 20)))
						{
							sprint::bind_text = "[...]";
							sprint::awaiting_bind = true;
						}

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Clicker"))
					{
						ImGui::Text("Clicker");

						ImGui::SameLine(); ImGui::Checkbox("##1", &clicker::left::toggle);
						ImGui::SameLine(); if (ImGui::Button(clicker::left::bind_text, ImVec2(100, 20)))
						{
							clicker::left::bind_text = "[...]";
							clicker::left::awaiting_bind = true;
						}

						ImGui::SliderFloat("CPS", &clicker::left::value, 1, 10);

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Triggerbot"))
					{
						ImGui::Text("Triggerbot");

						ImGui::SameLine(); ImGui::Checkbox("##1", &triggerbot::toggle);
						ImGui::SameLine(); if (ImGui::Button(triggerbot::bind_text, ImVec2(100, 20)))
						{
							triggerbot::bind_text = "[...]";
							triggerbot::awaiting_bind = true;
						}

						ImGui::SliderFloat("Threshold", &triggerbot::threshold, 0.1, 2);
						ImGui::Checkbox("RMB Mode", &triggerbot::rmb);

						ImGui::EndTabItem();
					}
				}
				ImGui::EndTabBar();
			}
			ImGui::End();
		}

		{
			auto drawlist = ImGui::GetBackgroundDrawList();



			if (sizeof(activerenderinfo::viewport) > 0 && sizeof(activerenderinfo::projection) > 0 && sizeof(activerenderinfo::modelview) > 0)
			{
				// esp
				if (esp::toggle && !esp::_3d && esp::list_n.size() > 0)
				{
					auto rect = [&drawlist](std::vector<double> v, std::vector<std::string> vs)
					{
						std::stringstream ss(aim::whitelist);
						std::string to;

						std::vector<std::string> vvvv;
						if (aim::whitelist != NULL)
						{
							while (std::getline(ss, to, '\n')) {
								vvvv.push_back(to);
							}
						}

						if (std::find(vvvv.begin(), vvvv.end(), vs[0]) != vvvv.end())
							drawlist->AddRect(ImVec2(v[0], v[1]), ImVec2(v[2], v[3]), IM_COL32(0, 255, 0, esp::color[3] * 255), 0, 0, 1);
						else
							drawlist->AddRect(ImVec2(v[0], v[1]), ImVec2(v[2], v[3]), IM_COL32(esp::color[0] * 255, esp::color[1] * 255, esp::color[2] * 255, esp::color[3] * 255), 0, 0, 1);
					};
					auto rectf = [&drawlist](std::vector<double> v, std::vector<std::string> vs)
					{
						std::stringstream ss(aim::whitelist);
						std::string to;

						std::vector<std::string> vvvv;
						if (aim::whitelist != NULL)
						{
							while (std::getline(ss, to, '\n')) {
								vvvv.push_back(to);
							}
						}

						if (std::find(vvvv.begin(), vvvv.end(), vs[0]) != vvvv.end())
							drawlist->AddRectFilled(ImVec2(v[0], v[1]), ImVec2(v[0] + abs(v[2] - v[0]), v[1] + abs(v[3] - v[1])), IM_COL32(0, 255, 0, esp::color[3] * 255));
						else
							drawlist->AddRectFilled(ImVec2(v[0], v[1]), ImVec2(v[0] + abs(v[2] - v[0]), v[1] + abs(v[3] - v[1])), IM_COL32(esp::color[0] * 255, esp::color[1] * 255, esp::color[2] * 255, esp::color[3] * 255));
					};
					auto _rect = [&drawlist](std::vector<double> v, std::vector<std::string> vs)
					{
						std::stringstream ss(aim::whitelist);
						std::string to;

						std::vector<std::string> vvvv;
						if (aim::whitelist != NULL)
						{
							while (std::getline(ss, to, '\n')) {
								vvvv.push_back(to);
							}
						}

						if (std::find(vvvv.begin(), vvvv.end(), vs[0]) != vvvv.end())
						{
							drawlist->AddRect(ImVec2(v[0], v[1]), ImVec2(v[2], v[3]), IM_COL32(0, 255, 0, 255), 0, 0, 1);
							drawlist->AddRectFilled(ImVec2(v[0], v[1]), ImVec2(v[0] + abs(v[2] - v[0]), v[1] + abs(v[3] - v[1])), IM_COL32(0, 255, 0, esp::color[3] * 255));
						}
						else
						{
							drawlist->AddRect(ImVec2(v[0], v[1]), ImVec2(v[2], v[3]), IM_COL32(esp::color[0] * 255, esp::color[1] * 255, esp::color[2] * 255, 255), 0, 0, 1);
							drawlist->AddRectFilled(ImVec2(v[0], v[1]), ImVec2(v[0] + abs(v[2] - v[0]), v[1] + abs(v[3] - v[1])), IM_COL32(esp::color[0] * 255, esp::color[1] * 255, esp::color[2] * 255, esp::color[3] * 255));
						}
					};
					auto recto = [&drawlist](std::vector<double> v, std::vector<std::string> vs)
					{
						drawlist->AddRect(ImVec2(v[0], v[1]), ImVec2(v[2], v[3]), IM_COL32(esp::outline_color[0] * 255, esp::outline_color[1] * 255, esp::outline_color[2] * 255, esp::outline_color[3] * 255), 0, 0, 4);
					};
					auto name = [&drawlist](std::vector<double> vn, std::vector<std::string> vs)
						{
							// Format the distance and health text
							std::string distanceText = vs[2]; // No "m" here, just the number
							std::string healthText = vs[1]; // Added " HP" for clarity

							// Use a string stream to format health with one decimal place
							std::stringstream healthStream;
							healthStream << std::fixed << std::setprecision(1) << std::stof(vs[1]);
							healthText = healthStream.str();

							// Calculate the sizes for the distance, name, and health
							ImVec2 distanceSize = ImGui::CalcTextSize(distanceText.c_str());
							ImVec2 nameSize = ImGui::CalcTextSize(vs[0].c_str());
							ImVec2 healthSize = ImGui::CalcTextSize(healthText.c_str());

							// Calculate total size for the name tag
							float totalWidth = distanceSize.x + nameSize.x + healthSize.x + 20; // 20 for padding
							float totalHeight = nameSize.y + 4; // Slightly bigger than the text height

							// Calculate the background rectangle position
							ImVec2 min = ImVec2(vn[0], vn[1] - totalHeight / 2);
							ImVec2 max = ImVec2(min.x + totalWidth, vn[1] + totalHeight / 2);

							// Draw the background
							drawlist->AddRectFilled(min, max, ImColor(50, 50, 50, 180)); // Lighter gray background

							// Set the initial cursor position for text
							float curX = min.x + 5; // 5 pixels padding from the left edge
							float textY = vn[1] - totalHeight / 2;

							// Draw the text elements with appropriate padding
							drawlist->AddText(ImVec2(curX, textY), ImGui::GetColorU32(ImVec4(0, 1, 0, 1)), "[");
							curX += ImGui::CalcTextSize("[").x;
							drawlist->AddText(ImVec2(curX, textY), ImGui::GetColorU32(ImVec4(1, 1, 1, 1)), distanceText.c_str());
							curX += distanceSize.x;
							drawlist->AddText(ImVec2(curX, textY), ImGui::GetColorU32(ImVec4(0, 1, 0, 1)), "] ");
							curX += ImGui::CalcTextSize("] ").x;
							drawlist->AddText(ImVec2(curX, textY), ImGui::GetColorU32(ImVec4(1, 1, 1, 1)), (vs[0] + " ").c_str());
							curX += nameSize.x + ImGui::CalcTextSize(" ").x + 1;
							drawlist->AddText(ImVec2(curX, textY), ImGui::GetColorU32(ImVec4(0, 1, 0, 1)), healthText.c_str());
						};



					auto bar = [&drawlist](std::vector<double> vn, std::vector<std::string> vs)
					{
						drawlist->AddLine(ImVec2(vn[0] - 3, vn[1]), ImVec2(vn[0] - 3, vn[3]), IM_COL32(255, 0, 0, 220), 2);
						drawlist->AddLine(ImVec2(vn[0] - 3, vn[1] + ((abs(vn[3] - vn[1]) / 20) * (20 - std::stoi(vs[1])))), ImVec2(vn[0] - 3, vn[3]), IM_COL32(0, 255, 0, 220), 2);
					};
					auto baro = [&drawlist](std::vector<double> vn, std::vector<std::string> vs)
					{
						drawlist->AddLine(ImVec2(vn[0] - 4, vn[1]), ImVec2(vn[0] - 4, vn[3]), IM_COL32(0, 0, 0, 255), 4);
						drawlist->AddLine(ImVec2(vn[0] - 4, vn[1] + 1), ImVec2(vn[0] - 4, vn[3] - 1), IM_COL32(255, 0, 0, 220), 2);
						drawlist->AddLine(ImVec2(vn[0] - 4, vn[1] + 1 + ((abs(vn[3] - vn[1]) / 20) * (20 - std::stoi(vs[1])))), ImVec2(vn[0] - 4, vn[3] - 1), IM_COL32(0, 255, 0, 220), 2);
					};
				
					int l = esp::list_n.size();
					for (int i = 0; i < l; i++)
					{
						if (l > esp::list_n.size())
							break;

						std::vector<double> vn = esp::list_n[i];
						std::vector<std::string> vs = esp::list_s[i];

						if ((esp::draw_box || esp::draw_box_filled) && esp::draw_outline)
							recto(vn, vs);
						if (esp::draw_box && !esp::draw_box_filled)
							rect(vn, vs);
						else if (!esp::draw_box && esp::draw_box_filled)
							rectf(vn, vs);
						else if (esp::draw_box && esp::draw_box_filled)
							_rect(vn, vs);
						if (esp::draw_nametags)
							name(vn, vs);
						if (esp::draw_hp && !esp::draw_outline)
							bar(vn, vs);
						else if (esp::draw_hp && esp::draw_outline)
							baro(vn, vs);
					}

					
				}
				else if (esp::toggle)
				{
					// hud
					if (esp::draw_hud)
					{
						if (hud::health != 0 && hud::name != "")
						{
							ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
							ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 8.f);
							ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.06, 0.06, 0.06, 0.8));
							ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
							ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));
							ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
							ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));

							ImGui::SetNextWindowSize(ImVec2(100, 50));
							ImGui::SetNextWindowPos(ImVec2((activerenderinfo::viewport[2] / 2) - (100 / 2), (activerenderinfo::viewport[3] / 10 * 6) - (50 / 2)));
							ImGui::Begin("hudddd", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
							{
								std::string hp = "HP > " + std::to_string((int)hud::health);
								ImGui::Button(hud::name.c_str(), ImVec2(100, 25));
								ImGui::SetCursorPos(ImVec2(0, 25));

								ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 1, 0, 1));
								ImGui::Button(hp.c_str(), ImVec2(100, 25));
								ImGui::PopStyleColor();
							}
							ImGui::End();

							ImGui::PopStyleVar(2);
							ImGui::PopStyleColor(5);
						}
					}
				}
				
				// hud
				if (gui::draw_hud)
				{
					hud_modules[0] = aim::toggle ? "Aim: " + std::to_string(aim::speed).substr(0, std::to_string(aim::speed).find(".") + 2) : "";
					hud_modules[1] = blink::toggle ? "Blink: " + std::to_string(blink::limit).substr(0, std::to_string(blink::limit).find(".") + 2) : "";
					hud_modules[2] = timer::toggle ? "Timer: " + std::to_string(timer::value).substr(0, std::to_string(timer::value).find(".") + 2) : "";
					hud_modules[3] = esp::toggle ? "ESP: 2D" : "";
					hud_modules[4] = fullbright::toggle ? "Fullbright: ON" : "";

					std::vector<std::string> mods;
					for (const auto& mod : hud_modules) {
						if (!mod.empty()) {
							mods.push_back(mod);
						}
					}

					time_t now = time(nullptr);
					struct tm* timeinfo = localtime(&now);
					char buffer[80];
					strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
					std::string title = "Sleepy | Forge 1.8.9 | " + std::string(buffer);
					ImVec2 title_text_size = ImGui::CalcTextSize(title.c_str());

					ImVec4 bg_color = ImVec4(0.137f, 0.137f, 0.137f, 0.6f); // Semi-transparent background
					ImVec4 vibrant_purple = ImVec4(0.7f, 0.2f, 0.8f, 1.0f); // Vibrant purple for the border
					ImVec4 text_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

					// Title bar
					ImVec2 title_window_pos = ImVec2((ImGui::GetIO().DisplaySize.x - title_text_size.x) / 2, 10);
					ImGui::SetNextWindowPos(title_window_pos, ImGuiCond_FirstUseEver);
					ImGui::SetNextWindowSize(ImVec2(title_text_size.x + 20, title_text_size.y + 20));
					ImGui::Begin("HUDTitle", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
					{
						ImGui::Text("%s", title.c_str());
					}
					ImGui::End();

					// Blink bar
					if (blink::active)
					{
						auto now = std::chrono::steady_clock::now();
						float elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - blink::start_time).count() / 1000.0f;
						float progress = (blink::limit - elapsed) / blink::limit;
						progress = (progress < 0) ? 0 : (progress > 1 ? 1 : progress);

						ImVec2 window_pos = ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f + 25);
						ImVec2 window_size = ImVec2(200, 30); // Set the desired size of the progress bar
						ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
						ImGui::SetNextWindowSize(window_size);

						// Before starting the progress bar window, push a transparent color for the window background
						ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // Transparent window background

						ImGui::Begin("Blink Timer", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);

						// Apply the vibrant purple fill color to the progress bar
						ImGui::PushStyleColor(ImGuiCol_PlotHistogram, vibrant_purple); // Use vibrant purple for fill
						ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // Transparent background for the progress bar
						ImGui::PushStyleColor(ImGuiCol_Border, text_color); // Use the text color for the border
						ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
						ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);

						ImGui::ProgressBar(progress, ImVec2(-FLT_MIN, 0), "");

						ImGui::PopStyleVar(2);
						ImGui::PopStyleColor(4); // Pop FrameBg, PlotHistogram, Border, and WindowBg
						ImGui::End();
					}





					// Module list
					if (!mods.empty())
					{
						ImGui::PushStyleColor(ImGuiCol_Text, text_color);
						ImGui::PushStyleColor(ImGuiCol_WindowBg, bg_color);
						ImGui::PushStyleColor(ImGuiCol_Border, vibrant_purple);
						ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.f);
						ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4, 4)); // Adjusted padding

						// Calculate the width required for the longest module text
						int max_text_width = 0;
						for (const auto& mod : mods) {
							ImVec2 text_size = ImGui::CalcTextSize(mod.c_str());
							max_text_width = (text_size.x > max_text_width) ? text_size.x : max_text_width;
						}
						int window_width = max_text_width + 20 + 5; // Added space for the border line
						int window_height = ImGui::GetTextLineHeightWithSpacing() * mods.size() + 8; // Adjusted padding

						// Position the window at the top right corner
						ImVec2 window_pos = ImVec2(ImGui::GetIO().DisplaySize.x - window_width, 0);
						ImGui::SetNextWindowPos(window_pos);
						ImGui::SetNextWindowSize(ImVec2(window_width, window_height));

						ImGui::Begin("ModuleList", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
						{
							for (const auto& mod : mods) {
								ImGui::Text("%s", mod.c_str());
								// Draw a border line 5px to the right of the first character
								drawlist->AddLine(ImVec2(ImGui::GetCursorPosX() + 5, ImGui::GetCursorPosY()), ImVec2(ImGui::GetCursorPosX() + 5, ImGui::GetCursorPosY() + ImGui::GetTextLineHeight()), IM_COL32(vibrant_purple.x * 255, vibrant_purple.y * 255, vibrant_purple.z * 255, vibrant_purple.w * 255), 1.0f);
							}
						}
						ImGui::End();

						ImGui::PopStyleVar(2);
						ImGui::PopStyleColor(3);
					}
				}

			}

		}
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	ImGui::EndFrame();

}
