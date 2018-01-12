#pragma once
#include "Configuration.hpp"
#include "dropboxes.h"
#include "Variables.h"
#include "Tabs.h"
#include "Themes.h"
#include "XorStr.hpp"
#include <Windows.h>
#include <chrono>
#include "IconFontAwesome.h"

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))
extern HMODULE g_hLib;
extern HWND g_hWnd;


namespace ImGui
{
	class Tab
	{
	private:

		std::vector<std::string> labels;

	public:

		void add(std::string name)
		{
			labels.push_back(name);
		}

		void draw(int *selected)
		{
			ImGuiStyle &style = GetStyle();
			ImVec4 color = style.Colors[ImGuiCol_Button];
			ImVec4 colorActive = style.Colors[ImGuiCol_ButtonActive];
			ImVec4 colorHover = style.Colors[ImGuiCol_ButtonHovered];
			ImVec2 max = GetContentRegionMax();
			float size_x = max.x / labels.size() - 0.f;
			float size_y = max.y / labels.size() - 30.f;

			for (size_t i = 0; i < labels.size(); i++)
			{
				if (i == *selected)
				{
					style.Colors[ImGuiCol_Button] = colorActive;
					style.Colors[ImGuiCol_ButtonActive] = colorActive;
					style.Colors[ImGuiCol_ButtonHovered] = colorActive;
				}
				else
				{
					style.Colors[ImGuiCol_Button] = color;
					style.Colors[ImGuiCol_ButtonActive] = colorActive;
					style.Colors[ImGuiCol_ButtonHovered] = colorHover;
				}

				if (Button(labels.at(i).c_str(), { size_x, size_y }))
					*selected = i;
			}

			style.Colors[ImGuiCol_Button] = color;
			style.Colors[ImGuiCol_ButtonActive] = colorActive;
			style.Colors[ImGuiCol_ButtonHovered] = colorHover;
		}
	};
}

void RenderInterface() {
	

	switch (g_Options.Menu.Theme)
	{
	case 0:
		RenderRay();
		break;
	case 1:
		RenderMono();
		break;
	case 2:
		RenderDefault();
		break;
	case 3:
		RenderOverlay();
		break;
	case 4:
		RenderGlad();
			break;
	case 5:
		RenderXD();
		break;
	
	}
	
	static int p = 0;
	
	ImGui::SetNextWindowSize(ImVec2(774, 330), ImGuiSetCond_FirstUseEver);
	ImGui::SetNextWindowPosCenter(ImGuiSetCond_FirstUseEver);
	if (ImGui::Begin(XorStr("Hades - Private (Alpha)"), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders |  ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar))
	{

		ImGui::BeginGroup();
		
		ImGuiStyle& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
		ImGui::BeginChild("##logo", ImVec2(130, 60), false);
		{
			static int fps = 0;
			using namespace std::chrono;
			static int count = 0;
			static auto last = high_resolution_clock::now();
			auto now = high_resolution_clock::now();
			count++;
			if (duration_cast<milliseconds>(now - last).count() > 1000) {
				fps = count;
				count = 0;
				last = now;
			}
			ImGui::NewLine();
			ImGui::Text(XorStr("    Hades - Private"));
			ImGui::Separator();
			ImGui::TextColored(ImVec4{ 1.0f, 1.0f, 1.0f, 0.5f }, "     FPS: %03d", fps);
		}ImGui::EndChild();
		style.Colors[ImGuiCol_Border] = ImVec4(0.16f, 0.16f, 0.16f, 0.5f);
		ImGui::Tab tabs;
		//tabs.add("Rage");
		tabs.add("Legit");
		tabs.add("Visuals");
		tabs.add("Misc");
		tabs.add("Skinchanger");
		tabs.add("HVH");
		tabs.add("Colors");


		ImGui::NewLine();
		tabs.draw(&p);



		//ImGui::NewLine();
		ImGui::NewLine();
		ImGui::BeginChild("##conf", ImVec2(124, 60), false);
		{
			drawConfig();
		}ImGui::EndChild();
	
		ImGui::EndGroup();

		ImGui::SameLine();
		style.Colors[ImGuiCol_Border] = ImVec4(0.61f, 0.00f, 1.f, 0.5f);
		ImGui::BeginGroup();
		{
			ImGui::PushID(p);
			{
				switch (p)
				{

				case 0:
					RenderLegit();
					break;
				case 1:
					RenderVisuals();
					break;
				case 2:
					RenderMisc();
					break;
				case 3:
					RenderSkinChanger();
					break;
				case 4:
					RenderRage();
					break;
				case 5:
					RenderColors();
					break;
				}
			}ImGui::PopID();

		}ImGui::EndGroup();

		
	}ImGui::End();

	//TOO LAZY TO FIX THIS MENU, ITS COOL THO
	
	/*
	ImGui::SetNextWindowPos(ImVec2(0, 400),ImGuiSetCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(300, 346),ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Hades", &g_Options.Menu.Opened, ImVec2(300, 346), -1.0f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar);
	{
		
	RenderMain();


	}ImGui::End();
	*/
	/*
	int iTab;
	ImGui::SetNextWindowSize(ImVec2(774, 330), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("a source", &g_Options.Menu.Opened, ImVec2(774, 330), 1.f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
	{
		char* text = XorStr("Unknown");
		text = XorStr(ICON_FA_SHIELD "  Hades Private(Beta)");

		//ImGui::Text(text);

		ImGui::Columns(2, nullptr, false);
		ImGui::SetColumnOffset(1, 230);
		ImGuiStyle& style = ImGui::GetStyle();
		style.ItemSpacing = ImVec2(0.f, 0.f);
		ImGui::BeginChild("##tabs", ImVec2(200, 350), false);
		{
			style.Colors[ImGuiCol_Button] = iTab == 0 ? ImColor(199, 79, 13) : ImColor(18, 18, 18, 255);
			if (ImGui::Button("Aimbot", ImVec2(200, 45))) iTab = 0;
			style.Colors[ImGuiCol_Button] = iTab == 1 ? ImColor(199, 79, 13) : ImColor(18, 18, 18, 255);
			if (ImGui::Button("Visuals", ImVec2(200, 45))) iTab = 1;
			style.Colors[ImGuiCol_Button] = iTab == 2 ? ImColor(199, 79, 13) : ImColor(18, 18, 18, 255);
			if (ImGui::Button("Misc", ImVec2(200, 45))) iTab = 2;
			style.Colors[ImGuiCol_Button] = iTab == 3 ? ImColor(199, 79, 13) : ImColor(18, 18, 18, 255);
			if (ImGui::Button("Skins", ImVec2(200, 45))) iTab = 3;
		}ImGui::EndChild();

		ImGui::NextColumn();


		ImGui::BeginChild("##main", ImVec2(670, 350), true);
		{
			switch (iTab)
			{
			case 0: //aimbot
			{
				if (ImGui::Button("Unhook"))
				{
					g_Engine->ClientCmd_Unrestricted("cl_mouseenable 1");
					unload = true;
				}
			}
				break;
			case 1:
				RenderRage();
				break;
			}
		}ImGui::EndChild();
	}
	ImGui::End();
	*/
	

}


