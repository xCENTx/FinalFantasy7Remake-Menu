#pragma once
#include <Engine.h>
#include <Menu.h>

namespace FF7Remake 
{
	/*
	*		GENERAL GUIDELINES
	* 
	*	namespace		: global game member variables. should be constexpr as the values will never change.
	*	struct			: offsets arranged with padding to align with game memory. member variables are public by default.
	*	class			: implies the "struct" has virtual methods, member variables should be made private with methods for accessing data for safety
	*	enum			: should be as close to the origin data structure as possible. i.e EItemType would reside above AItem
	*	member vars		: [bool : b<name> : bValid] [enum : e<Name> : eType] [pointer : p<Name> : pInstance] [static pointer : g<Name>] [global : g_<prefix><Name> : g_bRunning]
	*	A<StructName>	: all game engine general purpose class and struct names should be prefixed with A to signify it is a game engine related data structure
	*	T<StructName>	: all game engine template class and struct names should be prefixed with T to signify that it is both a templated and game related data structure.
	*	
	*	ternary			: keep it basic and readable.
	*	recursion		: would batman ?
	*	

	*/
	
	namespace Offsets
	{
		constexpr auto						oGameBase{ 0x57B9260 };					//	48 8B 05 ? ? ? ? 4C 89 B4 24 ? ? ? ? 44 0F B6 76
		constexpr auto						oGameBase_CloudState{ 0x880 };			//	Analyze APlayerState_SetHealth_hook
		constexpr auto						oGameBase_ItemsList{ 0x35640 };			//	Analyze APlayerState_SubItem_hook
		constexpr auto						oGameBase_MateriaList{ 0x20A8 };		//	
	};

	namespace FunctionOffsets
	{
		constexpr auto						fnXinputState{ 0x1D1F920 };				//	XInput_State_hook
		constexpr auto						fnSceneUpdate{ 0x16B44A0 };				//	AScene_Update_hook
		constexpr auto						fnSetHealth{ 0x0AFB6C0 };				//	APlayerState_SetHealth_hook
		constexpr auto						fnSetMana{ 0x0AFB8D0 };					//	APlayerState_SetMana_hook
		constexpr auto						fnSubItem{ 0x0B1CAF0 };					//	APlayerState_SubItem_hook
		constexpr auto						fnTargetGetHP{ 0x08884C0 };				//	ATargetEntity_GetHP_hook
		constexpr auto						fnTargetGetStaggerAmount{ 0x0890620 };	//	ATargetEntity_GetStaggerAmount_hook		
	}

	namespace VtableOffsets
	{
		constexpr auto						vfTargetEntity{ 0x4B3E5E8 };			//  Analyze ATargetEntity_GetHP_hook
	}

	class AGame
	{
	public:
		static class AGameBase*				gGameBase;				//0x0000
		static bool							bDemiGod;
		static bool							bDemiGodMagic;
		static bool							bMaxLimit;
		static bool							bMaxATB;
		static bool							bPauseGame;
		static bool							bNullDmg;
		static bool							bNullMgk;
		static bool							bNullItem;
		static bool							bModTimeScale;
		static float						fTimeScalar;
		static bool							bModTargetLevel;
		static int							iLevelScalar;
		static bool							bKillTarget;
		static bool							bNoTargetAttack;		//	target doesnt attack
		static bool							bNullTargetDmg;			//	target takes no damage
		static bool							bTargetAlwaysStagger;	//	target defense is set to 0
		static bool							bXpFarm;				//	sets targets hp to 0, prevents targets from attacking , sets target stagger to max and sets target to max level for max reward
	
	public:
		static void							InitGame();
		static void							ShutdownGame();
		
	public:
		struct Patches
		{
			static void						RefillCloudHP();
			static void						RefillCloudMP();
			static void						CloudMaxLimit();
			static void						CloudMaxATB();
			static void						RefillPartyHP();
			static void						RefillPartyMP();
			static void						PartyMaxLimit();
			static void						PartyMaxATB();
		};

	public:
		struct Hooks
		{
			typedef __int64(__fastcall* XInput_State)(__int64);
			static __int64 __fastcall XInput_State_hook(__int64 a1);
			static XInput_State XInput_State_stub;
			static __int64 pXInput_State;

			typedef void(__fastcall* AScene_Update)(__int64);
			static void __fastcall AScene_Update_hook(__int64 p);
			static AScene_Update AScene_Update_stub;
			static __int64 pAScene_Update;

			typedef __int64(__fastcall* APlayerState_SetHealth)(unsigned __int8, int);
			static __int64 __fastcall APlayerState_SetHealth_hook(unsigned __int8 a1, int a2);
			static APlayerState_SetHealth APlayerState_SetHealth_stub;
			static __int64 pAPlayerState_SetHealth;

