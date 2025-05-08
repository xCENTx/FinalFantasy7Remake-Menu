#pragma once
#include <Engine.h>
#include <Menu.h>

namespace FF7Remake 
{
	/*
	*		GENERAL GUIDELINES
	
	//	classes , structs, methods and members
	*	namespace		: global game member variables. should be constexpr as the values will never change.
	*	struct			: offsets arranged with padding to align with game memory. member variables are public by default.
	*	class			: implies the "struct" has virtual methods, member variables should be made private with methods for accessing data for safety
	*	enum			: should be as close to the origin data structure as possible. i.e EItemType would reside above AItem
	*	member vars		: [bool : b<name> : bValid] [enum : e<Name> : eType] [pointer : p<Name> : pInstance] [static pointer : g<Name>] [global : g_<prefix><Name> : g_bRunning]
	*	A<StructName>	: all game engine general purpose class and struct names should be prefixed with A to signify it is a game engine related data structure
	*	T<StructName>	: all game engine template class and struct names should be prefixed with T to signify that it is both a templated and game related data structure.
	*	S<StructName>	: all custom methods acting as wrappers to join game info should be prefixed with S to signify that it acts as an extention to the game
	*	C<ClassName>	: Similiar to S<StructName> all classes which are helper / wrapper methods for the game shall be prefixed with C to signifay that it acts as an extension to the game.

	*/
	
	namespace Offsets
	{
		constexpr auto						gObjects{ 0x539e410 };					//	48 8D 05 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? 48 8D 0D ? ? ? ? 48 89 05 ? ? ? ? 48 83 C4
		constexpr auto						oGameBase{ 0x57CA5E0 };					//	 : subtract 0x8 from the qword for oGameState
		constexpr auto						oGameState{ 0x57CA5E0 };				//	48 8B 05 ? ? ? ? 4C 89 B4 24 ? ? ? ? 44 0F B6 76
		constexpr auto						oGameBase_CloudState{ 0x880 };			//	Analyze APlayerState_SetHealth_hook
		constexpr auto						oGameBase_ItemsList{ 0x35640 };			//	Analyze APlayerState_SubItem_hook
		constexpr auto						oGameBase_MateriaList{ 0x20A8 };		//	
	};

