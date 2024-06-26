#pragma once
#include <Menu.h>
#include <Game.h>
#include <helper.h>

namespace DX11Base
{
    using namespace FF7Remake;

	namespace Styles 
    {
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

            if (ImGui::InputFloat("##atb1", &stats.ATB, 1.0f, 100.f, "%.2f"))
                bUpdateStats = true;
            ImGui::SameLine();
            if (ImGui::Button("MAX##ATB"))
            {
                stats.SetMaxATB();
                bUpdateStats = true;
            }
            ImGui::SameLine();
            ImGui::Text("ATB");

            if (ImGui::InputFloat("##limitbreak1", &stats.LimitBreak, 1.0f, 100.f, "%.2f"))
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
            AGameState* pGameState = AGame::gGameBase->GetGameState();
            if (!pGameState)
                return;

            static int selected_index{ 0 };
            static const char* stats_party[]{ "CLOUD", "PARTY SLOT 2", "PARTY SLOT 3", "PARTY SLOT 4", "PARTY SLOT 5" };
            ImGui::Combo("PARTY MEMBER", &selected_index, stats_party, IM_ARRAYSIZE(stats_party));
            ImGui::Separator();

            int index = (selected_index - 1);
            Widgets::StatsEditor(pGameState, index);
        }
    }

	namespace Tabs 
    {
        void TABplayer()
        {
            ImGui::Toggle("DEMI GOD", &AGame::bDemiGod);
            ImGui::Toggle("DEMI MANA", &AGame::bDemiGodMagic);
            ImGui::Toggle("MAX LIMIT", &AGame::bMaxLimit);
            ImGui::Toggle("MAX ATB", &AGame::bMaxATB);
            ImGui::Toggle("NO HP LOSS", &AGame::bNullDmg);
            ImGui::Toggle("NO MANA LOSS", &AGame::bNullMgk);
            ImGui::Toggle("NO ITEM LOSS", &AGame::bNullItem);
            ImGui::Toggle("XP MOD", &AGame::bXpFarm);

            if (ImGui::Toggle("MODIFY TIME SCALE", &AGame::bModTimeScale) && !AGame::bModTimeScale)
                AGame::fTimeScalar = 1.0f;
            if (AGame::bModTimeScale)
                ImGui::SliderFloat("##TIME SCALE", &AGame::fTimeScalar, 0.0f, 1.0f, "%.2f");
        }

        void TABitems()
        {
            auto pGameState = AGame::gGameBase->GetGameState();
            if (!pGameState)
                return;

            ImGui::BeginChild("##ITEMS_LIST", ImVec2(ImGui::GetContentRegionAvail().x - 5.f, 250.f), true);
            {
                AItem* _itemsList = pGameState->GetItems();
                for (int i = 0; i < 65; i++)
                {
                    AItem item = _itemsList[i];
                    if (item.Valid == -1)
                        break;

                    if (!item.IsItem())
                        continue;

                    ImGui::PushID(i);

                    if (ImGui::CollapsingHeader(std::to_string(i).c_str()))
                    {
                        ImGui::Text("ID: 0x%8X", (int*)&item.ID, 1, 0);
                        ImGui::InputInt("COUNT", (int*)&item.Count, 1, 0);
                    }

                    ImGui::PopID();
                }
            }
            ImGui::EndChild();
        }

        void TABmateria()
        {
            auto pGameState = AGame::gGameBase->GetGameState();
            if (!pGameState)
                return;

            ImGui::BeginChild("##MATERIA_LIST", ImVec2(ImGui::GetContentRegionAvail().x - 5.f, 250.f), true);
            {
                AMateria* _materiaList = pGameState->GetMateria();
                for (int i = 0; i < 1000; i++)
                {
                    AMateria materia = _materiaList[i];
                    if (materia.Index != i)
                        break;

                    ImGui::PushID(i);

                    if (ImGui::CollapsingHeader(std::to_string(materia.Index).c_str()))
                    {
                        ImGui::Text("ID: 0x%8X", materia.MateriaID, 1, 0);
                        ImGui::Text("NAME ID: %d", materia.NameID, 1, 0);
                        ImGui::InputInt("LEVEL", (int*)&materia.Level, 1, 0);
                        ImGui::InputInt("XP", &materia.TotalXP, 1, 0);
                    
                    }

                    ImGui::PopID();
                }
            }
            ImGui::EndChild();
        }

        void TABstats()
        {
            Stats::Stats();
        }

        void TABenemies()
        {

            ImGui::Toggle("STUPIFY", &AGame::bNoTargetAttack);
            ImGui::Toggle("NO DAMAGE", &AGame::bNullTargetDmg);
            ImGui::Toggle("AUTO STAGGER", &AGame::bTargetAlwaysStagger);
            ImGui::Toggle("1 HIT KILLS", &AGame::bKillTarget);
            ImGui::Toggle("MODIFY LEVEL", &AGame::bModTargetLevel);
            if (AGame::bModTargetLevel)
                ImGui::InputInt("LEVEL", &AGame::iLevelScalar);

        }
        
        void TABoptions()
        {
            ImGui::Text("BASE MENU (PREVIEW)");
            ImGui::Text("BUILD VERSION: v1.2");
            ImGui::Text("BUILD DATE: 5/22/2024");
            ImGui::Checkbox("PAUSE GAME", &AGame::bPauseGame);
            ImGui::Checkbox("SHOW IMGUI DEMO", &g_Engine->m_ShowDemo);
#if _DEBUG
            //  ImGui::Checkbox("SHOW CONSOLE", &g_Console->m_ShowConsole);
#endif
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            if (ImGui::Button("UNHOOK DLL", ImVec2(ImGui::GetWindowContentRegionWidth() - 3, 20))) 
            {
                g_Engine->m_ShowMenu = false;
                g_bKillswitch = true;
            }
        }
	}

    //----------------------------------------------------------------------------------------------------
    //										MENU
    //-----------------------------------------------------------------------------------

	void Menu::Draw()
	{
        if (!g_Engine->m_ShowDemo)
            Styles::InitStyle();

        if (g_Engine->m_ShowMenu)
            Menu::MainMenu();

		if (g_Engine->m_ShowHud)
            Menu::HUD();

		if (g_Engine->m_ShowDemo)
			ImGui::ShowDemoWindow();
	}

    void Menu::MainMenu()
    {
        if (!ImGui::Begin("Final Fantasy 7 Remake", &g_Engine->m_ShowMenu, 96 | ImGuiWindowFlags_NoTitleBar))
        {
            ImGui::End();
            return;
        }


        if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
        {
            if (ImGui::BeginTabItem("PLAYER"))
            {
                Tabs::TABplayer();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("ITEMS"))
            {
                Tabs::TABitems();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("MATERIA"))
            {
                Tabs::TABmateria();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("STATS"))
            {
                Tabs::TABstats();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("ENEMIES"))
            {
                Tabs::TABenemies();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("OPTIONS"))
            {
                Tabs::TABoptions();
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
        if (AGame::bDemiGod)
            AGame::Patches::RefillCloudHP();

        if (AGame::bDemiGodMagic)
            AGame::Patches::RefillCloudMP();

        if (AGame::bMaxLimit)
            AGame::Patches::CloudMaxLimit();

        if (AGame::bMaxATB)
            AGame::Patches::CloudMaxATB();
	}

    //----------------------------------------------------------------------------------------------------
    //										GUI
    //-----------------------------------------------------------------------------------

    void GUI::TextCentered(const char* pText)
    {
        ImVec2 textSize = ImGui::CalcTextSize(pText);
        ImVec2 windowSize = ImGui::GetWindowSize();
        ImVec2 textPos = ImVec2((windowSize.x - textSize.x) * 0.5f, (windowSize.y - textSize.y) * 0.5f);
        ImGui::SetCursorPos(textPos);
        ImGui::Text("%s", pText);
    }

    //  @ATTN: max buffer is 256chars
    void GUI::TextCenteredf(const char* pText, ...)
    {
        va_list args;
        va_start(args, pText);
        char buffer[256];
        vsnprintf(buffer, sizeof(buffer), pText, args);
        va_end(args);

        TextCentered(buffer);
    }

    void GUI::DrawText_(ImVec2 pos, ImColor color, const char* pText, float fontSize)
    {
        ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), fontSize, pos, color, pText, pText + strlen(pText), 800, 0);
    }

    //  @ATTN: max buffer is 256chars
    void GUI::DrawTextf(ImVec2 pos, ImColor color, const char* pText, float fontSize, ...)
    {
        va_list args;
        va_start(args, fontSize);
        char buffer[256];
        vsnprintf(buffer, sizeof(buffer), pText, args);
        va_end(args);

        DrawText_(pos, color, buffer, fontSize);
    }

    void GUI::DrawTextCentered(ImVec2 pos, ImColor color, const char* pText, float fontSize)
    {
        float textSize = ImGui::CalcTextSize(pText).x;
        ImVec2 textPosition = ImVec2(pos.x - (textSize * 0.5f), pos.y);
        DrawText_(textPosition, color, pText, fontSize);
    }

    //  @ATTN: max buffer is 256chars
    void GUI::DrawTextCenteredf(ImVec2 pos, ImColor color, const char* pText, float fontSize, ...)
    {
        va_list args;
        va_start(args, fontSize);
        char buffer[256];
        vsnprintf(buffer, sizeof(buffer), pText, args);
        va_end(args);

        DrawTextCentered(pos, color, pText, fontSize);
    }

    //  @ATTN: max buffer is 256chars
    void GUI::DrawTextWindow(ImVec2 pos, const char* fmt, ...)
    {

        va_list args;
        va_start(args, fmt);
        char buffer[256];
        vsnprintf(buffer, sizeof(buffer), fmt, args);
        va_end(args);

        ImGui::SetNextWindowPos(pos);
        if (!ImGui::Begin(std::string("##").append(buffer).c_str(), 0, 103))
        {
            ImGui::End();
            return;
        }

        ImGui::Text("%s", buffer);

        ImGui::End();
    }
}