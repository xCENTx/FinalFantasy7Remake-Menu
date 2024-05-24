#include "Menu.hpp"


static const char* stats_party[]{ "CLOUD", "PARTY SLOT 2", "PARTY SLOT 3", "PARTY SLOT 4", "PARTY SLOT 5"};

namespace FF7Remake 
{

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
        }
	}

    namespace Widgets
    {
        void StatsEditor(AGameState* pGameState, int index)
        {
            if (!pGameState)
                return;

            APlayerStats stats;
            APlayerAttributes attributes;
            bool bUpdateStats{ false };
            bool bUpdateAttributes{ false };
            if (index == -1)
            {
                stats = pGameState->GetCloudStats();
                attributes = pGameState->GetCloudAttributes();
            }
            else
            {
                stats = pGameState->GetPlayerStats(index);
                attributes = pGameState->GetPlayerAttributes(index + 1);
            }

            ImGui::TextCentered("PLAYER STATS");
            ImGui::Spacing();

            if (ImGui::InputInt("##HP1", &stats.HP))
                bUpdateStats = true;
            ImGui::SameLine();
            if (ImGui::Button("MAX##HP"))
            {
                stats.RefillHP();
                bUpdateStats = true;
            }
            ImGui::SameLine();
            ImGui::Text("HP (%d/%d)", stats.HP, stats.MaxHP);

            if (ImGui::InputInt("##MP1", &stats.MP))
                bUpdateStats = true;
            ImGui::SameLine();
            if (ImGui::Button("MAX##MP"))
            {
                stats.RefillMana();
                bUpdateStats = true;
            }
            ImGui::SameLine();
            ImGui::Text("MP (%d/%d)", stats.MP, stats.MaxMP);

            if (ImGui::InputFloat("##atb1", &stats.ATB))
                bUpdateStats = true;
            ImGui::SameLine();
            if (ImGui::Button("MAX##ATB"))
            {
                stats.SetMaxATB();
                bUpdateStats = true;
            }
            ImGui::SameLine();
            ImGui::Text("ATB");

            if (ImGui::InputFloat("##limitbreak1", &stats.LimitBreak))
                bUpdateStats = true;
            ImGui::SameLine();
            if (ImGui::Button("MAX##Limit"))
            {
                stats.SetMaxLimit();
                bUpdateStats = true;
            }
            ImGui::SameLine();
            ImGui::Text("LimitBreak");

            if (ImGui::InputInt("##experience", &stats.XP))
                bUpdateStats = true;
            ImGui::SameLine();
            ImGui::Text("XP");

            if (ImGui::InputInt("##Attack1", &stats.Attack))
                bUpdateStats = true;
            ImGui::SameLine();
            ImGui::Text("Attack");

            if (ImGui::InputInt("##MagicAttack1", &stats.MagicAtk))
                bUpdateStats = true;
            ImGui::SameLine();
            ImGui::Text("MagicAttack");

            if (ImGui::InputInt("##Defense1", &stats.Defense))
                bUpdateStats = true;
            ImGui::SameLine();
            ImGui::Text("Defense");

            if (ImGui::InputInt("##MagicDefense1", &stats.MagicDef))
                bUpdateStats = true;
            ImGui::SameLine();
            ImGui::Text("MagicDefense");

            if (ImGui::InputInt("##Strength1", &attributes.Strength))
                bUpdateAttributes = true;
            ImGui::SameLine();
            ImGui::Text("Strength");

            if (ImGui::InputInt("##Magic1", &attributes.Magic))
                bUpdateAttributes = true;
            ImGui::SameLine();
            ImGui::Text("Magic");

            if (ImGui::InputInt("##Vitality1", &attributes.Vitality))
                bUpdateAttributes = true;
            ImGui::SameLine();
            ImGui::Text("Vitality");

            if (ImGui::InputInt("##Spirit1", &attributes.Spirit))
                bUpdateAttributes = true;
            ImGui::SameLine();
            ImGui::Text("Spirit");

            if (ImGui::InputInt("##Luck1", &stats.Luck))
                bUpdateStats = true;
            ImGui::SameLine();
            ImGui::Text("Luck");

            if (bUpdateStats)
            {
                if (index == -1)
                    pGameState->SetCloudStats(stats);
                else
                    pGameState->SetPlayerStats(index, stats);
            }

            if (bUpdateAttributes)
            {
                if (index == -1)
                    pGameState->SetCloudAttributes(attributes);
                else
                    pGameState->SetPlayerAttributes(index, attributes);
            }
        }
    }

    namespace Stats 
    {
        void Stats()
        {
            AGameState* pGameState = CGlobal::gGameBase->GetGameState();
            if (!pGameState)
                return;

            static int selected_index{ 0 };
            ImGui::Combo("PARTY MEMBER", &selected_index, stats_party, IM_ARRAYSIZE(stats_party));
            ImGui::Separator();

            int index = (selected_index - 1);
            //  if (selected_index == 0)
            //      index = -1;
            //  else
            //      index = selected_index - 1;

            Widgets::StatsEditor(pGameState, index);
        }
    }

	namespace Tabs 
    {
        void TABMain()
        {
            ImGui::TextCentered("CHEATS");
            ImGui::Toggle("NULLIFY DAMAGE", &g_GameData->bNullDmg);
            ImGui::Toggle("DEMI GOD", &g_GameData->bDemiGod);
            ImGui::Toggle("DEMI GOD MAGIC", &g_GameData->bDemiGodMagic);
            ImGui::Toggle("ALWAYS LIMIT", &g_GameData->bMaxLimit);
            ImGui::Toggle("ALWAYS ATB", &g_GameData->bMaxATB);

            ImGui::Toggle("PAUSE GAME w/ MENU", &g_GameData->bPauseGame);
            if (ImGui::Toggle("MODIFY TIME SCALE", &g_GameData->bModTimeScale) && !g_GameData->bModTimeScale)
                g_GameData->fTimeScale = 1.0f;
            if (g_GameData->bModTimeScale)
                ImGui::SliderFloat("TIME SCALE", &g_GameData->fTimeScale, 0.0f, 1.0f, "%.2f");

        }

        void TABStats()
        {
            Stats::Stats();
        }

        void TABAbout()
        {
            ImGui::Text("BASE MENU (PREVIEW)");
            ImGui::Text("BUILD VERSION: v1.2");
            ImGui::Text("BUILD DATE: 5/22/2024");
            ImGui::Checkbox("SHOW IMGUI DEMO", &g_GameData->m_ShowDemo);
#if _DEBUG
            ImGui::Checkbox("SHOW CONSOLE", &g_Console->m_ShowConsole);
#endif
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            if (ImGui::Button("UNHOOK DLL", ImVec2(ImGui::GetWindowContentRegionWidth() - 3, 20))) 
            {
                g_GameData->m_ShowMenu = false;
                og_Killswitch = true;
            }
        }
	}

	void Menu::Draw()
	{
        if (!g_GameData->m_ShowDemo)
            Styles::InitStyle();

        if (g_GameData->m_ShowMenu)
            MainMenu();

		if (g_GameData->m_ShowHud)
			HUD();

		if (g_GameData->m_ShowDemo)
			ImGui::ShowDemoWindow();
	}

	void Menu::MainMenu()
	{
        if (!ImGui::Begin("Final Fantasy 7 Remake", &g_GameData->m_ShowMenu, 96 | ImGuiWindowFlags_NoTitleBar))
        {
            ImGui::End();
            return;
        }


        if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
        {
            if (ImGui::BeginTabItem("MAIN"))
            {
                Tabs::TABMain();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("STATS"))
            {
                Tabs::TABStats();
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

	void Menu::HUD()
	{
        ImGui::SetNextWindowPos(ImVec2(10, 10));
        if (!ImGui::Begin("FFVii Internal Launch Window", 0, 103))
        {
            ImGui::End();
            return;
        }
        
        ImGui::Text("FINAL FANTASY VII INTERNAL MENU LOADED");
        ImGui::Text("PRESS [INSERT] OR [L3 + R3] TO SHOW THE MENU");
        ImGui::Separator();
        ImGui::TextColored(ImColor(255, 0, 0, 255), "MENU v1.2 | Released: May 23, 2024");

        ImGui::End();
	}

	void Menu::Loops()
	{
        if (g_GameData->bDemiGod)
            Patches::RefillCloudHP();

        if (g_GameData->bDemiGodMagic)
            Patches::RefillCloudMP();

        if (g_GameData->bMaxLimit)
            Patches::CloudMaxLimit();

        if (g_GameData->bMaxATB)
            Patches::CloudMaxATB();
	}
}