	namespace FunctionOffsets
	{
		constexpr auto						fnXinputState{ 0x1D253A0 };				//	XInput_State_hook			; FF 15 ? ? ? ? 85 C0 0F 94 C1 - 0x8E	; __int64 __fastcall x__XInput_UpdateState(__int64)
		constexpr auto						fnSceneUpdate{ 0x16B9510 };				//	AScene_Update_hook			;	E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B 89 ? ? ? ? 48 83 C4	; __int64 __fastcall x__AScene_Update(__int64)
		constexpr auto						fnSetHealth{ 0x0AFDF80 };				//	APlayerState_SetHealth_hook	;	E8 ? ? ? ? 0F B6 CB E8 ? ? ? ? 8B D0	; __int64 __fastcall x__APlayerState_SubHealth(unsigned __int8, int)
		constexpr auto						fnSetMana{ 0x0AFE190 };					//	APlayerState_SetMana_hook	;	E8 ? ? ? ? 48 83 C6 ? 48 3B F5 0F 85 ? ? ? ? 4C 8B 74 24 ? 48 8B 7C 24 ? 48 8B 5C 24 ? 48 83 C4	; __int64 __fastcall x__APlayerState_SetMana(unsigned __int8, int)
		constexpr auto						fnSubItem{ 0x0B1F410 };					//	APlayerState_SubItem_hook	;	E8 ? ? ? ? B0 ? EB ? CC CC CC CC CC CC CC 48 89 5C 24 ? 57	; __int64 __fastcall x__APlayerState_SubItem(__int64, int)
		constexpr auto						fnTargetGetHP{ 0x0889710 };				//	ATargetEntity_GetHP_hook	;	E8 ? ? ? ? 8B C8 88 45 ? C1 F9 ? 48 8D 55 ? 88 4D ? 41 B8 ? ? ? ? 8B C8 C1 F8 ? C1 F9 ? 88 45 ? 48 8B 07 88 4D ? 48 8B CF FF 50 ? 48 8B 5C 24	; __int64 __fastcall x__ATargetEntity_GetHP(__int64)
		constexpr auto						fnTargetGetStaggerAmount{ 0x0891870 };	//	ATargetEntity_GetStaggerAmount_hook	;	48 8B 05 ? ? ? ? 48 39 41 ? 0F 94 C0 + 0x16	; float __fastcall x__ATargetEntity_GetStaggerAmount(__int64)
		constexpr auto                      fnGetHighlitedEquipment{ 0x0AFF020 };	//	GetHighlitedEquipment_hook	;	E8 ? ? ? ? 8B 85 ? ? ? ? 44 8B 8D ? ? ? ? 44 8B 85	; __int64 __fastcall _GetHighlitedEquipment(_QWORD *, __int64)
		constexpr auto						vfGetEquipmentByID{ 0x1996E80 };		//	vfGetEquipmentByID_hook		; __int64 __fastcall _vfGetEquipmentByID(__int64 a1, __int64 eqID)
		constexpr auto						fnSetGil{ 0xB232E0 };					//	AGameState_SetGil_hook		;	E8 ? ? ? ? 49 8B 87 ? ? ? ? 48 8B 88 ? ? ? ? 48 85 C9 74 ? 48 8B 89 ? ? ? ? E8 ? ? ? ? C7 45 ? ? ? ? ? 48 8D 0D ? ? ? ? 48 89 4D ? 48 8D 55 ? 0F 28 45 ? 66 0F 7F 45 ? E8 ? ? ? ? 8B 4D ? 8B D8	;	void __fastcall x__SetGil(__int64 a1, int newCount)
	}

	namespace VtableOffsets
	{
		constexpr auto						vfTargetEntity{ 0x4B4E128 };			//  Analyze ATargetEntity_GetHP_hook	;	48 8D 0D ? ? ? ? 48 89 78 ? 48 89 08 48 89 78	
	}

	

	class AGame
	{
	public:
		static class AGameBase*				gGameBase;				//	
		static int							iSelectedPlayerIndex;	//	selected player party index
		static bool							bSelectedPlayer[7];		//  selected player party member flags
		static bool							bDemiGod;				//	prevents damage events < health
		static bool							bDemiGodMagic;			//	sets demi god to magic < magic defense
		static bool							bMaxLimit;				//	sets max limit
		static bool							bMaxATB;				//	sets max ATB guags
		static bool							bMaxGil;				//	sets gil to max amount and prevents loss of gil
		static bool							bPauseGame;				//	pauses the game
		static bool							bNullDmg;				//	disables health loss on damage events
		static bool							bNullMgk;				//	disables mana loss on cast
		static bool							bNullItem;				//	disables item loss on use
		static bool							bNullGil;				//	disables gil loss on purchases
		static bool							bRefundGil;				//	gain gil equal to what would be spent
		static bool							bGilMp;					//	enables a gil multiplier on gain events
		static int							iGilMpScalar;			//	gil multiplier
		static bool							bModTimeScale;			//	
		static float						fTimeScalar;			//	
		static bool							bModTargetLevel;		//	
		static int							iLevelScalar;			//	
		static bool							bKillTarget;			//	kills the selected target
		static bool							bNoTargetAttack;		//	target doesnt attack
		static bool							bNullTargetDmg;			//	target takes no damage
		static bool							bTargetAlwaysStagger;	//	target defense is set to 0
		static bool							bXpFarm;				//	sets targets hp to 0, prevents targets from attacking , sets target stagger to max and sets target to max level for max reward
		static struct STargetInfo			sTargetEntity;			//  target entity struct

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
			static void						RefillPlayerHP(int index);
			static void						RefillPlayerMP(int index);
			static void						PlayerMaxLimit(int index);
			static void						PlayerMaxATB(int index);
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

