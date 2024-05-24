#include "Game.hpp"
namespace FF7Remake {
	AGameBase* CGlobal::gGameBase{ nullptr };
	int Offsets::oXinputState{ 0x1D1F920 };
	int Offsets::oGameBase{ 0x57B9260 };
	int Offsets::oSceneUpdate{ 0x16B44A0 };
	int Offsets::oSubHealth{ 0x0AFB6C0 };

	GameData::GameData() { }

	void GameData::Init()
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


	void APlayerStats::RefillHP() { HP = MaxHP; }

	void APlayerStats::RefillMana() { MP = MaxMP; }

	void APlayerStats::SetMaxLimit() { LimitBreak = 1000.f; }

	void APlayerStats::SetMaxATB() { ATB = 2000.f; }


	struct APlayerStats AGameState::GetPlayerStats(int index) { return this->mPartyStats[index]; }

	void AGameState::SetPlayerStats(int index, const APlayerStats newStats) { this->mPartyStats[index] = newStats; }

	struct APlayerStats AGameState::GetCloudStats() { return this->mCloudState.mStats; }

	void AGameState::SetCloudStats(const APlayerStats newState) { this->mCloudState.mStats = newState; }

	struct APlayerAttributes AGameState::GetPlayerAttributes(int index) { return this->mPartyAttributes[index]; }

	void AGameState::SetPlayerAttributes(int index, const APlayerAttributes newAttributes) { this->mPartyAttributes[index] = newAttributes; }

	struct APlayerAttributes AGameState::GetCloudAttributes() { return GetPlayerAttributes(0); }											//	return this->mPamPartyAttributes[0];

	void AGameState::SetCloudAttributes(const APlayerAttributes newAttributes) { SetPlayerAttributes(0, newAttributes); }	//	this->mPartyAttributes[0] = newAttributes; }


	bool AGameBase::Valid() { return this->mMatchState_0 <= 2; }

	class AGameState* AGameBase::GetGameState()
	{
		AGameState* result{ nullptr };

		if (this->Valid())
			result = this->pGameState;

		return result;
	}

	void AScene::SetPauseState(bool newState) { this->bPause = newState; }

	bool AScene::GetPauseState() { return this->bPause; }

	void AScene::SetTimeScale(float newScalar) { this->TimeScale = newScalar; }

	float AScene::GetTimeScale() { return this->TimeScale; }
}