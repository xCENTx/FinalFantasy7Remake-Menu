#pragma once
#include "helper.h"
#include "Console.hpp"

namespace FF7Remake {

	struct Offsets {
		int aStatsPTR = 0x057A57E8;
		std::vector<unsigned int> oCloud = { 0x880 };
		std::vector<unsigned int> oParty2 = { 0x8C0 };
		std::vector<unsigned int> oParty3 = { 0x900 };
		std::vector<unsigned int> oParty4 = { 0x940 };
	};

	struct Stats
	{
		char pad_0000[16];	//0x0000
		int Level;	//0x0010
		char pad_0014[28];	//0x0014
		int HP;	//0x0030
		int MaxHP;	//0x0034
		int MP;	//0x0038
		int MaxMP;	//0x003C
		char pad_0040[8];	//0x0040
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
		char pad_0230[128];	//0x0230
	};	//Size: 0x02B0

	class GameData
	{
	public:
		Offsets offsets{};
		Stats* Cloud{};
		Stats* Party2{};
		Stats* Party3{};
		Stats* Party4{};

		explicit GameData();
		~GameData() noexcept = default;
		GameData(GameData const&) = delete;
		GameData(GameData&&) = delete;
		GameData& operator=(GameData const&) = delete;
		GameData& operator=(GameData&&) = delete;

		void Init();
		void Patch(BYTE* dst, BYTE* src, unsigned int size);
		void Nop(BYTE* dst, unsigned int size);
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
