#include "Game.hpp"
namespace FF7Remake {
	AGameBase* CGlobal::gGameBase{ nullptr };
	int Offsets::oXinputState{ 0x1D1F920 };
	int Offsets::oGameBase{ 0x57B9260 };
	int Offsets::oSceneUpdate{ 0x16B44A0 };
	int Offsets::oSetHealth{ 0x0AFB6C0 };
	int Offsets::oSetMana{ 0x0AFB8D0 };
	int Offsets::oSubItem{ 0x0B1CAF0 };
	int Offsets::oTargetGetHP{ 0x08884C0 };
	int Offsets::oTargetGetStaggerAmount{ 0x0890620 };

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

	bool AItemSlot::IsValidIndex()
	{
		if (flag > 0)
			return false;

		if (flag2 > 0)
			return false;

		return isAvailable;
	}

	void APlayerStats::RefillHP() { HP = MaxHP; }

	void APlayerStats::RefillMana() { MP = MaxMP; }

	void APlayerStats::SetMaxLimit() { LimitBreak = 1000.f; }

	void APlayerStats::SetMaxATB() { ATB = 2000.f; }

	struct AGameState* ACloudState::GetGameState()
	{
		return reinterpret_cast<AGameState*>(reinterpret_cast<__int64>(pad_0000) - 0x880);
	}

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


	AGameState* OnUseItem::GetGameState() { return pCloudState->GetGameState(); }
	
	AInventory* OnUseItem::GetInventory() { return reinterpret_cast<AInventory*>(*pInventory); }

	AItemSlot* OnUseItem::GetCurrentItemSlot() { return GetItemSlot(); }

	AItemSlot* OnUseItem::GetItemSlot(int index)
	{
		/*
			AItemSlot* result{ nullptr };
			auto p = GetInventory();
			auto i = index * sizeof(AItemSlot);
			auto z = reinterpret_cast<long long>(p) + i;
			auto inv = reinterpret_cast<AInventory*>(z);
			AItemSlot* result = &inv->Item;
		*/
		return &reinterpret_cast<AInventory*>(reinterpret_cast<__int64>(GetInventory()) + index * sizeof(AItemSlot))->Item;
	}

	int OnUseItem::GetCurrentItemCount()
	{
		int result{ 0 };

		auto inventory = GetInventory();

		if (inventory)
			result = inventory->Item.count;

		return result;
	}

	OnSetHealth::OnSetHealth() {}
	OnSetHealth::OnSetHealth(int i, int hp)
	{
		bool isTakeDmg{ false };
		bool isHealing{ false };
		AGameBase* pGame = CGlobal::gGameBase;
		AGameState* pGameS = pGame->GetGameState();
		APlayerStats player_stats = pGameS->GetPlayerStats(i - 1); //	due to the way structures are spaced cloud is not included in the player stats array. subtracting 1 resolves this issue.
		int diff = player_stats.HP - hp;
		if (diff < 0)	//	if <0 player is healing
		{
			isHealing = true;
			diff = hp - player_stats.HP;
		}
		else if (diff > 0)
			isTakeDmg = true;

		index = i;
		mNewHP = hp;
		mDiff = diff;
		bHealing = isHealing;
		bTakingDmg = isTakeDmg;
		mPlayerStats = player_stats;
		pGameState = pGameS;
	}

	OnSetMana::OnSetMana() {}
	OnSetMana::OnSetMana(int i, int mp)
	{
		bool isSubMana{ false };
		bool isHealing{ false };
		AGameBase* pGame = CGlobal::gGameBase;
		AGameState* pGameS = pGame->GetGameState();
		APlayerStats player_stats = pGameS->GetPlayerStats(i - 1); //	due to the way structures are spaced cloud is not included in the player stats array. subtracting 1 resolves this issue.
		int diff = player_stats.MP - mp;
		if (diff < 0)	//	if <0 player is healing mana
		{
			isHealing = true;
			diff = mp - player_stats.MP;
		}
		else if (diff > 0)
			isSubMana = true;

		index = i;
		mNewMP = mp;
		mDiff = diff;
		bHealing = isHealing;
		bUsingMana = isSubMana;
		mPlayerStats = player_stats;
		pGameState = pGameS;
	}
}