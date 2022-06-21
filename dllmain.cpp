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
        std::this_thread::sleep_for(1ms);
        std::this_thread::yield();
    }
    return;
}

DWORD WINAPI MainThread()
{
    using namespace FF7Remake;
    g_Console = std::make_unique<Console>();

#if DEBUG
    g_Console->InitializeConsole("FINAL FANTASY Vii INTERNAL - DEBUG CONSOLE");
    g_Console->printdbg("Final Fantasy Vii Remake Internal\n", g_Console->color.DEFAULT);
#endif

    g_GameData = std::make_unique<GameData>();
    g_GameVariables = std::make_unique<GameVariables>();
    g_GameData->Init();

    g_D3D11Window = std::make_unique<D3D11Window>();
    g_Hooking = std::make_unique<Hooking>();
    g_Menu = std::make_unique<Menu>();
    g_Hooking->Hook();



#if DEBUG
    g_Console->printdbg("Main::Initialized\n", g_Console->color.green);
#endif

    std::thread UPDATE(BackgroundWorker);
    while (og_Running)
    {
        if (GetAsyncKeyState(VK_INSERT) & 1) g_GameVariables->m_ShowMenu ^= 1;
        if (GetAsyncKeyState(VK_END) & 1) og_Killswitch = TRUE;
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