			typedef __int64(__fastcall* APlayerState_SetMP)(unsigned __int8, int);
			static __int64 __fastcall APlayerState_SetMana_hook(unsigned __int8 a1, int a2);
			static APlayerState_SetMP APlayerState_SetMana_stub;
			static __int64 pAPlayerState_SetMana;

			typedef __int64(__fastcall* APlayerState_SubItem)(__int64, int);
			static __int64 __fastcall APlayerState_SubItem_hook(__int64 a1, int a2);
			static APlayerState_SubItem APlayerState_SubItem_stub;
			static __int64 pAPlayerState_SubItem;

			typedef __int64(__fastcall* ATargetEntity_GetHP)(__int64 a1);
			static __int64 __fastcall ATargetEntity_GetHP_hook(__int64 a1);
			static ATargetEntity_GetHP ATargetEntity_GetHP_stub;
			static __int64 pATargetEntity_GetHP;

			typedef float(__fastcall* ATargetEntity_GetStaggerAmount)(__int64);
			static __int64 __fastcall ATargetEntity_GetStaggerAmount_hook(__int64 a1);
			static ATargetEntity_GetStaggerAmount ATargetEntity_GetStaggerAmount_stub;
			static __int64 pATargetEntity_GetStaggerAmount;
		};
	};

	enum EItemType : __int32
	{
		EItemType_Item = 0,
		EItemType_Unk1,
		EItemType_KeyItem,
		EItemType_Unk3,
		EItemType_Unk8 = 8,
		EItemType_Unk9,
		EItemType_Unk10,
	};

	struct AItem
	{
		unsigned __int32					ID;							//0x0000
		char								pad_0004[8];				//0x0004
		int									Valid;						//0x0008
		int									Count;						//0x000C
		enum EItemType						eItemType;					//0x0010
		char								pad_0014[4];				//0x0014

	public:
		bool								IsItem();
		__int32								GetID();
		std::string							GetName();
	};	//Size: 0x0018

	struct AMateria
	{
		int									Index;						//0x0000
		char								pad_0004[4];				//0x0004
		char								Level;						//0x0008
		char								AssignedPartyMemberIndex;	//0x0009
		char								pad_000A[2];				//0x000A
		unsigned int						NameID;						//0x000C
		int									TotalXP;					//0x0010
		char								pad_0014[4];				//0x0014
		int									MateriaID;					//0x0018
		char								pad_001C[4];				//0x001C

	public:
		__int32								GetID();
		__int32								GetNameID();
		std::string							GetName();
	};	//Size: 0x0020

	struct AEquipment
	{
		char								pad_0000[80];				//0x0000
		int									GilCost;					//0x0050
		char								pad_0054[4];				//0x0054
		int									GilSell;					//0x0058
		//	unsigned char						N00000257;					//0x005C
		//	char								pad_005D[19];				//0x005D
		char								pad_005C[20];				//0x005C
		int									Attack;						//0x0070
		char								pad_0074[4];				//0x0074
		int									MagicAtk;					//0x0078
		char								pad_007C[4];				//0x007C
		int									Defense;					//0x0080
		char								pad_0084[4];				//0x0084
		int									MagicDefense;				//0x0088
		char								pad_008C[4];				//0x008C
		int									Strength;					//0x0090
		char								pad_0094[4];				//0x0094
		int									Magic;						//0x0098
		char								pad_009C[4];				//0x009C
		int									Vitality;					//0x00A0
		char								pad_00A4[4];				//0x00A4
		int									Spirit;						//0x00A8
		char								pad_00AC[4];				//0x00AC
		int									Luck;						//0x00B0
		char								pad_00B4[108];				//0x00B4
		char								LinkedMateriaSlots;			//0x0120
		char								SingleMateriaSlots;			//0x0121
	};	//Size: 0x0122

	struct AInventory
	{
		struct AItem						Item;					//0x0000
		char								pad_0018[312];			//0x0018
	};	//Size: 0x0150

	struct AComponents
	{
		struct AInventory*					pInventory;				//0x0000
		char								pad_0008[120];			//0x0008
	};	//Size: 0x0080

	struct APlayerStats
	{
		char								pad_0000[4];			//0x0000
		float								LimitBreak;				//0x0004
		char								pad_0008[8];			//0x0008
		int									HP;						//0x0010	//	0x30
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
		char								pad_0000[32];			//0x0000	//0x0880
		struct APlayerStats					Stats;					//0x0020	//0x08C0

		//	
		class AGameState*					GetGameState();
	};	//Size: 0x0060

	class AGameState
	{
	private:
		char								pad_0000[2176];			//0x0000
		struct ACloudState					CloudState;				//0x0880
		struct APlayerStats					PartyStats[6];			//0x08E0
		char								pad_0A60[64];			//0x0A60
		struct APlayerAttributes			PartyAttributes[6];		//0x0AA0
		char								pad_0B00[32];			//0x0B00
		__int64								TotalGameTime;			//0x0B20
	
