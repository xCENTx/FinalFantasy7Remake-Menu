#pragma once
#define DEBUG 1

#include <windows.h>
#include <Psapi.h>
#include <TlHelp32.h>

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include <iostream>
#include <conio.h>
#include <string>
#include <thread>
#include <vector>
#include <chrono>

//	External Libraries
#include "libs/ImGui/imgui.h"
#include "libs/ImGui/imgui_internal.h"
#include "libs/ImGui/imgui_Impl_dx11.h"
#include "libs/ImGui/imgui_Impl_Win32.h"
#include "libs/MinHook/MinHook.h"

namespace FF7Remake {
	using namespace std::chrono_literals;
	inline HMODULE og_hModule{};
	inline LPCWSTR og_ModuleName{};
	inline std::atomic_bool og_Running = TRUE;
	inline std::atomic_bool og_Killswitch = FALSE;
	static uintptr_t og_GameBase = (uintptr_t)GetModuleHandle(NULL);
}