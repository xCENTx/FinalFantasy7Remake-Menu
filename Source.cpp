#include "helper.h"

VOID WINAPI BackgroundThread()
{
    while (g_bRunning)
    {
        DX11Base::Menu::Loops();

        if (g_bKillswitch)
        {
           FF7Remake::AGame::ShutdownGame();
            DX11Base::g_Hooking->Shutdown();

            DX11Base::g_Engine.release();     //  releases all created class instances
            g_bRunning = false;
        }

        std::this_thread::sleep_for(1ms);
        std::this_thread::yield();
    }
    return;
}

DWORD WINAPI MainThread(LPVOID hInstance)
{
    UNREFERENCED_PARAMETER(hInstance);

    DX11Base::g_Engine = std::make_unique<DX11Base::Engine>();
    DX11Base::g_Console->InitializeConsole("Final Fantasy 7 Remake : Debug Console", true);      //  initialize console without menu gui
    DX11Base::g_Engine->Init();                                                                   //  Get Process Information
    DX11Base::g_Hooking->Initialize();                                                            //  Hook Functions
    FF7Remake::AGame::InitGame();

    std::thread UPDATE(BackgroundThread);

    //  MAIN LOOP
    static int LastTick{ 0 };
    while (g_bRunning)
    {
        if (DX11Base::Console::m_bGUI)
        {
            if ((DX11Base::Engine::GamePadGetKeyState(XINPUT_GAMEPAD_RIGHT_THUMB | XINPUT_GAMEPAD_LEFT_THUMB) || DX11Base::Engine::GetKeyState(VK_INSERT, 0)) && ((GetTickCount64() - LastTick) > 500))
                //if ((GetAsyncKeyState(VK_INSERT) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                //  Hide our welcome message
                if (DX11Base::g_Engine->m_ShowWelcome)
                    DX11Base::g_Engine->m_ShowWelcome ^= 1;

                //  Show / Hide Menu
                DX11Base::g_Engine->m_ShowMenu ^= 1;

                LastTick = GetTickCount64();
            }
        }

        if (!DX11Base::Console::m_bGUI)
        {
            //  Adjust Console Verbosity
            if ((GetAsyncKeyState(VK_NUMPAD0) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                DX11Base::g_Console->m_bVerbose ^= 1;
                LastTick = GetTickCount64();

                DX11Base::Console::Log("[+] [Console::Verbose] %d\n", DX11Base::g_Console->m_bVerbose);
            }

            //  Set No Damage Mod
            if ((GetAsyncKeyState(VK_NUMPAD1) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                FF7Remake::AGame::bNullDmg ^= 1;
                LastTick = GetTickCount64();

                DX11Base::Console::Log("[+] [Patch::NullDmg] %d\n", FF7Remake::AGame::bNullDmg);
            }

            //  Set No Mana Use Mod
            if ((GetAsyncKeyState(VK_NUMPAD2) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                FF7Remake::AGame::bNullMgk ^= 1;
                LastTick = GetTickCount64();

                DX11Base::Console::Log("[+] [Patch::NullMana] %d\n", FF7Remake::AGame::bNullMgk);
            }

            //  Set No Item Use Mod
            if ((GetAsyncKeyState(VK_NUMPAD3) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                FF7Remake::AGame::bNullItem ^= 1;
                LastTick = GetTickCount64();

                DX11Base::Console::Log("[+] [Patch::NullItem] %d\n", FF7Remake::AGame::bNullItem);
            }

            //  Set Max ATB Mod
            if ((GetAsyncKeyState(VK_NUMPAD4) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                FF7Remake::AGame::bMaxATB ^= 1;
                LastTick = GetTickCount64();

                DX11Base::Console::Log("[+] [Patch::MaxATB] %d\n", FF7Remake::AGame::bMaxATB);
            }

            //  Set Max Limit Mod
            if ((GetAsyncKeyState(VK_NUMPAD5) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                FF7Remake::AGame::bMaxLimit ^= 1;
                LastTick = GetTickCount64();

                DX11Base::Console::Log("[+] [Patch::MaxLimit] %d\n", FF7Remake::AGame::bMaxLimit);
            }

            //  Set Target Doesn't Attack
            if ((GetAsyncKeyState(VK_NUMPAD6) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                FF7Remake::AGame::bNoTargetAttack ^= 1;
                LastTick = GetTickCount64();

                DX11Base::Console::Log("[+] [Patch::TargetNoAttack] %d\n", FF7Remake::AGame::bNoTargetAttack);
            }

            //  Set Target Takes No Damage
            if ((GetAsyncKeyState(VK_NUMPAD7) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                FF7Remake::AGame::bNullTargetDmg ^= 1;
                LastTick = GetTickCount64();

                DX11Base::Console::Log("[+] [Patch::TargetTakesNoDamage] %d\n", FF7Remake::AGame::bNullTargetDmg);
            }

            //  Set Target Always Stagger
            if ((GetAsyncKeyState(VK_NUMPAD8) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                FF7Remake::AGame::bTargetAlwaysStagger ^= 1;
                LastTick = GetTickCount64();

                DX11Base::Console::Log("[+] [Patch::TargetAlwaysStagger] %d\n", FF7Remake::AGame::bTargetAlwaysStagger);
            }

            //  Set Kill Target
            //  Set Xp Farm
            if ((GetAsyncKeyState(VK_NUMPAD9) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
            {
                //  AGame::bNullTargetDmg = false;
                //  AGame::bTargetAlwaysStagger = false;
                //  AGame::bKillTarget ^= 1;
                FF7Remake::AGame::bXpFarm ^= 1;
                LastTick = GetTickCount64();

                //  Console::Log("[+] [Patch::KillTarget]\n");
                DX11Base::Console::Log("[+] [Patch::XpFarm] %d\n", FF7Remake::AGame::bXpFarm);
            }
        }

        if ((GetAsyncKeyState(VK_END) & 0x8000) && ((GetTickCount64() - LastTick) > 500))
        {
            g_bKillswitch = true;
            LastTick = GetTickCount64();
        }

        std::this_thread::sleep_for(1ms);
        std::this_thread::yield();
    }

    UPDATE.join();
    FreeLibraryAndExitThread(g_pModule, EXIT_SUCCESS);
}