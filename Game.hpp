#pragma once
#include "helper.h"
#include "Console.hpp"

namespace FF7Remake {

	struct Offsets {
		int aStatsPTR = 0x057A57E8;
		int aXinputState = 0x1D1F870;
		int aPauseGame = 0x16B4A84;
		std::vector<unsigned int> oCloud = { 0x880 };
		std::vector<unsigned int> oParty2 = { 0x8C0 };
		std::vector<unsigned int> oParty3 = { 0x900 };
		std::vector<unsigned int> oParty4 = { 0x940 };
	};

	struct PlayerStats
	{
		char pad_0000[36];	//0x0000
		float LimitBreak;	//0x0024
		char pad_0028[8];	//0x0028
		int HP;	//0x0030
		int MaxHP;	//0x0034
		int MP;	//0x0038
		int MaxMP;	//0x003C
		int ExperiencePoints;	//0x0040
		float ATB;	//0x0044
		int Attack;	//0x0048
		int MagicAttack;	//0x004C
		int Defense;	//0x0050
		int MagicDefense;	//0x0054
		int Luck;	//0x0058
		char pad_005C[452];	//0x005C
		int Strength;	//0x0220
		int Magic;	//0x0224
		int Vitality;	//0x0228
		int Spirit;	//0x022C
		char pad_0230[112];	//0x0230
		int PlayTime;	//0x02A0
		char pad_02A4[12];	//0x02A4
	};	//Size: 0x02B0

	class GameData
	{
	public:
		Offsets offsets{};
		PlayerStats* Cloud{};
		PlayerStats* Party2{};
		PlayerStats* Party3{};
		PlayerStats* Party4{};

		explicit GameData();
		~GameData() noexcept = default;
		GameData(GameData const&) = delete;
		GameData(GameData&&) = delete;
		GameData& operator=(GameData const&) = delete;
		GameData& operator=(GameData&&) = delete;

		void Init();
		void Patch(uintptr_t Addr, BYTE* src, unsigned int size);
		void Nop(uintptr_t Addr, unsigned int size);
		uintptr_t ResolvePTRS(uintptr_t ptr, std::vector<unsigned int> offsets);
	};

	class GameVariables
	{
	public:

		//	Dx & ImGui
		int g_GamePid{};
		HANDLE g_GameHandle{};
		HWND g_GameWindow{};
		int g_GameWidth;
		int g_GameHeight;
		ImVec2 g_WindowSize{};
		LPCSTR g_GameTitle;
		LPCSTR g_ClassName;
		LPCSTR g_GamePath;

		//	MENU RELATED
		bool m_ShowMenu{};
		bool m_ShowHud{};
		bool m_ShowDemo{};

		bool bINFHEALTH = FALSE;
		bool bINFMAGIC = FALSE;
		bool bINFLIMIT = FALSE;
		bool bINFATB = FALSE;

		explicit GameVariables();
		~GameVariables() noexcept = default;
		GameVariables(GameVariables const&) = delete;
		GameVariables(GameVariables&&) = delete;
		GameVariables& operator=(GameVariables const&) = delete;
		GameVariables& operator=(GameVariables&&) = delete;

		void Init();
	};

	inline std::unique_ptr<GameData> g_GameData;
	inline std::unique_ptr<GameVariables> g_GameVariables;
}
