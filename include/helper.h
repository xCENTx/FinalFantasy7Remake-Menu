#pragma once
#include <Engine.h>
#include <Menu.h>
#include <Game.h>

using namespace std::chrono_literals;
inline HMODULE g_pModule{ nullptr };
inline std::atomic_bool g_bRunning{ false };
inline std::atomic_bool g_bKillswitch{ false };

extern DWORD WINAPI MainThread(LPVOID hInstance);
extern VOID WINAPI BackgroundThread();