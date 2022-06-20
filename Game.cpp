#include "Game.hpp"
namespace FF7Remake {
	GameData::GameData()
	{
		//	Establish base variables
		return;
	}

	void GameData::Init()
	{
		Cloud = (Stats*)g_GameData->ResolvePTRS(offsets.aStatsPTR, offsets.oCloud);
		Party2 = (Stats*)g_GameData->ResolvePTRS(offsets.aStatsPTR, offsets.oParty2);
		Party3 = (Stats*)g_GameData->ResolvePTRS(offsets.aStatsPTR, offsets.oParty3);
		Party4 = (Stats*)g_GameData->ResolvePTRS(offsets.aStatsPTR, offsets.oParty4);
#if DEBUG
		g_Console->printdbg("ModuleBase: { %llx }\n", g_Console->color.DEFAULT, og_GameBase);
		g_Console->printdbg("GameData::Stats->Cloud { %llx }\n", g_Console->color.DEFAULT, Cloud);
		g_Console->printdbg("GameData::Stats->oParty2 { %llx }\n", g_Console->color.DEFAULT, Party2);
		g_Console->printdbg("GameData::Stats->oParty3 { %llx }\n", g_Console->color.DEFAULT, Party3);
		g_Console->printdbg("GameData::Stats->oParty4 { %llx }\n", g_Console->color.DEFAULT, Party4);
		g_Console->printdbg("GameData::Initialized\n\n", g_Console->color.pink);
#endif
	}

	void GameData::Patch(BYTE* dst, BYTE* src, unsigned int size)
	{
		DWORD oldprotect;
		VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
		memcpy(dst, src, size);
		VirtualProtect(dst, size, oldprotect, &oldprotect);
	}

	void GameData::Nop(BYTE* dst, unsigned int size)
	{
		DWORD oldprotect;
		VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
		memset(dst, 0x00, size);
		VirtualProtect(dst, size, oldprotect, &oldprotect);
	}

	uintptr_t GameData::ResolvePTRS(uintptr_t ptr, std::vector<unsigned int> offsets)
	{
		uintptr_t addr = og_GameBase + ptr;
		for (unsigned int i = 0; i < offsets.size(); ++i)
		{
			addr = *(uintptr_t*)addr;
			addr += offsets[i];
		}
		return addr;
	}

	GameVariables::GameVariables()
	{
		//	Establish base variables
		return;
	}

	//	Get Process Window Information
	void GameVariables::Init()
	{
		g_GamePid = GetCurrentProcessId();
		g_GameHandle = GetCurrentProcess();
		g_GameWindow = GetForegroundWindow();

		RECT tempRECT;
		GetWindowRect(g_GameWindow, &tempRECT);
		g_GameWidth = tempRECT.right - tempRECT.left;
		g_GameHeight = tempRECT.bottom - tempRECT.top;

		char tempTitle[MAX_PATH];
		GetWindowTextA(g_GameWindow, tempTitle, sizeof(tempTitle));
		g_GameTitle = tempTitle;

		char tempClassName[MAX_PATH];
		GetClassNameA(g_GameWindow, tempClassName, sizeof(tempClassName));
		g_ClassName = tempClassName;

		char tempPath[MAX_PATH];
		GetModuleFileNameExA(g_GameHandle, NULL, tempPath, sizeof(tempPath));
		g_GamePath = tempPath;
#if DEBUG
		g_Console->printdbg("GameVariables::PID - { %d }\n", g_Console->color.DEFAULT, g_GamePid);
		g_Console->printdbg("GameVariables::GamePath - { %s }\n", g_Console->color.DEFAULT, g_GamePath);
		g_Console->printdbg("GameVariables::WindowTitle - { %s }\n", g_Console->color.DEFAULT, g_GameTitle);
		g_Console->printdbg("GameVariables::WindowWidth - { %d }\n", g_Console->color.DEFAULT, g_GameWidth);
		g_Console->printdbg("GameVariables::WindowHeight - { %d }\n", g_Console->color.DEFAULT, g_GameHeight);
		g_Console->printdbg("GameVariables::Init - Process Window Info Established\n", g_Console->color.pink);
		g_Console->printdbg("GameVariables::Initialized\n\n", g_Console->color.pink);
#endif
	}
}