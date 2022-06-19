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
            ImGui::Text("HP (%d/%d)  ", g_GameData->Player->HP, g_GameData->Player->MaxHP);
            ImGui::SameLine();
            ImGui::InputInt("##HP1", &g_GameData->Player->HP);

            ImGui::Text("MP (%d/%d)    ", g_GameData->Player->MP, g_GameData->Player->MaxMP);
            ImGui::SameLine();
            ImGui::InputInt("##MP1", &g_GameData->Player->MP);

            ImGui::Text("Attack        ");
            ImGui::SameLine();
            ImGui::InputInt("##Attack1", &g_GameData->Player->Attack);

            ImGui::Text("MagicAttack   ");
            ImGui::SameLine();
            ImGui::InputInt("##MagicAttack1", &g_GameData->Player->MagicAttack);

            ImGui::Text("Defense       ");
            ImGui::SameLine();
            ImGui::InputInt("##Defense1", &g_GameData->Player->Defense);

            ImGui::Text("MagicDefense  ");
            ImGui::SameLine();
            ImGui::InputInt("##MagicDefense1", &g_GameData->Player->MagicDefense);

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::TextCentered("CHEATS");
            ImGui::Toggle("ININITE HP", &g_GameVariables->bINFHEALTH);
            ImGui::Toggle("ININITE MP", &g_GameVariables->bINFMAGIC);
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

        //  I like to use tabs to display my content in an organized manner, Here is an example on how you could do the same
        //  As a courtesy I have left the TABS namespace with an Example Tab
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