			typedef void(__fastcall* AGameState_SetGil)(__int64, int);
			static void __fastcall AGameState_SetGil_hook(__int64 a1, int a2);
			static AGameState_SetGil AGameState_SetGil_stub;
			static __int64 pAGameState_SetGil;

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

	public:
		struct Helpers
		{
			static class AGameState* GetGameState();
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
		char								pad_0004[4];				//0x0004
		int									Valid;						//0x0008
		int									Count;						//0x000C
		enum EItemType						eItemType;					//0x0010
		char								pad_0014[4];				//0x0014

	public:
		bool								IsItem();
		__int32								GetID();
		std::string							GetName();
		std::string							GetName(int index);
	};	//Size: 0x0018

	enum EMateria : unsigned __int32
	{
		//	MAGIC
		EMateria_Healing = 0x2711,
		EMateria_Cleansing = 0x2712,
		EMateria_Revival = 0x2713,
		EMateria_Fire = 0x2714,
		EMateria_Ice = 0x2715,
		EMateria_Lightning = 0x2716,
		EMateria_UnkMagic0 = 0x2718,
		EMateria_UnkMagic1 = 0x2719,
		EMateria_UnkMagic2 = 0x271A,
		EMateria_Barrier = 0x271B,
		EMateria_UnkMagic3 = 0x271C,

		//	SUPPORT
		EMateria_UnkSupport0 = 0x2AF9,
		EMateria_Elemental = 0x2AFA,
		EMateria_UnkSupport1 = 0x2AFA,
		EMateria_UnkSupport2 = 0x2AFF,

		//	COMMAND
		EMateria_Assess = 0x2EE2,
		EMateria_Chakra = 0x2EE4,
		EMateria_Prayer = 0x2EE5,
		EMateria_DeadlyDodge = 0x32D4,

		//	BUFF
		EMateria_AutoCure = 0x32D7,
		EMateria_UnkBuff0 = 0x32CA,
		EMateria_UnkBuff1 = 0x32D4,	
		EMateria_UnkBuff2 = 0x32DA,	
		EMateria_UnkBuff3 = 0x32CA,
		EMateria_UnkBuff4 = 0x32CB,
		EMateria_UnkBuff5 = 0x32CC,
		EMateria_UnkBuff6 = 0x36B1,
		EMateria_UnkBuff7 = 0x36B2,
		EMateria_UnkBuff8 = 0x36B3,
		EMateria_UnkBuff9 = 0x36B6,
		EMateria_UnkBuff10 = 0x36B7,
		EMateria_UnkBuff11 = 0x36B8,
		EMateria_UnkBuff12 = 0x36B9,
	};

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

	//	@TODO: retrieve information from the assess target page. 
	//	- there should be a function to retrieve this data
	struct STargetInfo
	{
		bool								bValid{ false };		//	OSD
		int									Level{ 0 };
		float								SpAtkTime{ 0.0f };
		float								SpAtkTimeMax{ 0.0f };
		float								AttackRate{ 0.0f };
		int									HP{ 0 };
		int									HPMax{ 0 };
		int									Attack{ 0 };
		int									MagicAtk{ 0 };
		int									Defense{ 0 };
		int									MagicDefense{ 0 };
		float								Stagger{ 0.0f };
		float								StaggerMax{ 0.0f };

		bool								Update();
		void								StaggerUpdate(class ATargetStagger* sInfo);
		void								ClearTarget();
		bool								IsCurrentTarget(class ATarget* pCmp);

		STargetInfo();
		STargetInfo(ATarget* p);
		
	private:
		class ATarget*						pTarget{ nullptr };
	};
}
