#include "Menu.hpp"
namespace FF7Remake {

	namespace Styles {
        void InitStyle()
        {
            ImGuiStyle& style = ImGui::GetStyle();
            ImVec4* colors = ImGui::GetStyle().Colors;

            //	STYLE PROPERTIES
            style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

            //  Base ImGui Styling , Aplying a custyom style is left up to you.
            ImGui::StyleColorsClassic();

            /// EXAMPLE COLOR 
            //colors[ImGuiCol_FrameBg] = ImVec4(0, 0, 0, 0);

            //	COLORS
            if (g_Menu->dbg_RAINBOW_THEME) {
                //  RGB MODE STLYE PROPERTIES
                colors[ImGuiCol_Separator] = ImVec4(g_Menu->dbg_RAINBOW);
                colors[ImGuiCol_TitleBg] = ImVec4(0, 0, 0, 1.0f);
                colors[ImGuiCol_TitleBgActive] = ImVec4(0, 0, 0, 1.0f);
                colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0, 0, 0, 1.0f);
            }
            else {
                /// YOUR DEFAULT STYLE PROPERTIES HERE
            }
        }
	}

	namespace Tabs {
        void TABMain()
        {
            ImGui::TextCentered("PLAYER STATS");
            ImGui::Spacing();

            ImGui::InputInt("##HP1", &g_GameData->Player->HP);
            ImGui::SameLine();
            ImGui::Text("HP (%d/%d)", g_GameData->Player->HP, g_GameData->Player->MaxHP);

            ImGui::InputInt("##MP1", &g_GameData->Player->MP);
            ImGui::SameLine();
            ImGui::Text("MP (%d/%d)", g_GameData->Player->MP, g_GameData->Player->MaxMP);

            ImGui::InputInt("##Attack1", &g_GameData->Player->Attack);
            ImGui::SameLine();
            ImGui::Text("Attack");

            ImGui::InputInt("##MagicAttack1", &g_GameData->Player->MagicAttack);
            ImGui::SameLine();
            ImGui::Text("MagicAttack");

            ImGui::InputInt("##Defense1", &g_GameData->Player->Defense);
            ImGui::SameLine();
            ImGui::Text("Defense");

            ImGui::InputInt("##MagicDefense1", &g_GameData->Player->MagicDefense);
            ImGui::SameLine();
            ImGui::Text("MagicDefense");

            ImGui::InputInt("##Strength1", &g_GameData->Player->Strength);
            ImGui::SameLine();
            ImGui::Text("Strength");

            ImGui::InputInt("##Magic1", &g_GameData->Player->Magic);
            ImGui::SameLine();
            ImGui::Text("Magic");

            ImGui::InputInt("##Vitality1", &g_GameData->Player->Vitality);
            ImGui::SameLine();
            ImGui::Text("Vitality");

            ImGui::InputInt("##Spirit1", &g_GameData->Player->Spirit);
            ImGui::SameLine();
            ImGui::Text("Spirit");

            ImGui::InputInt("##Luck1", &g_GameData->Player->Luck);
            ImGui::SameLine();
            ImGui::Text("Luck");

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::TextCentered("CHEATS");
            ImGui::Toggle("INFINITE HP", &g_GameVariables->bINFHEALTH);
            ImGui::Toggle("INFINITE MP", &g_GameVariables->bINFMAGIC);
        }

        void TABAbout()
        {
            ImGui::Text("BASE MENU (PREVIEW)");
            ImGui::Text("BUILD VERSION: v1.0");
            ImGui::Text("BUILD DATE: 6/19/2022");
            ImGui::Checkbox("SHOW IMGUI DEMO", &g_GameVariables->m_ShowDemo);
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            if (ImGui::Button("UNHOOK DLL", ImVec2(ImGui::GetWindowContentRegionWidth() - 3, 20))) {
#if DEBUG
                g_Console->printdbg("\n\n[+] UNHOOK INITIALIZED [+]\n\n", g_Console->color.red);
#endif
                og_Killswitch = TRUE;
            }
        }
	}

	void Menu::Draw()
	{
		if (g_GameVariables->m_ShowMenu)
			MainMenu();

		if (g_GameVariables->m_ShowHud)
			HUD(&g_GameVariables->m_ShowHud);

		if (g_GameVariables->m_ShowDemo)
			ImGui::ShowDemoWindow();
	}

	void Menu::MainMenu()
	{
        if (!g_GameVariables->m_ShowDemo)
            Styles::InitStyle();

        if (g_Menu->dbg_RAINBOW_THEME) {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(g_Menu->dbg_RAINBOW));
            ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(g_Menu->dbg_RAINBOW));
            ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(g_Menu->dbg_RAINBOW));
        }
        if (!ImGui::Begin("Final Fantasy 7", &g_GameVariables->m_ShowMenu, 96))
        {
            ImGui::End();
            return;
        }
        if (g_Menu->dbg_RAINBOW_THEME) {
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
        }

        if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
        {
            if (ImGui::BeginTabItem("MAIN"))
            {
                Tabs::TABMain();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("DEBUG"))
            {
                Tabs::TABAbout();
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        ImGui::End();
	}

	void Menu::HUD(bool* p_open)
	{

	}

	void Menu::Loops()
	{
        if (g_GameVariables->bINFHEALTH)
            g_GameData->Player->HP = g_GameData->Player->MaxHP;

        if (g_GameVariables->bINFMAGIC)
            g_GameData->Player->MP = g_GameData->Player->MaxMP;
	}
}