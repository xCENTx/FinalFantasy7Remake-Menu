#pragma once
#include "helper.h"
#include "Engine.h"
#include "Game.h"
#include "Menu.h"

void BackgroundWorker()
{
    using namespace FF7Remake;
    while (og_Running)
    {
        Menu::Loops();

        if (og_Killswitch)
        {
            AGame::ShutdownGame();
            g_Hooking->Shutdown();

            g_Engine.release();     //  releases all created class instances
            og_Running = false;
        }

        std::this_thread::sleep_for(1ms);
        std::this_thread::yield();
    }
    return;
}

DWORD WINAPI MainThread(LPVOID hInstance)
{
    UNREFERENCED_PARAMETER(hInstance);

    using namespace FF7Remake;
    g_Engine = std::make_unique<Engine>();
    g_Console->InitializeConsole("Final Fantasy 7 Remake : Debug Console", true);      //  initialize console without menu gui
    g_Engine->Init();                                                                   //  Get Process Information
    g_Hooking->Initialize();                                                            //  Hook Functions
    AGame::InitGame();

    std::thread UPDATE(BackgroundWorker);

    //  MAIN LOOP
    static int LastTick{ 0 };
    while (og_Running)
    {
        if (Console::m_bGUI)
        {
            if ((Engine::GamePadGetKeyState(XINPUT_GAMEPAD_RIGHT_THUMB | XINPUT_GAMEPAD_LEFT_THUMB) || Engine::GetKeyState(VK_INSERT, 0)) && ((GetTickCount64() - LastTick) > 500))
            //if ((GetAsyncKeyState(VK_INSERT) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                //  Hide our info message
                if (g_Engine->m_ShowHud == TRUE)
                    g_Engine->m_ShowHud = FALSE;

                //  Show / Hide Menu
                g_Engine->m_ShowMenu ^= 1;

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
                AGame::bNullDmg ^= 1;
                LastTick = GetTickCount64();

                Console::Log("[+] [Patch::NullDmg] %d\n", AGame::bNullDmg);
            }

            //  Set No Mana Use Mod
            if ((GetAsyncKeyState(VK_NUMPAD2) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                AGame::bNullMgk ^= 1;
                LastTick = GetTickCount64();

                Console::Log("[+] [Patch::NullMana] %d\n", AGame::bNullMgk);
            }

            //  Set No Item Use Mod
            if ((GetAsyncKeyState(VK_NUMPAD3) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                AGame::bNullItem ^= 1;
                LastTick = GetTickCount64();

                Console::Log("[+] [Patch::NullItem] %d\n", AGame::bNullItem);
            }

            //  Set Max ATB Mod
            if ((GetAsyncKeyState(VK_NUMPAD4) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                AGame::bMaxATB ^= 1;
                LastTick = GetTickCount64();

                Console::Log("[+] [Patch::MaxATB] %d\n", AGame::bMaxATB);
            }
            
            //  Set Max Limit Mod
            if ((GetAsyncKeyState(VK_NUMPAD5) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                AGame::bMaxLimit ^= 1;
                LastTick = GetTickCount64();

                Console::Log("[+] [Patch::MaxLimit] %d\n", AGame::bMaxLimit);
            }

            //  Set Target Doesn't Attack
            if ((GetAsyncKeyState(VK_NUMPAD6) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                AGame::bNoTargetAttack ^= 1;
                LastTick = GetTickCount64();

                Console::Log("[+] [Patch::TargetNoAttack] %d\n", AGame::bNoTargetAttack);
            }

            //  Set Target Takes No Damage
            if ((GetAsyncKeyState(VK_NUMPAD7) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                AGame::bNullTargetDmg ^= 1;
                LastTick = GetTickCount64();

                Console::Log("[+] [Patch::TargetTakesNoDamage] %d\n", AGame::bNullTargetDmg);
            }

            //  Set Target Always Stagger
            if ((GetAsyncKeyState(VK_NUMPAD8) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                AGame::bTargetAlwaysStagger ^= 1;
                LastTick = GetTickCount64();

                Console::Log("[+] [Patch::TargetAlwaysStagger] %d\n", AGame::bTargetAlwaysStagger);
            }

            //  Set Kill Target
            //  Set Xp Farm
            if ((GetAsyncKeyState(VK_NUMPAD9) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                //  AGame::bNullTargetDmg = false;
                //  AGame::bTargetAlwaysStagger = false;
                //  AGame::bKillTarget ^= 1;
                AGame::bXpFarm ^= 1;
                LastTick = GetTickCount64();

                //  Console::Log("[+] [Patch::KillTarget]\n");
                Console::Log("[+] [Patch::XpFarm] %d\n", AGame::bXpFarm);
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

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(lpReserved);

    using namespace FF7Remake;

    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        og_hModule = hModule;

        DisableThreadLibraryCalls(og_hModule);
    
        HANDLE hThread = CreateThread(NULL, NULL, MainThread, og_hModule, NULL, NULL);
        
        if (hThread)
            CloseHandle(hThread);
    }
    
    return true;
}