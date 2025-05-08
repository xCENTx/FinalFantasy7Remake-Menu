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
        void WelcomeMessage()
        {
            static ImVec2 window_size;

            ImGuiViewport* pViewport = ImGui::GetMainViewport();
            if (!pViewport)
                return;

            ImVec2 client_rect = pViewport->WorkSize;
            ImVec2 center = { client_rect.x * .5f - window_size.x * .5f, client_rect.y * .5f - window_size.y * .5f };
            ImGui::SetNextWindowPos({ center });
            if (!ImGui::Begin("FFVii Internal Launch Window", 0, 103))
            {
                ImGui::End();
                return;
            }

            GUI::TextCentered("FINAL FANTASY VII REMAKE INTERNAL MENU");
            ImGui::Text("PRESS [INSERT] OR [L3 + R3] TO SHOW THE MENU");
            ImGui::Separator();
            ImGui::TextColored(ImColor(255, 0, 0, 255), "MENU v1.2 | Released: May 23, 2024");
            ImGui::Text("https://github.com/xCENTx/FinalFantasy7Remake-Menu");  //  @TODO: copy to clipboard

            window_size = ImGui::GetWindowSize();

            ImGui::End();
        }

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

            GUI::TextCentered("PLAYER STATS");
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

        void TargetInfo()
        {
            static ImVec2 window_size;
           
            ImGuiViewport* pViewport = ImGui::GetMainViewport();
            if (!pViewport || !AGame::sTargetEntity.bValid)
                return;

            ImVec2 client_rect = pViewport->WorkSize;
            ImVec2 top_center = { ( client_rect.x * .5f ) - window_size.x * .5f , 0.0f };
            ImGui::SetNextWindowPos(top_center);
            
            //  if (window_size)
            //  ImGui::SetNextWindowSize(window_size);  //  first pass will be empty
            if (!ImGui::Begin("Target Info", 0, 96 | ImGuiWindowFlags_NoTitleBar) || !AGame::sTargetEntity.bValid)
            {
                window_size = { 0.f, 0.f };
                ImGui::End();
                return;
            }
            GUI::TextCenteredf("Level: %d", AGame::sTargetEntity.Level);
            GUI::TextCenteredf("HP: %d / %d", AGame::sTargetEntity.HP, AGame::sTargetEntity.HPMax);
            GUI::TextCenteredf("STAGGER: %.1f / %.1f", AGame::sTargetEntity.Stagger, AGame::sTargetEntity.StaggerMax);
            GUI::TextCenteredf("SPECIAL ATTACK: %.1f / %.1f", AGame::sTargetEntity.SpAtkTime, AGame::sTargetEntity.SpAtkTimeMax);
            GUI::TextCenteredf("ATTACK: %d", AGame::sTargetEntity.Attack);
            GUI::TextCenteredf("MAGIC ATTACK: %d", AGame::sTargetEntity.MagicAtk);
            GUI::TextCenteredf("DEFENSE: %d", AGame::sTargetEntity.Defense);
            GUI::TextCenteredf("MAGIC DEFENSE: %d", AGame::sTargetEntity.MagicDefense);
            //  ImGui::ProgressBar((float)(AGame::sTargetEntity.HP * AGame::sTargetEntity.HPMax), { (float)AGame::sTargetEntity.HP , (float)AGame::sTargetEntity.HPMax});



            window_size = ImGui::GetWindowSize();

            ImGui::End();
        }
    }

	namespace Tabs 
    {
        void TABplayer()
        {
            // Select Character
            static const char* selectables_names[]{ "CLOUD", "BARRET", "TIFA", "AERITH", "RED Xiii", "ALL", "RESET" };
            if (ImGui::BeginTable("SELECTION", 7, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders))
            {
                for (int i = 0; i < 7; i++)
                {
                    const char* name_entry = selectables_names[i];
                    ImGui::TableNextColumn();
                    if (ImGui::Selectable(name_entry, &AGame::bSelectedPlayer[i]))
                    {
                        AGame::iSelectedPlayerIndex = i;

                        if (i == 5 || i == 6)
                        {
                            bool res = AGame::bSelectedPlayer[i];
                            switch (i)
                            {
                            case 5:
                                for (int i = 0; i < 6; i++)
                                    AGame::bSelectedPlayer[i] = res;
                                break;

                            case 6:
                                for (int i = 0; i < 7; i++)
                                    AGame::bSelectedPlayer[i] = false;
                                AGame::bSelectedPlayer[0] = true;
                                break;
                            }
                        }
                    }
                }

                ImGui::EndTable();
            }


            //  ImGui::RadioButton
            GUI::Toggle("DEMI GOD", &AGame::bDemiGod);
            GUI::Toggle("DEMI MANA", &AGame::bDemiGodMagic);
            GUI::Toggle("MAX LIMIT", &AGame::bMaxLimit);
            GUI::Toggle("MAX ATB", &AGame::bMaxATB);
            GUI::Toggle("NO HP LOSS", &AGame::bNullDmg);
            GUI::Toggle("NO MANA LOSS", &AGame::bNullMgk);
            GUI::Toggle("NO ITEM LOSS", &AGame::bNullItem);
            GUI::Toggle("XP MOD", &AGame::bXpFarm);

            if (GUI::Toggle("MODIFY TIME SCALE", &AGame::bModTimeScale) && !AGame::bModTimeScale)
                AGame::fTimeScalar = 1.0f;
            if (AGame::bModTimeScale)
            {
                ImGui::SameLine();
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 5.0f);
                if(ImGui::Button("x2"))
                    AGame::fTimeScalar = 2.0f;
                ImGui::SameLine();
                if (ImGui::Button("x3"))
                    AGame::fTimeScalar = 3.0f;
                ImGui::SameLine();
                if (ImGui::Button("x5"))
                    AGame::fTimeScalar = 5.0f;
                ImGui::SameLine();
                if (ImGui::Button("x10"))
                    AGame::fTimeScalar = 10.0f;

                ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
                ImGui::SliderFloat("##TIME SCALE", &AGame::fTimeScalar, 0.0f, 1.0f, "%.2f");
            }
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
                    std::string nameEntry = "[" + std::to_string(i) + "] " + item.GetName(i);
                    if (!ImGui::CollapsingHeader(nameEntry.c_str()))
                    {
                        ImGui::PopID();
                        continue;
                    }
                    
                    //  ImGui::Text("ID: 0x%8X", item.ID, 1, 0);
                    if (ImGui::InputInt("COUNT", &item.Count, 1, 0))
                        _itemsList[i].Count = item.Count;

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

                    std::string nameEntry = "[" + std::to_string(materia.Level) + "] " + materia.GetName();
                    if (!ImGui::CollapsingHeader(nameEntry.c_str()))
                    {
                        ImGui::PopID();
                        continue;
                    }

                    //  ImGui::Text("ID: 0x%8X", materia.MateriaID, 1, 0);
                    ImGui::Text("NAME ID: %d", materia.NameID, 1, 0);

                    int level = materia.Level;
                    if (ImGui::InputInt("LEVEL", &level, 1, 0))
                        _materiaList[i].Level = (__int8)level;
                        
                    if (ImGui::InputInt("XP", &materia.TotalXP, 1, 0))
                        _materiaList[i].TotalXP = materia.TotalXP;

                    ImGui::Separator();
                    

                    ImGui::PopID();
                }
            }
            ImGui::EndChild();
        }

        void TABstats()
        {
            AGameState* pGameState = AGame::gGameBase->GetGameState();
            if (!pGameState)
                return;

            static int selected_index{ 0 };
            static const char* party_names[]{ "CLOUD", "BARRET", "TIFA", "AERITH", "RED Xiii" };
            ImGui::Combo("PARTY MEMBER", &selected_index, party_names, IM_ARRAYSIZE(party_names));
            ImGui::Separator();

            int index = (selected_index - 1);
            Widgets::StatsEditor(pGameState, index);
        }

        void TABenemies()
        {

            //  GUI::Toggle("STUPIFY", &AGame::bNoTargetAttack);
            GUI::Toggle("NO DAMAGE", &AGame::bNullTargetDmg);
            GUI::Toggle("AUTO STAGGER", &AGame::bTargetAlwaysStagger);
            GUI::Toggle("1 HIT KILLS", &AGame::bKillTarget);
            GUI::Toggle("MODIFY LEVEL", &AGame::bModTargetLevel);
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

            if (ImGui::Button("UNHOOK DLL", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20))) 
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


    static ImVec2 gui_pos{0, 0};
    static ImVec2 gui_size{0, 0};
    void Menu::MainMenu()
    {

        if (!ImGui::Begin("Final Fantasy 7 Remake", &g_Engine->m_ShowMenu, 96 | ImGuiWindowFlags_NoTitleBar))
        {
            ImGui::End();
            return;
        }

        //  shrouded background
        auto draw = ImGui::GetWindowDrawList();
        draw->AddRectFilled(gui_pos, { gui_pos.x + gui_size.x, gui_pos.y + gui_size.y }, ImColor(0.0f, 0.0f, 0.0f, .5f), 0.f);
        
        
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


        gui_pos = ImGui::GetWindowPos();
        gui_size = ImGui::GetWindowSize();
        ImGui::End();
	}

	void Menu::HUD()
	{
        //  Welcome Message
        if (g_Engine->m_ShowWelcome)
            Widgets::WelcomeMessage();


        //  Target Info
        // @TODO: ImGui annoying navigation menu needs to be removed
        //  Widgets::TargetInfo();
	}

	void Menu::Loops()
	{
        if (AGame::bDemiGod)
        {
            switch (AGame::iSelectedPlayerIndex)
            {
                case 6: AGame::Patches::RefillPartyHP(); break;
                default: AGame::Patches::RefillPlayerHP(AGame::iSelectedPlayerIndex); break;
            }

        }

        if (AGame::bDemiGodMagic)
        {
            switch (AGame::iSelectedPlayerIndex)
            {
                case 6: AGame::Patches::RefillPartyMP(); break;
                default: AGame::Patches::RefillPlayerMP(AGame::iSelectedPlayerIndex); break;
            }
        }

        if (AGame::bMaxATB)
        {

            switch (AGame::iSelectedPlayerIndex)
            {
                case 6: AGame::Patches::PartyMaxATB(); break;
                default: AGame::Patches::PlayerMaxATB(AGame::iSelectedPlayerIndex); break;
            }
        }

        if (AGame::bMaxLimit)
        {
            switch (AGame::iSelectedPlayerIndex)
            {
                case 6: AGame::Patches::PartyMaxLimit(); break;
                default: AGame::Patches::PlayerMaxLimit(AGame::iSelectedPlayerIndex); break;
            }
        }
	}

    //----------------------------------------------------------------------------------------------------
    //										GUI
    //-----------------------------------------------------------------------------------

    void GUI::TextCentered(const std::string& pText)
    {
        ImVec2 textSize = ImGui::CalcTextSize(pText.c_str());
        ImVec2 windowSize = ImGui::GetWindowSize();
        ImVec2 textPos = ImVec2((windowSize.x - textSize.x) * 0.5f, (windowSize.y - textSize.y) * 0.5f);
        ImGui::SetCursorPos({textPos.x, ImGui::GetCursorPosY()});
        ImGui::Text("%s", pText.c_str());
    }

    void GUI::TextCenteredf(const std::string pText, ...)
    {
        float windowWidth = ImGui::GetWindowSize().x;
        float textWidth = ImGui::CalcTextSize(pText.c_str()).x;
        ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
        va_list args;
        va_start(args, pText);
        ImGui::TextV(pText.c_str(), args);
        va_end(args);
    }

    void GUI::Tooltip(const std::string& tip)
    {
        if (!ImGui::IsItemHovered())
            return;

        ImGui::SetTooltip(tip.c_str());
    }

    bool GUI::Toggle(const std::string& label, bool* v)
    {
        using namespace ImGui;

        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label.c_str());
        const ImVec2 label_size = CalcTextSize(label.c_str(), NULL, true);

        const float square_sz = GetFrameHeight();
        ImVec2 pos = window->DC.CursorPos;

        const ImRect total_bb(pos, pos + ImVec2(square_sz + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), label_size.y + style.FramePadding.y * 2.0f));
        ItemSize(total_bb, style.FramePadding.y);
        if (!ItemAdd(total_bb, id))
            return false;

        bool hovered, held;
        bool pressed = ButtonBehavior(total_bb, id, &hovered, &held);
        if (pressed)
        {
            *v = !(*v);
            MarkItemEdited(id);
        }


        //  COLOR PROPERTIES
        ImU32 uncheck_col = GetColorU32(ImGuiCol_FrameBg);
        // ImColor uncheck_col = ImColor(42, 42, 42, 255);// GetColorU32(ImGuiCol_FrameBg);
        ImU32 circle_col = GetColorU32(ImGuiCol_NavWindowingDimBg);
        //ImU32 check_col = GetColorU32(ImGuiCol_CheckMark);
        ImU32 check_col = ImColor(42, 42, 42, 255);;

        //  Position
        const ImRect check_bb(pos, ImVec2(pos.x, pos.y) + ImVec2(square_sz * 1.5, square_sz * 0.8));
        RenderNavHighlight(total_bb, id);
        auto col = GetColorU32((held && hovered) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
        ImVec2 UpperLeft(check_bb.GetTL().x, check_bb.GetTL().y + 2.f);
        ImVec2 LowerRight(check_bb.GetBR().x, check_bb.GetBR().y + 2.f);
        ImRect newRect(UpperLeft, LowerRight);
        window->DrawList->AddRectFilled(newRect.Min, newRect.Max, uncheck_col, 10); //  Color
        ImVec2 sUpperLeft(check_bb.GetTL().x, check_bb.GetTL().y + 2.f);
        ImVec2 sLowerRight(check_bb.GetCenter().x, check_bb.GetBR().y + 2.f);
        ImRect sRect(sUpperLeft, sLowerRight);
        window->DrawList->AddRectFilled(sRect.Min, sRect.Max, circle_col, 10);  // COLOR

        //reset
        if (*v) 
        {
            window->DrawList->AddRectFilled(ImVec2(newRect.Min.x - 1.f, newRect.Min.y - 1.f), ImVec2(newRect.Max.x + .5f, newRect.Max.y + 1.f), check_col, 10); //  COLOR
            ImVec2 tUpperLeft(check_bb.GetCenter().x, check_bb.GetTL().y + 2.f);
            ImVec2 tLowerRight(check_bb.GetBR().x, check_bb.GetBR().y + 2.f);
            ImRect tRect(tUpperLeft, tLowerRight);
            window->DrawList->AddRectFilled(tRect.Min, tRect.Max, circle_col, 10);
        }

        if (label_size.x > 0.0f)
            RenderText(ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x, check_bb.Min.y + style.FramePadding.y), label.c_str());

        IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.ItemFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
        return pressed;
    }

    void GUI::DrawText_(const ImVec2& pos, const ImColor& color, const std::string& text, const float& szFont)
    {
        ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), szFont, pos, color, text.c_str(), text.c_str() + text.size(), 800.f, nullptr);
    }

    void GUI::DrawBGText(const ImVec2& pos, const ImColor& color, const std::string& text, const ImColor& background, const float& szFont)
    {
        auto pFont = ImGui::GetFont();
        const ImVec2& textSize = ImGui::CalcTextSize(text.c_str());
        ImRect textRect = ImRect(pos, pos + textSize);
        if (szFont > 0.f)
        {
            const ImVec2& scaledTextSize = ImVec2(textSize.x * szFont / pFont->FontSize, szFont);
            ImVec2 scaledTextPos = ImVec2(pos.x - (scaledTextSize.x * .5f), pos.y);
        }
        ImGui::GetWindowDrawList()->AddRectFilled(textRect.Min, textRect.Max, background);
        DrawText_(textRect.Min, color, text, szFont);
    }

    void GUI::DrawBorderText(const ImVec2& pos, const ImColor& color, const std::string& text, const ImColor& border, const float& szFont)
    {
        auto pFont = ImGui::GetFont();
        const ImVec2& textSize = ImGui::CalcTextSize(text.c_str());
        ImRect textRect = ImRect(pos, pos + textSize);
        if (szFont > 0.f)
        {
            const ImVec2& scaledTextSize = ImVec2(textSize.x * szFont / pFont->FontSize, szFont);
            ImVec2 scaledTextPos = ImVec2(pos.x - (scaledTextSize.x * .5f), pos.y);
            textRect = (ImRect(scaledTextPos, scaledTextPos + scaledTextSize));
        }
        ImGui::GetWindowDrawList()->AddRect(textRect.Min, textRect.Max, border);
        DrawText_(textRect.Min, color, text, szFont);
    }

    void GUI::DrawTextCentered(const ImVec2& pos, const ImColor& color, const std::string& text, const float& szFont)
    {
        const ImVec2& textSize = ImGui::CalcTextSize(text.c_str());
        ImVec2 textPosition = ImVec2(pos.x - (textSize.x * 0.5f), pos.y);
        if (szFont <= 0.f)
        {
            DrawText_(textPosition, color, text, szFont);
            return;
        }

        auto pFont = ImGui::GetFont();
        ImVec2 scaledTextSize = ImVec2(textSize.x * szFont / pFont->FontSize, szFont);
        ImVec2 scaledTextPos = ImVec2(pos.x - (scaledTextSize.x * .5f), pos.y);
        DrawText_(scaledTextPos, color, text, szFont);
    }

    void GUI::DrawBGTextCentered(const ImVec2& pos, const ImColor& color, const std::string& text, const ImColor& background, const float& szFont)
    {
        const ImVec2& textSize = ImGui::CalcTextSize(text.c_str());
        ImVec2 textPosition = ImVec2(pos.x - (textSize.x * 0.5f), pos.y);
        if (szFont <= 0.f)
        {
            DrawBGText(textPosition, color, text, background, szFont);
            return;
        }

        auto pFont = ImGui::GetFont();
        ImVec2 scaledTextSize = ImVec2(textSize.x * szFont / pFont->FontSize, szFont);
        ImVec2 scaledTextPos = ImVec2(pos.x - (scaledTextSize.x * .5f), pos.y);
        ImGui::GetWindowDrawList()->AddRectFilled(scaledTextPos, scaledTextPos + scaledTextSize, background);
        DrawText_(scaledTextPos, color, text, szFont);
    }

    void GUI::DrawBorderTextCentered(const ImVec2& pos, const ImColor& color, const std::string& text, const ImColor& border, const float& szFont)
    {
        const ImVec2& textSize = ImGui::CalcTextSize(text.c_str());
        ImVec2 textPosition = ImVec2(pos.x - (textSize.x * 0.5f), pos.y);
        if (szFont <= 0.f)
        {
            DrawBorderText(textPosition, color, text, border, szFont);
            return;
        }

        auto pFont = ImGui::GetFont();
        ImVec2 scaledTextSize = ImVec2(textSize.x * szFont / pFont->FontSize, szFont);
        ImVec2 scaledTextPos = ImVec2(pos.x - (scaledTextSize.x * .5f), pos.y);
        ImGui::GetWindowDrawList()->AddRect(scaledTextPos, scaledTextPos + scaledTextSize, border);
        DrawText_(scaledTextPos, color, text, szFont);
    }

    void GUI::Line(const ImVec2& posA, const ImVec2& posB, const ImColor& color, const float& thickness)
    {
        ImGui::GetWindowDrawList()->AddLine(posA, posB, color, thickness);
    }

    void GUI::Circle(const ImVec2& pos, const ImColor& color, const float& radius, const float& thickness, const float& segments)
    {
        ImGui::GetWindowDrawList()->AddCircle(pos, radius, color, segments, thickness);
    }

    void GUI::CleanLine(const ImVec2& posA, const ImVec2& posB, const ImColor& color, const float& thickness)
    {
        Line(posA, posB, ImColor(0.0f, 0.0f, 0.0f, color.Value.w), (thickness + 0.25));
        Line(posA, posB, ImColor(1.0f, 1.0f, 1.0f, color.Value.w), (thickness + 0.15));
        Line(posA, posB, color, thickness);
    }

    void GUI::CleanCircle(const ImVec2& pos, const ImColor& color, const float& radius, const float& thickness, const float& segments)
    {
        Circle(pos, ImColor(0.0f, 0.0f, 0.0f, color.Value.w), radius, thickness, segments);
        Circle(pos, ImColor(1.0f, 1.0f, 1.0f, color.Value.w), radius, thickness, segments);
        Circle(pos, color, radius, thickness, segments);
    }
}