#pragma once
#include "helper.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(lpReserved);

    using namespace FF7Remake;

    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        g_pModule = hModule;

        DisableThreadLibraryCalls(g_pModule);
    
        HANDLE hThread = CreateThread(NULL, NULL, MainThread, g_pModule, NULL, NULL);
        
        if (hThread)
            CloseHandle(hThread);
    }
    
    return true;
}