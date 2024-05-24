#pragma once
#include "helper.h"
#include "Console.hpp"
#include "Game.hpp"
#include "D3D11Window.hpp"
#include "Hooking.hpp"
#include "Menu.hpp"

void BackgroundWorker()
{
    using namespace FF7Remake;
    while (og_Running)
    {
        g_Menu->Loops();

        if (og_Killswitch)
        {
            g_Hooking->Shutdown();

            g_Hooking.release();
            g_Menu.release();
            g_D3D11Window.release();
            g_GameData.release();

            og_Running = false;
        }

        std::this_thread::sleep_for(1ms);
        std::this_thread::yield();
    }
    return;
}

DWORD WINAPI MainThread()
{
    using namespace FF7Remake;
    g_Console = std::make_unique<Console>();
    g_GameData = std::make_unique<GameData>();
    g_D3D11Window = std::make_unique<D3D11Window>();
    g_Hooking = std::make_unique<Hooking>();
    g_Menu = std::make_unique<Menu>();
    

    g_Console->InitializeConsole("Final Fantasy 7 Remake : Debug Console", false);      //  initialize console without menu gui
    g_GameData->Init();                                                                 //  Get Process Information
    g_Hooking->Initialize();                                                            //  Hook Functions

    std::thread UPDATE(BackgroundWorker);

    //  MAIN LOOP
    static int LastTick{ 0 };
    while (og_Running)
    {
        if (Console::m_bGUI)
        {
            if ((GetAsyncKeyState(VK_INSERT) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                //  Hide our info message
                if (g_GameData->m_ShowHud == TRUE)
                    g_GameData->m_ShowHud = FALSE;

                //  Show / Hide Menu
                g_GameData->m_ShowMenu ^= 1;

                LastTick = GetTickCount64();
            }
        }

        if (!Console::m_bGUI)
        {
            //  Adjust Console Verbosity
            if ((GetAsyncKeyState(VK_NUMPAD0) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                g_Console->m_bVerbose ^= 1;
                LastTick = GetTickCount64();

                Console::Log("[+] [Console::Verbose] %d\n", g_Console->m_bVerbose);
            }

            //  Set No Damage Mod
            if ((GetAsyncKeyState(VK_NUMPAD1) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                g_GameData->bNullDmg ^= 1;
                LastTick = GetTickCount64();

                Console::Log("[+] [Patch::NullDmg] %d\n", g_GameData->bNullDmg);
            }

            //  Set No Mana Use Mod
            if ((GetAsyncKeyState(VK_NUMPAD2) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                g_GameData->bNullMgk ^= 1;
                LastTick = GetTickCount64();

                Console::Log("[+] [Patch::NullMana] %d\n", g_GameData->bNullMgk);
            }

            //  Set No Item Use Mod
            if ((GetAsyncKeyState(VK_NUMPAD3) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                g_GameData->bNullItem ^= 1;
                LastTick = GetTickCount64();

                Console::Log("[+] [Patch::NullItem] %d\n", g_GameData->bNullItem);
            }

            //  Set Max ATB Mod
            if ((GetAsyncKeyState(VK_NUMPAD4) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                g_GameData->bMaxATB ^= 1;
                LastTick = GetTickCount64();

                Console::Log("[+] [Patch::MaxATB] %d\n", g_GameData->bMaxATB);
            }
            
            //  Set Max Limit Mod
            if ((GetAsyncKeyState(VK_NUMPAD5) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                g_GameData->bMaxLimit ^= 1;
                LastTick = GetTickCount64();

                Console::Log("[+] [Patch::MaxLimit] %d\n", g_GameData->bMaxLimit);
            }

            //  Set Target Doesn't Attack
            if ((GetAsyncKeyState(VK_NUMPAD6) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                g_GameData->bNoTargetAttack ^= 1;
                LastTick = GetTickCount64();

                Console::Log("[+] [Patch::TargetNoAttack] %d\n", g_GameData->bNoTargetAttack);
            }

            //  Set Target Takes No Damage
            if ((GetAsyncKeyState(VK_NUMPAD7) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                g_GameData->bNullTargetDmg ^= 1;
                LastTick = GetTickCount64();

                Console::Log("[+] [Patch::TargetTakesNoDamage] %d\n", g_GameData->bNullTargetDmg);
            }

            //  Set Target Always Stagger
            if ((GetAsyncKeyState(VK_NUMPAD8) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                g_GameData->bTargetAlwaysStagger ^= 1;
                LastTick = GetTickCount64();

                Console::Log("[+] [Patch::TargetAlwaysStagger] %d\n", g_GameData->bTargetAlwaysStagger);
            }

            //  Set Kill Target
            //  Set Xp Farm
            if ((GetAsyncKeyState(VK_NUMPAD9) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                //  g_GameData->bNullTargetDmg = false;
                //  g_GameData->bTargetAlwaysStagger = false;
                //  g_GameData->bKillTarget ^= 1;
                g_GameData->bXpFarn ^= 1;
                LastTick = GetTickCount64();

                //  Console::Log("[+] [Patch::KillTarget]\n");
                Console::Log("[+] [Patch::XpFarm] %d\n", g_GameData->bXpFarn);
            }
        }

        if ((GetAsyncKeyState(VK_END) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
        {
            og_Killswitch = true;
            LastTick = GetTickCount64();
        }

        std::this_thread::sleep_for(1ms);
        std::this_thread::yield();
    }

    UPDATE.join();
    std::this_thread::sleep_for(5ms);
    FreeLibraryAndExitThread(og_hModule, EXIT_SUCCESS);
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved )
{
    using namespace FF7Remake;
    og_hModule = hModule;
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(og_hModule);
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, og_hModule, NULL, NULL);
        break;
    case DLL_PROCESS_DETACH:
        og_Killswitch = TRUE;
        break;
    }
    return TRUE;
}