	public:
		struct APlayerStats					GetPlayerStats(int index);
		void								SetPlayerStats(int index, const APlayerStats newStats);
		struct APlayerStats					GetCloudStats();
		void								SetCloudStats(const APlayerStats newState);
		struct APlayerAttributes			GetPlayerAttributes(int index);
		void								SetPlayerAttributes(int index, const APlayerAttributes newAttributes);
		struct APlayerAttributes			GetCloudAttributes();
		void								SetCloudAttributes(const APlayerAttributes newAttributes);
		struct AMateria*					GetMateria();
		struct AItem*						GetItems();
	};	//Size: 0x0B28

	class AGameBase
	{
		__int32								MatchState0;			//0x0000	//	0x08 at main menu	|	0x2 in story
		__int32								MatchState1;			//0x0004	//	0x01 at main menu	|	0x1 in story
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

	struct OnUseItem
	{
		char								pad_0000[24];			//0x0000
		struct ACloudState*					pCloudState;			//0x0018	//	AGameState->mCloudStats
		char								pad_0020[40];			//0x0020
		//	struct AComponents*					pComponents;			//0x0048
		__int64**							ppInventory;			//0x0048
		char								pad_0050[48];			//0x0050

		//	
		class AGameState*					GetGameState();
		struct AInventory*					GetInventory();
		struct AItem*						GetCurrentItemSlot();
		struct AItem*						GetItemSlot(int index = 0);
		int									GetCurrentItemCount();
	};	//Size: 0x0080

	struct OnSetHealth
	{
		class AGameState*					pGameState{ nullptr };
		struct APlayerStats					PlayerStats;
		int									index{ 0 };
		int									Diff{ 0 };
		int									NewHP{ 0 };
		bool								bHealing{ false };
		bool								bTakingDmg{ false };

		OnSetHealth();
		OnSetHealth(int i, int health);
	};

	struct OnSetMana
	{
		class AGameState*					pGameState{ nullptr };
		struct APlayerStats					PlayerStats;
		int									index{ 0 };
		int									Diff{ 0 };
		int									NewMP{ 0 };
		bool								bRestoring{ false };
		bool								bUsing{ false };

		OnSetMana();
		OnSetMana(int i, int mana);
	};

	class ATarget
	{
	public:	//	@TODO: make private
		int									Level;			//0x0008
		float								SpAtkTime;		//0x000C
		float								SpAtkTimeMax;	//0x0010
		float								AttackRate;		//0x0014
		int									HP;				//0x0018
		int									HPMax;			//0x001C
		char								pad_0020[8];	//0x0020
		int									Attack;			//0x0028
		int									MagicAtk;		//0x002C
		int									Defense;		//0x0030
		int									MagicDefense;	//0x0034
		char								pad_0038[8];	//0x0038

	public:	
		virtual void						Function0();
		virtual int							GetLevel() = 0;
		virtual void						SetLevel(int lvl);
		virtual float						GetSpAtkTime() = 0;
		virtual void						SetSpAtkTime(float time);
		virtual float						GetSpAtkTimeMax() = 0;
		virtual void						SetSpAtkTimeMax(float maxTime);
		virtual float						GetAttackRate() = 0;
		virtual void						SetAttackRate(float rate);
		virtual int							GetHP() = 0;
		virtual void						SetHP(int hp);
		virtual int							GetHPMax() = 0;
		virtual void						SetHPMax(int mp);
		virtual void						Function13();
		virtual void						Function14();
		virtual void						Function15();
		virtual void						Function16();
		virtual void						Function17();
		virtual void						Function18();
		virtual int							GetAttack() = 0;
		virtual void						SetAttack(int atk);
		virtual int							GetMagicAtk() = 0;
		virtual void						SetMagicAtk(int atk);
		virtual int							GetDefense() = 0;
		virtual void						SetDefense(int def);
		virtual int							GetMagicDef() = 0;
		virtual void						SetMagicDef(int def);
		virtual void						Function27();	
		virtual void						Function28();
		virtual void						Function29();
		virtual void						Function30();
		virtual void						Function31();
		virtual void						Function32();
		virtual void						Function33();
		virtual void						Function34();
		virtual void						Function35();
		virtual void						Function36();

	public:
		bool								IsValid();		//	checks if matching vftable address
	};	//Size: 0x0040

	class ATargetStagger
	{
	public:	//	@TODO: make private
		unsigned char						pad_0000[0xCF8];		//	0x0000
		float								Stagger;				//	0x0CF8
		float								StaggerMax;				//	0x0CFC

	public:
		//	contains virtual functions for setting and getting stagger / max stagger but indexes are very high
	};

}
