#include "Game.hpp"
namespace FF7Remake {
	AGameBase* CGlobal::gGameBase{ nullptr };
	int Offsets::oXinputState{ 0x1D1F920 };             //	0x1D1F870;
	int Offsets::oGameBase{ 0x57B9260 };
	int Offsets::oSceneUpdate{ 0x16B44A0 };
	int Offsets::oSubHealth{ 0x0AFB6C0 };

	GameData::GameData()
	{
		g_GamePid = GetCurrentProcessId();
		g_GameHandle = GetCurrentProcess();
		g_GameWindow = GetForegroundWindow();
		g_GameModule = GetModuleHandle(0);
		g_GameBaseAddr = reinterpret_cast<__int64>(g_GameModule);

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
		GetModuleFileNameExA(g_GameHandle, 0, tempPath, sizeof(tempPath));
		g_GamePath = tempPath;


		CGlobal::gGameBase = reinterpret_cast<AGameBase*>(g_GameBaseAddr + Offsets::oGameBase);
	}

	void GameData::Init()
	{
#if _DEBUG
		g_Console->printdbg("ModuleBase: { %llx }\n", g_Console->color.DEFAULT, g_GameBaseAddr);
		g_Console->printdbg("GameStateBase: { %llx }\n", g_Console->color.DEFAULT, CGlobal::gGameBase);
		g_Console->printdbg("GameData::Initialized\n\n", g_Console->color.pink);
#endif
	}

	void Patches::RefillCloudHP()
	{
		AGameState* pGameState = CGlobal::gGameBase->GetGameState();
		if (!pGameState)
			return;

		//	Get cloud player stats
		APlayerStats cloud_stats = pGameState->GetCloudStats();
		cloud_stats.RefillHP();	//	set hp var to match max hp

		//	 Set cloud new player stats
		pGameState->SetCloudStats(cloud_stats);
	}

	void Patches::RefillCloudMP()
	{
		AGameState* pGameState = CGlobal::gGameBase->GetGameState();
		if (!pGameState)
			return;

		//	Get cloud player stats
		APlayerStats cloud_stats = pGameState->GetCloudStats();
		cloud_stats.RefillMana();

		//	 Set cloud new player stats
		pGameState->SetCloudStats(cloud_stats);
	}

	void Patches::CloudMaxLimit()
	{
		AGameState* pGameState = CGlobal::gGameBase->GetGameState();
		if (!pGameState)
			return;

		//	Get cloud player stats
		APlayerStats cloud_stats = pGameState->GetCloudStats();
		cloud_stats.SetMaxLimit();

		//	 Set cloud new player stats
		pGameState->SetCloudStats(cloud_stats);
	}

	void Patches::CloudMaxATB()
	{
		AGameState* pGameState = CGlobal::gGameBase->GetGameState();
		if (!pGameState)
			return;

		//	Get cloud player stats
		APlayerStats cloud_stats = pGameState->GetCloudStats();
		cloud_stats.SetMaxATB();

		//	 Set cloud new player stats
		pGameState->SetCloudStats(cloud_stats);
	}
}