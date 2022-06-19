#include "Game.hpp"
namespace FF7Remake {
	GameData::GameData()
	{

#if DEBUG
		g_Console->printdbg("ModuleBase: %llx\n", g_Console->color.DEFAULT, og_GameBase);
		g_Console->printdbg("GameData::Initialized\n", g_Console->color.pink);
#endif

		return;
	}

	void GameData::Init()
	{
		//Player = (PlayerObject*)(*(uintptr_t*)(og_GameBase + g_GameData->offsets.BaseOffset)) + 880;
		Player = (PlayerObject*)g_GameData->ResolvePTRS(offsets.BaseOffset, { 0x880 });
#if DEBUG
		g_Console->printdbg("PlayerObjectBase: %llx\n", g_Console->color.DEFAULT, Player);
		g_Console->printdbg("PlayerHP: %d\n", g_Console->color.DEFAULT, Player->MaxHP);
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
#if DEBUG
		g_Console->printdbg("GameVariables::Initialized\n", g_Console->color.pink);
#endif

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
		g_Console->printdbg("GameData::PID - %d\n", g_Console->color.DEFAULT, g_GamePid);
		g_Console->printdbg("GameData::GamePath - %s\n", g_Console->color.DEFAULT, g_GamePath);
		g_Console->printdbg("GameData::WindowWidth - %x\n", g_Console->color.DEFAULT, g_GameWidth);
		g_Console->printdbg("GameData::WindowHeight - %x\n", g_Console->color.DEFAULT, g_GameHeight);
		g_Console->printdbg("GameData::WindowTitle - %s\n", g_Console->color.DEFAULT, g_GameTitle);
		g_Console->printdbg("GameData::Init - Process Window Info Established\n", g_Console->color.pink);
#endif
	}
}