#pragma once
#include "helper.h"
#include "Console.hpp"

namespace FF7Remake 
{
	class GameData
	{
	public:

		//	PROCESS & WINDOW
		int									g_GamePid{ 0 };
		HMODULE								g_GameModule{ 0 };
		__int64								g_GameBaseAddr{ 0 };
		HANDLE								g_GameHandle{ 0 };
		HWND								g_GameWindow{ 0 };
		int									g_GameWidth{ 0 };
		int									g_GameHeight{ 0 };
		ImVec2								g_WindowSize{ 0.f , 0.f };
		LPCSTR								g_GameTitle{ 0 };
		LPCSTR								g_ClassName{ 0 };
		LPCSTR								g_GamePath{ 0 };

		//	MENU
		bool								m_ShowMenu{ false };
		bool								m_ShowHud{ false };
		bool								m_ShowDemo{ false };

		//	PATCHES
		bool								bDemiGod{ false };
		bool								bDemiGodMagic{ false };
		bool								bMaxLimit{ false };
		bool								bMaxATB{ false };
		bool								bPauseGame{ false };
		bool								bNullDmg{ false };
		bool								bNullItem{ false };
		bool								bModTimeScale{ false };
		float								fTimeScale{ 1.0f };

		//	
		void								Init();

		//	constructor
		GameData();
		~GameData() noexcept = default;
	};
	inline std::unique_ptr<GameData> g_GameData;

	struct Offsets 
	{
		static int							oXinputState;
		static int							oGameBase;
		static int							oSceneUpdate;
		static int							oSubHealth;
		static int							oSubItem;
	};

	struct Patches
	{
		static void							RefillCloudHP();
		static void							RefillCloudMP();
		static void							CloudMaxLimit();
		static void							CloudMaxATB();
	};
	
	class CGlobal
	{
	public:
		static class AGameBase*				gGameBase;				//0x0000
	};	//Size: 0x0008
	
	struct ItemSlot
	{
		char								pad_0000[12];		//0x0000
		int									Count;				//0x000C
		char								pad_0010[8];		//0x0010
	};	//Size: 0x0018

	struct AInventory
	{
		struct ItemSlot						Item;				//0x0000
		char								pad_0018[312];		//0x0018
	};	//Size: 0x0150

	struct APlayerStats
	{
		char								pad_0000[4];			//0x0000
		float								LimitBreak;				//0x0004
		char								pad_0008[8];			//0x0008
		int									HP;						//0x0010
		int									MaxHP;					//0x0014
		int									MP;						//0x0018
		int									MaxMP;					//0x001C
		int									XP;						//0x0020
		float								ATB;					//0x0024
		int									Attack;					//0x0028
		int									MagicAtk;				//0x002C
		int									Defense;				//0x0030
		int									MagicDef;				//0x0034
		int									Luck;					//0x0038
		char								pad_003C[4];			//0x003C

		//	
		void								RefillHP();
		void								RefillMana();
		void								SetMaxLimit();
		void								SetMaxATB();
	};	//Size: 0x0040

	struct APlayerAttributes
	{
		int									Strength;				//0x0000
		int									Magic;					//0x0004
		int									Vitality;				//0x0008
		int									Spirit;					//0x000C
	};	//Size: 0x0010

	struct ACloudState
	{
		char								pad_0000[32];			//0x0000
		struct APlayerStats					mStats;					//0x0020
	};	//Size: 0x0060

	class AGameState
	{
	private:
		char								pad_0000[2176];			//0x0000
		struct ACloudState					mCloudState;			//0x0880
		struct APlayerStats					mPartyStats[6];			//0x08E0
		char								pad_0A60[64];			//0x0A60
		struct APlayerAttributes			mPartyAttributes[6];	//0x0AA0
		char								pad_0B00[32];			//0x0B00
		__int64								TotalGamTime;			//0x0B20
	
	public:
		struct APlayerStats					GetPlayerStats(int index);
		void								SetPlayerStats(int index, const APlayerStats newStats);
		struct APlayerStats					GetCloudStats();
		void								SetCloudStats(const APlayerStats newState);
		struct APlayerAttributes			GetPlayerAttributes(int index);
		void								SetPlayerAttributes(int index, const APlayerAttributes newAttributes);
		struct APlayerAttributes			GetCloudAttributes();
		void								SetCloudAttributes(const APlayerAttributes newAttributes);

	};	//Size: 0x0B28

	class AGameBase
	{
		__int32								mMatchState_0;			//0x0000	//	0x08 at main menu	|	0x2 in story
		__int32								mMatchState_1;			//0x0004	//	0x01 at main menu	|	0x1 in story
		class AGameState*					pGameState;				//0x0008
	
	public:
		bool								Valid();
		class AGameState*					GetGameState();

	};	//Size: 0x0010

	class AScene
	{
	private:
		char								pad_0008[1256];			//0x0008
		bool								bPause;					//0x04F0
		char								pad_04F1[23];			//0x04F1
		float								TimeScale;				//0x0508
		char								pad_050C[68];			//0x050C

	private:
		virtual void						Function0();

	public:
		void								SetPauseState(bool newState);
		bool								GetPauseState();
		void								SetTimeScale(float newScalar);
		float								GetTimeScale();
	};	//Size: 0x0550
}
