#include "Menu.hpp"

int SELECTED_ITEM;
const char* ITEMS[4]{ "CLOUD", "PARTY SLOT 2", "PARTY SLOT 3", "PARTY SLOT 4" };

namespace FF7Remake {

	namespace Styles {
        void InitStyle()
        {
            ImGuiStyle& style = ImGui::GetStyle();
            ImVec4* colors = ImGui::GetStyle().Colors;

            //	STYLE PROPERTIES
            style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
            style.FrameRounding = 1;
            style.TabRounding = 0;
            style.WindowBorderSize = 1;
            style.ChildBorderSize = 1;
            style.PopupBorderSize = 1;
            style.FrameBorderSize = 1;
            style.TabBorderSize = 1;

            //	COLORS
            colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
            colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
            colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.36f, 0.69f, 0.25f);
            colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
            colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
            colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
            colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
            colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
            colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
            colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
            colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
            colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
            colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
            colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
            colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
            colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
            colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
            colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
            colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
            colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
            colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
            colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
            colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
            colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
            colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
            colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.35f, 0.58f, 0.86f);
            colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
            colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.41f, 0.68f, 1.00f);
            colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
            colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
            colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
            colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
            colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
            colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
            colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
            colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
            colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
            colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
            colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
            colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
            colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
            colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
            colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
            colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
            
            switch(g_Menu->dbg_RAINBOW_THEME) {
            case(TRUE):
                //  RGB MODE STLYE PROPERTIES
                colors[ImGuiCol_Separator] = ImVec4(g_Menu->dbg_RAINBOW);
                colors[ImGuiCol_SeparatorHovered] = ImVec4(g_Menu->dbg_RAINBOW);
                colors[ImGuiCol_SeparatorActive] = ImVec4(g_Menu->dbg_RAINBOW);
                colors[ImGuiCol_TitleBg] = ImVec4(0, 0, 0, 1.0f);
                colors[ImGuiCol_TitleBgActive] = ImVec4(0, 0, 0, 1.0f);
                colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0, 0, 0, 1.0f);
                break;
            case(FALSE):
                colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
                colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
                colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
                colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
                colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
                colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
                break;
            }
        }
	}

    namespace PlayerStats {
        void STATCloud()
        {
            ImGui::TextCentered("PLAYER STATS");
            ImGui::Spacing();

            ImGui::InputInt("##HP1", &g_GameData->Cloud->HP);
            ImGui::SameLine();
            ImGui::Text("HP (%d/%d)", g_GameData->Cloud->HP, g_GameData->Cloud->MaxHP);

            ImGui::InputInt("##MP1", &g_GameData->Cloud->MP);
            ImGui::SameLine();
            ImGui::Text("MP (%d/%d)", g_GameData->Cloud->MP, g_GameData->Cloud->MaxMP);

            ImGui::InputInt("##Attack1", &g_GameData->Cloud->Attack);
            ImGui::SameLine();
            ImGui::Text("Attack");

            ImGui::InputInt("##MagicAttack1", &g_GameData->Cloud->MagicAttack);
            ImGui::SameLine();
            ImGui::Text("MagicAttack");

            ImGui::InputInt("##Defense1", &g_GameData->Cloud->Defense);
            ImGui::SameLine();
            ImGui::Text("Defense");

            ImGui::InputInt("##MagicDefense1", &g_GameData->Cloud->MagicDefense);
            ImGui::SameLine();
            ImGui::Text("MagicDefense");

            ImGui::InputInt("##Strength1", &g_GameData->Cloud->Strength);
            ImGui::SameLine();
            ImGui::Text("Strength");

            ImGui::InputInt("##Magic1", &g_GameData->Cloud->Magic);
            ImGui::SameLine();
            ImGui::Text("Magic");

            ImGui::InputInt("##Vitality1", &g_GameData->Cloud->Vitality);
            ImGui::SameLine();
            ImGui::Text("Vitality");

            ImGui::InputInt("##Spirit1", &g_GameData->Cloud->Spirit);
            ImGui::SameLine();
            ImGui::Text("Spirit");

            ImGui::InputInt("##Luck1", &g_GameData->Cloud->Luck);
            ImGui::SameLine();
            ImGui::Text("Luck");

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::TextCentered("CHEATS");
            if (ImGui::Toggle("INFINITE HP", &g_GameVariables->bINFHEALTH)) g_Console->LogEvent("Stats::InfiniteHealth ; ", g_GameVariables->bINFHEALTH);
            if (ImGui::Toggle("INFINITE MP", &g_GameVariables->bINFMAGIC)) g_Console->LogEvent("Stats::InfiniteMagic ; ", g_GameVariables->bINFMAGIC);
        }

        void STATParty2()
        {
            ImGui::TextCentered("PLAYER STATS");
            ImGui::Spacing();

            ImGui::InputInt("##HP1", &g_GameData->Party2->HP);
            ImGui::SameLine();
            ImGui::Text("HP (%d/%d)", g_GameData->Party2->HP, g_GameData->Party2->MaxHP);

            ImGui::InputInt("##MP1", &g_GameData->Party2->MP);
            ImGui::SameLine();
            ImGui::Text("MP (%d/%d)", g_GameData->Party2->MP, g_GameData->Party2->MaxMP);

            ImGui::InputInt("##Attack1", &g_GameData->Party2->Attack);
            ImGui::SameLine();
            ImGui::Text("Attack");

            ImGui::InputInt("##MagicAttack1", &g_GameData->Party2->MagicAttack);
            ImGui::SameLine();
            ImGui::Text("MagicAttack");

            ImGui::InputInt("##Defense1", &g_GameData->Party2->Defense);
            ImGui::SameLine();
            ImGui::Text("Defense");

            ImGui::InputInt("##MagicDefense1", &g_GameData->Party2->MagicDefense);
            ImGui::SameLine();
            ImGui::Text("MagicDefense");

            ImGui::InputInt("##Strength1", &g_GameData->Party2->Strength);
            ImGui::SameLine();
            ImGui::Text("Strength");

            ImGui::InputInt("##Magic1", &g_GameData->Party2->Magic);
            ImGui::SameLine();
            ImGui::Text("Magic");

            ImGui::InputInt("##Vitality1", &g_GameData->Party2->Vitality);
            ImGui::SameLine();
            ImGui::Text("Vitality");

            ImGui::InputInt("##Spirit1", &g_GameData->Party2->Spirit);
            ImGui::SameLine();
            ImGui::Text("Spirit");

            ImGui::InputInt("##Luck1", &g_GameData->Party2->Luck);
            ImGui::SameLine();
            ImGui::Text("Luck");
        }

        void STATParty3()
        {
            ImGui::TextCentered("PLAYER STATS");
            ImGui::Spacing();

            ImGui::InputInt("##HP1", &g_GameData->Party3->HP);
            ImGui::SameLine();
            ImGui::Text("HP (%d/%d)", g_GameData->Party3->HP, g_GameData->Party3->MaxHP);

            ImGui::InputInt("##MP1", &g_GameData->Party3->MP);
            ImGui::SameLine();
            ImGui::Text("MP (%d/%d)", g_GameData->Party3->MP, g_GameData->Party3->MaxMP);

            ImGui::InputInt("##Attack1", &g_GameData->Party3->Attack);
            ImGui::SameLine();
            ImGui::Text("Attack");

            ImGui::InputInt("##MagicAttack1", &g_GameData->Party3->MagicAttack);
            ImGui::SameLine();
            ImGui::Text("MagicAttack");

            ImGui::InputInt("##Defense1", &g_GameData->Party3->Defense);
            ImGui::SameLine();
            ImGui::Text("Defense");

            ImGui::InputInt("##MagicDefense1", &g_GameData->Party3->MagicDefense);
            ImGui::SameLine();
            ImGui::Text("MagicDefense");

            ImGui::InputInt("##Strength1", &g_GameData->Party3->Strength);
            ImGui::SameLine();
            ImGui::Text("Strength");

            ImGui::InputInt("##Magic1", &g_GameData->Party3->Magic);
            ImGui::SameLine();
            ImGui::Text("Magic");

            ImGui::InputInt("##Vitality1", &g_GameData->Party3->Vitality);
            ImGui::SameLine();
            ImGui::Text("Vitality");

            ImGui::InputInt("##Spirit1", &g_GameData->Party3->Spirit);
            ImGui::SameLine();
            ImGui::Text("Spirit");

            ImGui::InputInt("##Luck1", &g_GameData->Party3->Luck);
            ImGui::SameLine();
            ImGui::Text("Luck");
        }

        void STATParty4()
        {
            ImGui::TextCentered("PLAYER STATS");
            ImGui::Spacing();

            ImGui::InputInt("##HP1", &g_GameData->Party4->HP);
            ImGui::SameLine();
            ImGui::Text("HP (%d/%d)", g_GameData->Party4->HP, g_GameData->Party4->MaxHP);

            ImGui::InputInt("##MP1", &g_GameData->Party4->MP);
            ImGui::SameLine();
            ImGui::Text("MP (%d/%d)", g_GameData->Party4->MP, g_GameData->Party4->MaxMP);

            ImGui::InputInt("##Attack1", &g_GameData->Party4->Attack);
            ImGui::SameLine();
            ImGui::Text("Attack");

            ImGui::InputInt("##MagicAttack1", &g_GameData->Party4->MagicAttack);
            ImGui::SameLine();
            ImGui::Text("MagicAttack");

            ImGui::InputInt("##Defense1", &g_GameData->Party4->Defense);
            ImGui::SameLine();
            ImGui::Text("Defense");

            ImGui::InputInt("##MagicDefense1", &g_GameData->Party4->MagicDefense);
            ImGui::SameLine();
            ImGui::Text("MagicDefense");

            ImGui::InputInt("##Strength1", &g_GameData->Party4->Strength);
            ImGui::SameLine();
            ImGui::Text("Strength");

            ImGui::InputInt("##Magic1", &g_GameData->Party4->Magic);
            ImGui::SameLine();
            ImGui::Text("Magic");

            ImGui::InputInt("##Vitality1", &g_GameData->Party4->Vitality);
            ImGui::SameLine();
            ImGui::Text("Vitality");

            ImGui::InputInt("##Spirit1", &g_GameData->Party4->Spirit);
            ImGui::SameLine();
            ImGui::Text("Spirit");

            ImGui::InputInt("##Luck1", &g_GameData->Party4->Luck);
            ImGui::SameLine();
            ImGui::Text("Luck");
        }
    }

	namespace Tabs {
        void TABMain()
        {
            ImGui::TextCentered("PLAYER SELECT");
            ImGui::Combo("##ComboLabel", &SELECTED_ITEM, ITEMS, IM_ARRAYSIZE(ITEMS));
            ImGui::Separator();
            switch (SELECTED_ITEM) {
            case(0):
                PlayerStats::STATCloud();
                break;
            case(1):
                PlayerStats::STATParty2();
                break;
            case(2):
                PlayerStats::STATParty3();
                break;
            case(3):
                PlayerStats::STATParty4();
                break;
            }
        }

        void TABAbout()
        {
            ImGui::Text("BASE MENU (PREVIEW)");
            ImGui::Text("BUILD VERSION: v1.0");
            ImGui::Text("BUILD DATE: 6/19/2022");
            if (ImGui::Checkbox("RGB MODE", &g_Menu->dbg_RAINBOW_THEME)) g_Console->LogEvent("Menu::RainbowTheme ; ", g_Menu->dbg_RAINBOW_THEME);
            if (ImGui::Checkbox("SHOW IMGUI DEMO", &g_GameVariables->m_ShowDemo)) g_Console->LogEvent("Menu::ShowImGuiDemo ; ", g_GameVariables->m_ShowDemo);
#if DEBUG
            if (ImGui::Checkbox("VERBOSE LOGGING", &g_Console->verbose)) g_Console->LogEvent("Console::VerboseLogging ; ", g_Console->verbose);
#endif
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

        //  Currently Unused
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
        if (!ImGui::Begin("Final Fantasy 7", &g_GameVariables->m_ShowMenu, 96 | ImGuiWindowFlags_NoTitleBar))
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
        //  This isn't really infinite.
        // - You can die if you take more damage than maximum hp
        // - You cannot use magic if it requires more MP than maximum mp
        if (g_GameVariables->bINFHEALTH)
            g_GameData->Cloud->HP = g_GameData->Cloud->MaxHP;

        if (g_GameVariables->bINFMAGIC)
            g_GameData->Cloud->MP = g_GameData->Cloud->MaxMP;
	}
}