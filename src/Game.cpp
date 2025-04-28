#pragma once
#include <Game.h>

namespace FF7Remake 
{
	using namespace DX11Base;

	//	STATICS
	AGameBase*										AGame::gGameBase{ nullptr };
	int												AGame::iSelectedPlayerIndex{ false };
	bool											AGame::bSelectedPlayer[7]{ false };
	bool											AGame::bDemiGod{ false };
	bool											AGame::bDemiGodMagic{ false };
	bool											AGame::bMaxLimit{ false };
	bool											AGame::bMaxATB{ false };
	bool											AGame::bPauseGame{ false };
	bool											AGame::bNullDmg{ false };
	bool											AGame::bNullMgk{ false };
	bool											AGame::bNullItem{ false };
	bool											AGame::bModTimeScale{ false };
	float											AGame::fTimeScalar{ 1.0f };
	bool											AGame::bModTargetLevel{ false };
	int												AGame::iLevelScalar{ 1 };
	bool											AGame::bKillTarget{ false };
	bool											AGame::bNoTargetAttack{ false };		//	target doesnt attack
	bool											AGame::bNullTargetDmg{ false };			//	target takes no damage
	bool											AGame::bTargetAlwaysStagger{ false };	//	target defense is set to 0
	bool											AGame::bXpFarm{ false };				//	sets targets hp to 0, prevents targets from attacking , sets target stagger to max and sets target to max level for max reward
	STargetInfo										AGame::sTargetEntity{};					//	structure contains last most recent target entity information obtained in ATargetEntity_GetHP_hook
	__int64											AGame::Hooks::pXInput_State{ 0 };
	__int64											AGame::Hooks::pAScene_Update{ 0 };
	__int64											AGame::Hooks::pAPlayerState_SetHealth{ 0 };
	__int64											AGame::Hooks::pAPlayerState_SetMana{ 0 };
	__int64											AGame::Hooks::pAPlayerState_SubItem{ 0 };
	__int64											AGame::Hooks::pATargetEntity_GetHP{ 0 };
	__int64											AGame::Hooks::pATargetEntity_GetStaggerAmount{ 0 };
	AGame::Hooks::XInput_State						AGame::Hooks::XInput_State_stub;
	AGame::Hooks::AScene_Update						AGame::Hooks::AScene_Update_stub;
	AGame::Hooks::APlayerState_SetHealth			AGame::Hooks::APlayerState_SetHealth_stub;
	AGame::Hooks::APlayerState_SetMP				AGame::Hooks::APlayerState_SetMana_stub;
	AGame::Hooks::APlayerState_SubItem				AGame::Hooks::APlayerState_SubItem_stub;
	AGame::Hooks::ATargetEntity_GetHP				AGame::Hooks::ATargetEntity_GetHP_stub;
	AGame::Hooks::ATargetEntity_GetStaggerAmount	AGame::Hooks::ATargetEntity_GetStaggerAmount_stub;

	//----------------------------------------------------------------------------------------------------
	//										AGAME
	//-----------------------------------------------------------------------------------
#pragma region	//	AGAME

	void AGame::InitGame()
	{

		gGameBase									= reinterpret_cast<AGameBase*>(g_Engine->g_GameBaseAddr + Offsets::oGameBase);
		bSelectedPlayer[0]							= true;
		Hooks::pXInput_State						= (g_Engine->g_GameBaseAddr + FunctionOffsets::fnXinputState);
		Hooks::pAScene_Update						= (g_Engine->g_GameBaseAddr + FunctionOffsets::fnSceneUpdate);
		Hooks::pAPlayerState_SetHealth				= (g_Engine->g_GameBaseAddr + FunctionOffsets::fnSetHealth);
		Hooks::pAPlayerState_SetMana				= (g_Engine->g_GameBaseAddr + FunctionOffsets::fnSetMana);
		Hooks::pAPlayerState_SubItem				= (g_Engine->g_GameBaseAddr + FunctionOffsets::fnSubItem);
		Hooks::pATargetEntity_GetHP					= (g_Engine->g_GameBaseAddr + FunctionOffsets::fnTargetGetHP);
		Hooks::pATargetEntity_GetStaggerAmount		= (g_Engine->g_GameBaseAddr + FunctionOffsets::fnTargetGetStaggerAmount);



		//	Controller Input Handler
		if (Hooks::pXInput_State)
			Hooking::CreateHook((LPVOID)Hooks::pXInput_State, &Hooks::XInput_State_hook, (void**)&Hooks::XInput_State_stub);

		//	Render Scene Update 
		if (Hooks::pAScene_Update)
			Hooking::CreateHook((LPVOID)Hooks::pAScene_Update, &Hooks::AScene_Update_hook, (void**)&Hooks::AScene_Update_stub);

		//	Party Set Health Handler
		if (Hooks::pAPlayerState_SetHealth)
			Hooking::CreateHook((LPVOID)Hooks::pAPlayerState_SetHealth, &Hooks::APlayerState_SetHealth_hook, (void**)&Hooks::APlayerState_SetHealth_stub);

		//	Party Set Mana Handler
		if (Hooks::pAPlayerState_SetMana)
			Hooking::CreateHook((LPVOID)Hooks::pAPlayerState_SetMana, &Hooks::APlayerState_SetMana_hook, (void**)&Hooks::APlayerState_SetMana_stub);

		//	Party Sub Item Handler
		if (Hooks::pAPlayerState_SubItem)
			Hooking::CreateHook((LPVOID)Hooks::pAPlayerState_SubItem, &Hooks::APlayerState_SubItem_hook, (void**)&Hooks::APlayerState_SubItem_stub);

		//	Target Entity Handler
		if (Hooks::pATargetEntity_GetHP)
			Hooking::CreateHook((LPVOID)Hooks::pATargetEntity_GetHP, &Hooks::ATargetEntity_GetHP_hook, (void**)&Hooks::ATargetEntity_GetHP_stub);

		//	Target Entity Stagger Handler
		if (Hooks::pATargetEntity_GetStaggerAmount)
			Hooking::CreateHook((LPVOID)Hooks::pATargetEntity_GetStaggerAmount, &Hooks::ATargetEntity_GetStaggerAmount_hook, (void**)&Hooks::ATargetEntity_GetStaggerAmount_stub);
	}

	void AGame::ShutdownGame()
	{
		if (Hooks::pXInput_State)
			Hooking::DisableHook((LPVOID)Hooks::pXInput_State);

		if (Hooks::pAScene_Update)
			Hooking::DisableHook((LPVOID)Hooks::pAScene_Update);

		if (Hooks::pAPlayerState_SetHealth)
			Hooking::DisableHook((LPVOID)Hooks::pAPlayerState_SetHealth);

		if (Hooks::pAPlayerState_SetMana)
			Hooking::DisableHook((LPVOID)Hooks::pAPlayerState_SetMana);

		if (Hooks::pAPlayerState_SubItem)
			Hooking::DisableHook((LPVOID)Hooks::pAPlayerState_SubItem);

		if (Hooks::pATargetEntity_GetHP)
			Hooking::DisableHook((LPVOID)Hooks::pATargetEntity_GetHP);

		if (Hooks::pATargetEntity_GetStaggerAmount)
			Hooking::DisableHook((LPVOID)Hooks::pATargetEntity_GetStaggerAmount);
	}

#pragma endregion

	//----------------------------------------------------------------------------------------------------
	//										AGAME::PATCHES
	//-----------------------------------------------------------------------------------
#pragma region	//	AGAME::PATCHES

	void AGame::Patches::RefillCloudHP()
	{
		AGameState* pGameState = gGameBase->GetGameState();
		if (!pGameState)
			return;

		//	Get cloud player stats
		APlayerStats cloud_stats = pGameState->GetCloudStats();
		cloud_stats.RefillHP();	//	set hp var to match max hp

		//	 Set cloud new player stats
		pGameState->SetCloudStats(cloud_stats);
	}

	void AGame::Patches::RefillCloudMP()
	{
		AGameState* pGameState = gGameBase->GetGameState();
		if (!pGameState)
			return;

		//	Get cloud player stats
		APlayerStats cloud_stats = pGameState->GetCloudStats();
		cloud_stats.RefillMana();

		//	 Set cloud new player stats
		pGameState->SetCloudStats(cloud_stats);
	}

	void AGame::Patches::CloudMaxLimit()
	{
		AGameState* pGameState = gGameBase->GetGameState();
		if (!pGameState)
			return;

		//	Get cloud player stats
		APlayerStats cloud_stats = pGameState->GetCloudStats();
		cloud_stats.SetMaxLimit();

		//	 Set cloud new player stats
		pGameState->SetCloudStats(cloud_stats);
	}

	void AGame::Patches::CloudMaxATB()
	{
		AGameState* pGameState = gGameBase->GetGameState();
		if (!pGameState)
			return;

		//	Get cloud player stats
		APlayerStats cloud_stats = pGameState->GetCloudStats();
		cloud_stats.SetMaxATB();

		//	 Set cloud new player stats
		pGameState->SetCloudStats(cloud_stats);
	}

	void AGame::Patches::RefillPartyHP()
	{
		AGameState* pGameState = gGameBase->GetGameState();
		if (!pGameState)
			return;

		for (int i = 0; i < 6; i++)
		{
			APlayerStats player_stats = pGameState->GetPlayerStats(i);
			player_stats.RefillHP();

			pGameState->SetPlayerStats(i, player_stats);
		}

		RefillCloudHP();
	}

	void AGame::Patches::RefillPartyMP()
	{
		AGameState* pGameState = gGameBase->GetGameState();
		if (!pGameState)
			return;

		for (int i = 0; i < 6; i++)
		{
			APlayerStats player_stats = pGameState->GetPlayerStats(i);
			player_stats.RefillMana();

			pGameState->SetPlayerStats(i, player_stats);
		}

		RefillCloudMP();
	}

	void AGame::Patches::PartyMaxLimit()
	{
		AGameState* pGameState = gGameBase->GetGameState();
		if (!pGameState)
			return;
		
		for (int i = 0; i < 6; i++)
		{
			APlayerStats player_stats = pGameState->GetPlayerStats(i);
			player_stats.SetMaxLimit();
				
			pGameState->SetPlayerStats(i, player_stats);
		}

		CloudMaxLimit();
	}

	void AGame::Patches::PartyMaxATB()
	{
		AGameState* pGameState = gGameBase->GetGameState();
		if (!pGameState)
			return;

		for (int i = 0; i < 6; i++)
		{
			APlayerStats player_stats = pGameState->GetPlayerStats(i);
			player_stats.SetMaxATB();

			pGameState->SetPlayerStats(i, player_stats);
		}

		CloudMaxATB();
	}

	void AGame::Patches::RefillPlayerHP(int index)
	{
		AGameState* pGameState = gGameBase->GetGameState();
		if (!pGameState)
			return;

		if (index == 0)
		{
			RefillCloudHP();
			return;
		}

		APlayerStats player_stats = pGameState->GetPlayerStats(index);
		player_stats.RefillHP();
		pGameState->SetPlayerStats(index, player_stats);
	}

	void AGame::Patches::RefillPlayerMP(int index)
	{
		AGameState* pGameState = gGameBase->GetGameState();
		if (!pGameState)
			return;

		if (index == 0)
		{
			RefillCloudMP();
			return;
		}
		
		APlayerStats player_stats = pGameState->GetPlayerStats(index);
		player_stats.RefillMana();
		pGameState->SetPlayerStats(index, player_stats);
	}

	void AGame::Patches::PlayerMaxLimit(int index)
	{
		AGameState* pGameState = gGameBase->GetGameState();
		if (!pGameState)
			return;

		if (index == 0)
		{
			CloudMaxLimit();
			return;
		}

		APlayerStats player_stats = pGameState->GetPlayerStats(index);
		player_stats.SetMaxLimit();
		pGameState->SetPlayerStats(index, player_stats);
	}

	void AGame::Patches::PlayerMaxATB(int index)
	{
		AGameState* pGameState = gGameBase->GetGameState();
		if (!pGameState)
			return;

		if (index == 0)
		{
			CloudMaxATB();
			return;
		}

		APlayerStats player_stats = pGameState->GetPlayerStats(index);
		player_stats.SetMaxATB();
		pGameState->SetPlayerStats(index, player_stats);
	}

#pragma endregion

	//----------------------------------------------------------------------------------------------------
	//										AGAME::HOOKS
	//-----------------------------------------------------------------------------------
#pragma region	//	AGAME::HOOKS

	//	
	__int64 AGame::Hooks::XInput_State_hook(__int64 a1)
	{
		///	PORT NOTES
		/*
			//	AOB: 48 8B C4 48 89 58 ? 48 89 70 ? 48 89 78 ? 55 41 54 41 55 41 56 41 57 48 8D 68 ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 44 0F 29 48 ? 44 0F 29 50 ? 44 0F 29 98 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B D9
		*/

		//	Whenever the menu is shown , we wont pass controller inputs to the game
		if (g_Engine->m_ShowMenu)
			return 0;

		return XInput_State_stub(a1);
	}

	//	
	void AGame::Hooks::AScene_Update_hook(__int64 p)
	{
		/// PORT NOTES
		/*
			// AOB: E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B 89 ? ? ? ? 48 83 C4
			//	STUB: void __fastcall sub_1416B44A0(__int64 a1)
			//	INSTRUCTION:   *(_BYTE *)(a1 + 0x4FC) = 0;
			//	ASM: mov     byte ptr [rcx+4FCh], 0

			This function is constantly executed. xref the function in IDA to get the following calling convention
			{
				v18 = *(_QWORD *)(qword_1457B95B0 + 0x3D0);	//	method of dynamic analysis
				if ( !v18 || !(unsigned __int8)sub_1416D4720(*(_QWORD *)(qword_1457B95B0 + 0x3D0)) )
				  v18 = 0i64;
				sub_1416B44A0(v18);	//	this function
			}

			Using ReClass one could look at "p" [  qword_1457B95B0 + 0x3D0 ] while pausing the game to visually see changes being made.
			Additional information will be obtained by utilizing "Tactical Mode" in game. This will show a float value of 1.0 changing to 0.10f to signify the time scale shift.

			We can simulate pausing the game by hooking the function and returning shortly after apply a hack to force time scale to 0 and set the pause flag to 1.

			//	FINDING AGAIN
			This function can originally be found by doing a memory scan of changed values 1 - 0 when pausing the game. After finding the variable in question you can xref what changes the value to get this function.

		*/

		auto pScene = reinterpret_cast<AScene*>(p);
		if (pScene && g_Engine->m_ShowMenu)
		{
			//	@TODO: this doesnt make the pause menu show up , however setting this flag requires the user to manually unpause the game. 
			//	pScene->SetPauseState(true);
			pScene->SetTimeScale(0.00f);
		}

		if (pScene && AGame::bPauseGame)
			pScene->SetTimeScale(pScene->GetTimeScale() * 0.0f);

		if (pScene && AGame::bModTimeScale)
			pScene->SetTimeScale(AGame::fTimeScalar);

		//	exec original fn
		AScene_Update_stub(p);
	}

	//	sets hp to party members by traditional game mechanics
	__int64 AGame::Hooks::APlayerState_SetHealth_hook(unsigned __int8 index, int health)
	{
		///	PORT NOTES
		/*

			// AOB:	E8 ? ? ? ? 0F B6 CB E8 ? ? ? ? 8B D0
			//	STUB:	__int64 __fastcall APlayerState_SubHealth(unsigned __int8, int)
			//	INSTRUCTION:	*(_DWORD *)(((unsigned __int64)a1 << 6) + result + 0x30) = a2;
			//	ASM:	mov     [rcx+rax+30h], edi

			//	FINDING AGAIN
			This function is relatively easy to find.
			First find Clouds HP by doing some scans on changed values in between taking damage from enemies.
			Figure out which function is adjusting the health value by checking what changes the hp value.
			[NOTE] this function is also good for inspecting "AGameState" and obtaining the new global pointer to the class and contained structures

			.text:0000000140AFB6C0                 mov     [rsp+arg_0], rbx																//
			.text:0000000140AFB6C5                 push    rdi																			//
			.text:0000000140AFB6C6                 sub     rsp, 20h																		//
			.text:0000000140AFB6CA                 mov     rax, cs:qword_1457B9268														//	this points to AGameState
			.text:0000000140AFB6D1                 mov     edi, edx																		//
			.text:0000000140AFB6D3                 movzx   ebx, cl																		//
			.text:0000000140AFB6D6                 test    rax, rax																		//
			.text:0000000140AFB6D9                 jnz     short loc_140AFB715															//
			.text:0000000140AFB6DB                 mov     rcx, cs:qword_1457F5148														//
			.text:0000000140AFB6E2                 test    rcx, rcx																		//
			.text:0000000140AFB6E5                 jnz     short loc_140AFB6F3															//
			.text:0000000140AFB6E7                 call    sub_141C22CC0																//
			.text:0000000140AFB6EC                 mov     rcx, cs:qword_1457F5148														//
			.text:0000000140AFB6F3																										//
			.text:0000000140AFB6F3 loc_140AFB6F3:                          																//
			.text:0000000140AFB6F3                 mov     rax, [rcx]																	//
			.text:0000000140AFB6F6                 xor     r8d, r8d																		//
			.text:0000000140AFB6F9                 mov     edx, 0B6DF0h																	//
			.text:0000000140AFB6FE                 call    qword ptr [rax+10h]															//
			.text:0000000140AFB701                 test    rax, rax																		//
			.text:0000000140AFB704                 jz      short loc_140AFB70E															//
			.text:0000000140AFB706                 mov     rcx, rax																		//
			.text:0000000140AFB709                 call    sub_140B26300																//
			.text:0000000140AFB70E																										//
			.text:0000000140AFB70E loc_140AFB70E:                          																//
			.text:0000000140AFB70E                 mov     cs:qword_1457B9268, rax														//
			.text:0000000140AFB715																										//
			.text:0000000140AFB715 loc_140AFB715:                          																//
			.text:0000000140AFB715                 mov     rax, [rax+0B6D80h]															//
			.text:0000000140AFB71C                 cmp     bl, 8																		//
			.text:0000000140AFB71F                 jnb     short loc_140AFB73C															//
			.text:0000000140AFB721                 test    byte ptr cs:dword_1457B9260, 10h												//
			.text:0000000140AFB728                 ja      short loc_140AFB73C															//
			.text:0000000140AFB72A                 mov     rax, [rax+3E60h]																//
			.text:0000000140AFB731                 movzx   ecx, bl																		//
			.text:0000000140AFB734                 shl     rcx, 6																		//
			.text:0000000140AFB738                 mov     [rcx+rax+30h], edi															//	[!] This instruction subtracts hp from party members
			.text:0000000140AFB73C																										//
			.text:0000000140AFB73C loc_140AFB73C:                          																//
			.text:0000000140AFB73C                 mov     rbx, [rsp+28h+arg_0]															//
			.text:0000000140AFB741                 add     rsp, 20h																		//
			.text:0000000140AFB745                 pop     rdi																			//
			.text:0000000140AFB746                 retn
		*/

		//	Generate a structure based on the input params
		//	- Party Member Index & Stats
		auto pSetHealth = OnSetHealth(index, health);

		if (g_Console->m_bVerbose && pSetHealth.Diff > 0)
			Console::Log("[+] [Hooking::APlayerState_SetHealth_hook(%d, %d)]\n- diff: %d\n- isTakeDmg: %d\n- isHealing: %d\n- origHealth: %d / %d\n- newHealth: %d / %d\n- bNullDmg: %d\n\n",
				index, health, pSetHealth.Diff, pSetHealth.bTakingDmg, pSetHealth.bHealing, health + pSetHealth.Diff, pSetHealth.PlayerStats.MaxHP, health, pSetHealth.PlayerStats.MaxHP, AGame::bNullDmg);

		//	prevent damage to party member
		if (AGame::bNullDmg && pSetHealth.bTakingDmg)
			return 0;

		//	exec original fn
		return APlayerState_SetHealth_stub(index, health);
	}

	//	sets mp to party members by traditional game mechanics
	__int64 AGame::Hooks::APlayerState_SetMana_hook(unsigned __int8 index, int mana)
	{
		///	PORT NOTES
		/*
			// AOB:	E8 ? ? ? ? 48 83 C6 ? 48 3B F5 0F 85 ? ? ? ? 4C 8B 74 24 ? 48 8B 7C 24 ? 48 8B 5C 24 ? 48 83 C4
			//	STUB:	__int64 __fastcall APlayerState_SetMp(unsigned __int8 a1, int a2)
			//	INSTRUCTION:	*(_DWORD *)(result + ((unsigned __int64)a1 << 6) + 56) = a2;
			//	ASM:	mov [rax+rcx+38],edi


			.text:0000000140AFB8D0 ; __int64 __fastcall APlayerState_SetMp(unsigned __int8, int)
			.text:0000000140AFB8D0 APlayerState_SetMp proc near
			.text:0000000140AFB8D0
			.text:0000000140AFB8D0 arg_0           = qword ptr  8
			.text:0000000140AFB8D0
			.text:0000000140AFB8D0                 mov     [rsp+arg_0], rbx
			.text:0000000140AFB8D5                 push    rdi
			.text:0000000140AFB8D6                 sub     rsp, 20h
			.text:0000000140AFB8DA                 mov     rax, cs:qword_1457B9268
			.text:0000000140AFB8E1                 mov     edi, edx
			.text:0000000140AFB8E3                 movzx   ebx, cl
			.text:0000000140AFB8E6                 test    rax, rax
			.text:0000000140AFB8E9                 jnz     short loc_140AFB925
			.text:0000000140AFB8EB                 mov     rcx, cs:qword_1457F5148
			.text:0000000140AFB8F2                 test    rcx, rcx
			.text:0000000140AFB8F5                 jnz     short loc_140AFB903
			.text:0000000140AFB8F7                 call    sub_141C22CC0
			.text:0000000140AFB8FC                 mov     rcx, cs:qword_1457F5148
			.text:0000000140AFB903
			.text:0000000140AFB903 loc_140AFB903:
			.text:0000000140AFB903                 mov     rax, [rcx]
			.text:0000000140AFB906                 xor     r8d, r8d
			.text:0000000140AFB909                 mov     edx, 0B6DF0h
			.text:0000000140AFB90E                 call    qword ptr [rax+10h]
			.text:0000000140AFB911                 test    rax, rax
			.text:0000000140AFB914                 jz      short loc_140AFB91E
			.text:0000000140AFB916                 mov     rcx, rax
			.text:0000000140AFB919                 call    sub_140B26300
			.text:0000000140AFB91E
			.text:0000000140AFB91E loc_140AFB91E:
			.text:0000000140AFB91E                 mov     cs:qword_1457B9268, rax
			.text:0000000140AFB925
			.text:0000000140AFB925 loc_140AFB925:
			.text:0000000140AFB925                 cmp     bl, 8
			.text:0000000140AFB928                 jnb     short loc_140AFB943
			.text:0000000140AFB92A                 mov     rax, [rax+0B6D80h]
			.text:0000000140AFB931                 movzx   ecx, bl
			.text:0000000140AFB934                 shl     rcx, 6
			.text:0000000140AFB938                 mov     rax, [rax+3E60h]
			.text:0000000140AFB93F                 mov     [rax+rcx+38h], edi
			.text:0000000140AFB943
			.text:0000000140AFB943 loc_140AFB943:
			.text:0000000140AFB943                 mov     rbx, [rsp+28h+arg_0]
			.text:0000000140AFB948                 add     rsp, 20h
			.text:0000000140AFB94C                 pop     rdi
			.text:0000000140AFB94D                 retn
			.text:0000000140AFB94D APlayerState_SetMp endp

			__int64 __fastcall APlayerState_SetMp(unsigned __int8 a1, int a2)
			{
			  __int64 result; // rax
			  __int64 v5; // rcx

			  result = qword_1457B9268;
			  if ( !qword_1457B9268 )
			  {
				v5 = qword_1457F5148;
				if ( !qword_1457F5148 )
				{
				  sub_141C22CC0();
				  v5 = qword_1457F5148;
				}
				result = (*(__int64 (__fastcall **)(__int64, __int64, _QWORD))(*(_QWORD *)v5 + 16i64))(v5, 749040i64, 0i64);
				if ( result )
				  result = sub_140B26300(result);
				qword_1457B9268 = result;
			  }
			  if ( a1 < 8u )
			  {
				result = *(_QWORD *)(*(_QWORD *)(result + 748928) + 15968i64);
				*(_DWORD *)(result + ((unsigned __int64)a1 << 6) + 56) = a2;
			  }
			  return result;
			}
		*/

		//	Generate a structure based on the input params
		//	- Party Member Index & Stats
		auto pSetMana = OnSetMana(index, mana);

		if (g_Console->m_bVerbose && pSetMana.Diff > 0)
			Console::Log("[+] [Hooking::APlayerState_SetMana_hook(%d, %d)]\n- diff: %d\n- isUsingMana: %d\n- isHealingMana: %d\n- origMana: %d / %d\n- newMana: %d / %d\n- bNullMgk: %d\n\n",
				index, mana, pSetMana.Diff, pSetMana.bUsing, pSetMana.bRestoring, mana + pSetMana.Diff, pSetMana.PlayerStats.MaxMP, mana, pSetMana.PlayerStats.MaxMP, AGame::bNullMgk);

		//	prevent damage to party member
		if (AGame::bNullMgk && pSetMana.bUsing)
			return 0;

		//	exec original fn
		return APlayerState_SetMana_stub(index, mana);
	}

	//	
	__int64 AGame::Hooks::APlayerState_SubItem_hook(__int64 p, int index)
	{
		///	PORT NOTES
		/*
			// AOB:	E8 ? ? ? ? B0 ? EB ? CC CC CC CC CC CC CC 48 89 5C 24 ? 57 [ CALL ]
			//	STUB:	__int64 __fastcall APlayerState_SubItem(__int64 a1, int a2)
			//	INSTRUCTION:	v13 = *(_DWORD *)(v12 + 0xC) - *((_DWORD *)v11 + 3);
			//	ASM:	mov ecx,[rdx+0C]


			a1 + 0x18 = PlayerStats ( pCloudState or pPlayerStats for the user ? )
			a1 + 0x48 = InventoryIndex
			a1 + 0x48 + 0X0C = ItemCount

			v4 = a1 + 8i64 * a2;
			v11 = *(__int64 **)(v4 + 0x48); // inventory
			v12 = *v11;	// Slot
			v13 = *(_DWORD *)(v12 + 0xC) - *((_DWORD *)v11 + 3); // sub item



			//	FINDING AGAIN
			This function is relatively easy to find.
			First find an item by doing some scans on changed values in between using said item.
			Figure out which function is adjusting the count value by checking what changes the item count value.

			.text:0000000140B1CAF0 ; __int64 __fastcall APlayerState_SubItem(__int64, int)
			.text:0000000140B1CAF0 APlayerState_SubItem proc near
			.text:0000000140B1CAF0
			.text:0000000140B1CAF0 arg_0           = qword ptr  8
			.text:0000000140B1CAF0 arg_8           = qword ptr  10h
			.text:0000000140B1CAF0 arg_10          = qword ptr  18h
			.text:0000000140B1CAF0 arg_18          = qword ptr  20h
			.text:0000000140B1CAF0
			.text:0000000140B1CAF0                 mov     [rsp+arg_10], rbp
			.text:0000000140B1CAF5                 mov     [rsp+arg_18], rsi
			.text:0000000140B1CAFA                 push    rdi
			.text:0000000140B1CAFB                 sub     rsp, 20h
			.text:0000000140B1CAFF                 movsxd  rax, edx
			.text:0000000140B1CB02                 mov     rbp, rcx
			.text:0000000140B1CB05                 lea     rsi, ds:0[rax*8]
			.text:0000000140B1CB0D                 add     rsi, rcx
			.text:0000000140B1CB10                 mov     rdi, [rsi+48h]
			.text:0000000140B1CB14                 test    rdi, rdi
			.text:0000000140B1CB17                 jz      loc_140B1CC2A
			.text:0000000140B1CB1D
			.text:0000000140B1CB1D loc_140B1CB1D:
			.text:0000000140B1CB1D                 mov     [rsp+28h+arg_0], rbx
			.text:0000000140B1CB22                 mov     [rsp+28h+arg_8], r14
			.text:0000000140B1CB27                 call    sub_140FCB3D0
			.text:0000000140B1CB2C                 xor     r14d, r14d
			.text:0000000140B1CB2F                 test    al, al
			.text:0000000140B1CB31                 jz      loc_140B1CBCC
			.text:0000000140B1CB37                 test    rdi, rdi
			.text:0000000140B1CB3A                 jz      loc_140B1CBCC
			.text:0000000140B1CB40                 mov     ebx, r14d
			.text:0000000140B1CB43                 lea     rax, [rbp+368h]
			.text:0000000140B1CB4A                 mov     ecx, r14d
			.text:0000000140B1CB4D                 nop     dword ptr [rax]
			.text:0000000140B1CB50
			.text:0000000140B1CB50 loc_140B1CB50:
			.text:0000000140B1CB50                 cmp     [rax], r14
			.text:0000000140B1CB53                 jz      short loc_140B1CB66
			.text:0000000140B1CB55                 inc     ebx
			.text:0000000140B1CB57                 inc     rcx
			.text:0000000140B1CB5A                 add     rax, 8
			.text:0000000140B1CB5E                 cmp     rcx, 64h ; 'd'
			.text:0000000140B1CB62                 jl      short loc_140B1CB50
			.text:0000000140B1CB64                 jmp     short loc_140B1CBCC
			.text:0000000140B1CB66 ; ---------------------------------------------------------------------------
			.text:0000000140B1CB66
			.text:0000000140B1CB66 loc_140B1CB66:
			.text:0000000140B1CB66                 mov     rcx, cs:qword_1457F5148
			.text:0000000140B1CB6D                 test    rcx, rcx
			.text:0000000140B1CB70                 jnz     short loc_140B1CB7E
			.text:0000000140B1CB72                 call    sub_141C22CC0
			.text:0000000140B1CB77                 mov     rcx, cs:qword_1457F5148
			.text:0000000140B1CB7E
			.text:0000000140B1CB7E loc_140B1CB7E:
			.text:0000000140B1CB7E                 mov     rax, [rcx]
			.text:0000000140B1CB81                 xor     r8d, r8d
			.text:0000000140B1CB84                 lea     edx, [r8+18h]
			.text:0000000140B1CB88                 call    qword ptr [rax+10h]
			.text:0000000140B1CB8B                 mov     rcx, rax
			.text:0000000140B1CB8E                 test    rax, rax
			.text:0000000140B1CB91                 jz      short loc_140B1CBA7
			.text:0000000140B1CB93                 mov     [rax], r14
			.text:0000000140B1CB96                 mov     dword ptr [rax+8], 0FFFFFFFFh
			.text:0000000140B1CB9D                 mov     [rax+0Ch], r14d
			.text:0000000140B1CBA1                 mov     [rax+10h], r14b
			.text:0000000140B1CBA5                 jmp     short loc_140B1CBAA
			.text:0000000140B1CBA7 ; ---------------------------------------------------------------------------
			.text:0000000140B1CBA7
			.text:0000000140B1CBA7 loc_140B1CBA7:
			.text:0000000140B1CBA7                 mov     rcx, r14
			.text:0000000140B1CBAA
			.text:0000000140B1CBAA loc_140B1CBAA:
			.text:0000000140B1CBAA                 movsxd  rax, ebx
			.text:0000000140B1CBAD                 mov     [rbp+rax*8+368h], rcx
			.text:0000000140B1CBB5                 test    rcx, rcx
			.text:0000000140B1CBB8                 jz      short loc_140B1CBCC
			.text:0000000140B1CBBA                 mov     rax, [rdi]
			.text:0000000140B1CBBD                 mov     [rcx], rax
			.text:0000000140B1CBC0                 mov     eax, [rdi+8]
			.text:0000000140B1CBC3                 mov     [rcx+8], eax
			.text:0000000140B1CBC6                 mov     eax, [rdi+0Ch]
			.text:0000000140B1CBC9                 mov     [rcx+0Ch], eax
			.text:0000000140B1CBCC
			.text:0000000140B1CBCC loc_140B1CBCC:
			.text:0000000140B1CBCC
			.text:0000000140B1CBCC                 mov     rbx, [rsi+48h]
			.text:0000000140B1CBD0                 mov     rdx, [rbx]
			.text:0000000140B1CBD3                 test    rdx, rdx
			.text:0000000140B1CBD6                 jz      short loc_140B1CBF6
			.text:0000000140B1CBD8                 mov     ecx, [rdx+0Ch]
			.text:0000000140B1CBDB                 mov     eax, r14d
			.text:0000000140B1CBDE                 sub     ecx, [rbx+0Ch]
			.text:0000000140B1CBE1                 cmovns  eax, ecx
			.text:0000000140B1CBE4                 mov     [rdx+0Ch], eax
			.text:0000000140B1CBE7                 mov     dword ptr [rbx+8], 0FFFFFFFFh
			.text:0000000140B1CBEE                 mov     [rbx+0Ch], r14d
			.text:0000000140B1CBF2                 mov     rbx, [rsi+48h]
			.text:0000000140B1CBF6
			.text:0000000140B1CBF6 loc_140B1CBF6:
			.text:0000000140B1CBF6                 test    rbx, rbx
			.text:0000000140B1CBF9                 jz      short loc_140B1CC20
			.text:0000000140B1CBFB                 mov     rcx, cs:qword_1457F5148
			.text:0000000140B1CC02                 test    rcx, rcx
			.text:0000000140B1CC05                 jnz     short loc_140B1CC13
			.text:0000000140B1CC07                 call    sub_141C22CC0
			.text:0000000140B1CC0C                 mov     rcx, cs:qword_1457F5148
			.text:0000000140B1CC13
			.text:0000000140B1CC13 loc_140B1CC13:
			.text:0000000140B1CC13                 mov     rax, [rcx]
			.text:0000000140B1CC16                 mov     rdx, rbx
			.text:0000000140B1CC19                 call    qword ptr [rax+20h]
			.text:0000000140B1CC1C                 mov     [rsi+48h], r14
			.text:0000000140B1CC20
			.text:0000000140B1CC20 loc_140B1CC20:
			.text:0000000140B1CC20                 mov     rbx, [rsp+28h+arg_0]
			.text:0000000140B1CC25                 mov     r14, [rsp+28h+arg_8]
			.text:0000000140B1CC2A
			.text:0000000140B1CC2A loc_140B1CC2A:
			.text:0000000140B1CC2A
			.text:0000000140B1CC2A                 mov     rbp, [rsp+28h+arg_10]
			.text:0000000140B1CC2F                 mov     rsi, [rsp+28h+arg_18]
			.text:0000000140B1CC34                 add     rsp, 20h
			.text:0000000140B1CC38                 pop     rdi
			.text:0000000140B1CC39                 retn
			.text:0000000140B1CC39 APlayerState_SubItem endp
		*/


		///	IDA PSUEDOCODE
		/*
			v4 = a1 + 8i64 * a2;
			v11 = *(__int64 **)(v4 + 0x48); // inventory
			v12 = *v11;	// Slot
			v13 = *(_DWORD *)(v12 + 0xC) - *((_DWORD *)v11 + 3); // sub item

			//	ADJUSTED FOR READABILITY
			auto v4 = p + 8 * index;									// OnSubItem*
			AInventory* v11 = *(__int64**)(v4 + 0x48);					// inventory
			AItemSlot* v12 = reinterpret_cast<AItemSlot*>(*v11);		// ItemSlot
			int sub_amount = *((__int32*)v11 + 3);						// sub amount
			int v13 = v12->count - sub_amount;							// sub item new amount
		*/

		///	
		/*
			///	RECREATION
			//	auto pUseItem = reinterpret_cast<OnUseItem*> (p);
			//	AItemSlot oItem = pUseItem->GetInventory()->Item;

			///	Get Other Slots
			//	AItemSlot* slot = pUseItem->GetItemSlot(index + 1);
			//	auto slot_item_count = slot->count;
		*/

		auto v4 = p + 8 * index;									// OnSubItem*
		auto v11 = *(__int64**)(v4 + 0x48);							// inventory
		AItem* v12 = reinterpret_cast<AItem*>(*v11);				// ItemSlot
		int sub_amount = *((__int32*)v11 + 3);						// sub amount
		int v13 = v12->Count - sub_amount;							// sub item new amount

		if (g_Console->m_bVerbose)
			Console::Log("[+] [Hooking::APlayerState_SubItem(0x%llX, %d)]\n- subAmount: %d\n- origCount: %d\n- newCount: %d\n- bNullItem: %d\n\n",
				p, index, sub_amount, v12->Count, v13, AGame::bNullItem);

		if (AGame::bNullItem)
		{
			auto result = APlayerState_SubItem_stub(p, index);

			//	Set new amount ( revert change )
			v12->Count = (v13 + sub_amount);

			return result;
		}

		//	exec original fn
		return APlayerState_SubItem_stub(p, index);
	}

	//	
	__int64 AGame::Hooks::ATargetEntity_GetHP_hook(__int64 p)
	{
		static bool bEditing{ false };	//	used so can call this function [ pTarget->GetHP() ] // recursion safety
		auto pTarget = reinterpret_cast<ATarget*>(p);
		if (!bEditing && pTarget)
		{
			bEditing = true;
			bool bValid = pTarget->IsValid();

			if (bValid)
			{

				//	target level is adjusted
				if (AGame::bModTargetLevel)
					pTarget->SetLevel(iLevelScalar);

				//	target health is restored ( note: target can still die if damage taken is > maxhp )
				if (AGame::bNullTargetDmg)
					pTarget->SetHP(pTarget->GetHPMax());

				//	target wont attack player
				if (AGame::bNoTargetAttack)
				{
					//	Attack Rate
					pTarget->SetAttackRate(0.0f);

					//	Special Attack Timer
					pTarget->SetSpAtkTime(0.0f);

					//	Special Attack Threshold
					pTarget->SetSpAtkTimeMax(0.0f);
				}

				//	prevents targets from attacking , sets max level and sets defenses to 0
				//	- apply Auto Kill || Auto Stagger for increased effects
				if (AGame::bXpFarm)
				{
					//	Set Level for rewards
					pTarget->SetLevel(9999);

					//	prevent targets from attacking party
					pTarget->SetAttackRate(0.0f);

					//	prevent targets from using special attacks
					pTarget->SetSpAtkTimeMax(0.0f);

					//	set target defense to 0 for critical hits
					pTarget->SetDefense(0);

					//	set target magic defense to 0 for critical magic hits
					pTarget->SetMagicDef(0);
				}

				//	target is killed
				if (AGame::bKillTarget)
					pTarget->SetHP(0);

				AGame::sTargetEntity = STargetInfo(pTarget);
				if (!AGame::sTargetEntity.Update())
					AGame::sTargetEntity.ClearTarget();

			}
			else if (AGame::sTargetEntity.bValid && AGame::sTargetEntity.IsCurrentTarget(pTarget))
				AGame::sTargetEntity.ClearTarget();

			bEditing = false;
		}

		return ATargetEntity_GetHP_stub(p);
	}

	//	
	__int64 AGame::Hooks::ATargetEntity_GetStaggerAmount_hook(__int64 a1)
	{
		auto pEnt = reinterpret_cast<ATargetStagger*>(a1);

		if (pEnt && AGame::sTargetEntity.bValid)
			AGame::sTargetEntity.StaggerUpdate(pEnt);

		if (pEnt && AGame::bTargetAlwaysStagger)
				pEnt->Stagger = pEnt->StaggerMax;

		return ATargetEntity_GetStaggerAmount_stub(a1);
	}


#pragma endregion

	//----------------------------------------------------------------------------------------------------
	//										AITEM
	//-----------------------------------------------------------------------------------
#pragma region	//	AITEM

	bool AItem::IsItem()
	{
		bool result{ false };

		switch (eItemType)
		{
			case EItemType_Item: result = true; break;
			case EItemType_KeyItem: result = true; break;
		}

		if (Valid <= 0)
			result = false;

		return result;
	}

	__int32 AItem::GetID() { return this->ID; }

	std::string AItem::GetName()
	{
		std::string result;
		
		switch (ID)
		{
		//	case EItem_POTION: result = "Potion"; break;
		//	case EItem_ETHER: result = "Ether"; break;
		//	case EItem_GIL: result = "Gil"; break;
		//	case EItem_GRENADE: result = "Grenade"; break;
		//	case EItem_MOOGLE_MEDAL: result = "Moogle Medal"; break;
		//	case EItem_PHOENIX_DOWN: result = "Phoenix Down"; break;
		//	case EItem_HI_POTION: result = "Hi-Potion"; break;
		//	case EItem_YELLOW_FLOWER: result = "Yellow Flower"; break;
		//	case EItem_ADRENALINE: result = "Adrenaline"; break;
		//	case EItem_SEDATIVE: result = "Sedative"; break;
		//	case EItem_COMBAT_ANALYZER: result = "Combat Analyzer"; break;
		//	case EItem_MAIDENS_KISS: result = "Maiden's Kiss"; break;
		//	case EItem_ANTIDOTE: result = "Antidote"; break;
		//	case EItem_ELIXIR: result = "Elixir"; break;
		//	case EItem_WATCH_SECURITY_KEY: result = "Watch Security Key"; break;
		//	case EItem_SHINRA_ID_CARD: result = "Shinra ID Card"; break;
		//	case EItem_ORB_OF_GRAVITY: result = "Orb of Gravity"; break;
		//	case EItem_HAZARDOUS_MATERIAL: result = "Hazardous Material"; break;
		//	case EItem_REMEDY: result = "Remedy"; break;
		//	case EItem_GRAPPLING_GUN: result = "Grappling Gun"; break;
		//	case EItem_ECHO_MIST: result = "Echo Mist"; break;
		//	case EItem_SECTOR_5_REACTOR_KEY_CARD: result = "Sector 5 Reactor Key Card"; break;
		//	case EItem_BIG_BOMBER: result = "Big Bomber"; break;
		//	case EItem_MEGA_POTION: result = "Mega Potion"; break;
		//	case EItem_SMELLING_SALTS: result = "Smelling Salts"; break;
		//	case EItem_CELERIS: result = "Celeris"; break;
		//	case EItem_HANDMADE_NECKLACE: result = "Handmade Necklace"; break;
		//	case EItem_MOOGLE_MEMBERSHIP_CARD: result = "Moogle Membership Card"; break;
		//	case EItem_GRAVEYARD_KEY: result = "Graveyard Key"; break;
		//	case EItem_GUARDIAN_ANGELS_CALLING_CARDS: result = "Guardian Angel's Calling Cards"; break;
		//	case EItem_SAMS_COIN: result = "Sam's Coin"; break;
		//	case EItem_TOURNAMENT_ENTRY_FORM: result = "Tournament Entry Form"; break;
		//	case EItem_FUZZY_WUZZY: result = "Fuzzy Wuzzy"; break;
		//	case EItem_MR_CUDDLESWORTH: result = "Mr. Cuddlesworth"; break;
		//	case EItem_SAMS_REQUESTS: result = "Sam's Requests"; break;
		default: result = "unknown"; break;
		}

		return result;
	}

	std::string AItem::GetName(int index)
	{
		std::string result;

		switch (index)
		{
			case 1: result = "Potion"; break;
			case 2: result = "Ether"; break;
			case 6: result = "Grenade"; break;
			case 7: result = "Moogle Medal"; break;
			case 8: result = "Phoenix Down"; break;
			case 9: result = "Hi-Potion"; break;
			case 10: result = "Yellow Flower"; break;
			case 12: result = "Adrenaline"; break;
			case 13: result = "Sedative"; break;
			case 15: result = "Combat Analyzer"; break; // Key Item
			case 16: result = "Maidens Kiss"; break;
			case 18: result = "Antidote"; break;
			case 19: result = "Elixir"; break;
			case 20: result = "Watch Security Key"; break;	//	Key Item
			case 23: result = "Shinra ID Card"; break;	//	Key Item
			case 25: result = "Orb of Gravity"; break;	
			case 27: result = "Hazardous Material"; break;	
			case 28: result = "Remdedy"; break;	
			case 37: result = "Grappling Gun"; break; // key item
			case 38: result = "Echo Mist"; break;
			case 40: result = "Sector 5 Reactor Keycard"; break; // key item
			case 41: result = "Big Bomber"; break;
			case 43: result = "Mega-Potion"; break;
			case 46: result = "Smelling Salts"; break;
			case 50: result = "Celeris"; break;
			case 51: result = "Handmade Necklace"; break;  // key item
			case 52: result = "Moogle Membership Card"; break;  // key item
			case 54: result = "Graveyard Key"; break;  // key item
			case 58: result = "Guardian Angel's Calling Cards Key"; break;  // key item
			case 59: result = "Sam's Coin"; break;  // key item
			case 60: result = "Tournament Entry Form"; break;  // key item
			case 62: result = "Fuzzy Wuzzy"; break;  
			case 63: result = "Mr. Cuddlesworth"; break;  
			case 64: result = "Sam's Requests"; break;  // key item


			//	case : result = "Gil"; break;
			//	case : result = "Grenade"; break;
			//	case : result = "Moogle Medal"; break;
			//	case : result = "Phoenix Down"; break;
			//	case : result = "Hi-Potion"; break;
			//	case : result = "Yellow Flower"; break;
			//	case : result = "Adrenaline"; break;
			//	case : result = "Sedative"; break;
			//	case : result = "Combat Analyzer"; break;
			//	case : result = "Maiden's Kiss"; break;
			//	case : result = "Antidote"; break;
			//	case : result = "Elixir"; break;
			//	case : result = "Watch Security Key"; break;
			//	case : result = "Shinra ID Card"; break;
			//	case : result = "Orb of Gravity"; break;
			//	case : result = "Hazardous Material"; break;
			//	case : result = "Remedy"; break;
			//	case : result = "Grappling Gun"; break;
			//	case : result = "Echo Mist"; break;
			//	case : result = "Sector 5 Reactor Key Card"; break;
			//	case : result = "Big Bomber"; break;
			//	case : result = "Mega Potion"; break;
			//	case : result = "Smelling Salts"; break;
			//	case : result = "Celeris"; break;
			//	case : result = "Handmade Necklace"; break;
			//	case : result = "Moogle Membership Card"; break;
			//	case : result = "Graveyard Key"; break;
			//	case : result = "Guardian Angel's Calling Cards"; break;
			//	case : result = "Sam's Coin"; break;
			//	case : result = "Tournament Entry Form"; break;
			//	case : result = "Fuzzy Wuzzy"; break;
			//	case : result = "Mr. Cuddlesworth"; break;
			//	case : result = "Sam's Requests"; break;
		default: result = "unknown"; break;
		}
		return result;
	}

#pragma endregion

	//----------------------------------------------------------------------------------------------------
	//										AMATERIA
	//-----------------------------------------------------------------------------------
#pragma region	//	AMATERIA

	__int32 AMateria::GetID() { return this->MateriaID; }

	__int32 AMateria::GetNameID() { return this->NameID; }

	std::string AMateria::GetName()
	{
		std::string result;

		switch (NameID)
		{
		case EMateria_Healing: result = "Healing"; break;
		case EMateria_Cleansing: result = "Cleansing"; break;
		case EMateria_Revival: result = "Revival"; break;
		case EMateria_Fire: result = "Fire"; break;
		case EMateria_Ice: result = "Ice"; break;
		case EMateria_Lightning: result = "Lightning"; break;
		case EMateria_Barrier: result = "Barrier"; break;
		case EMateria_Elemental: result = "Elemental"; break;
		case EMateria_Assess: result = "Assess"; break;
		case EMateria_Chakra: result = "Chakra"; break;
		case EMateria_Prayer: result = "Prayer"; break;
		case EMateria_DeadlyDodge: result = "Deadly Dodge"; break;
		case EMateria_AutoCure: result = "Auto Cure"; break;
		default: result = "unknown"; break;
		}

		return result;
	}

#pragma endregion

	//----------------------------------------------------------------------------------------------------
	//										APLAYERSTATE
	//-----------------------------------------------------------------------------------
#pragma region	//	APLAYERSTATE

	void APlayerStats::RefillHP() { HP = MaxHP; }

	void APlayerStats::RefillMana() { MP = MaxMP; }

	void APlayerStats::SetMaxLimit() { LimitBreak = 1000.f; }

	void APlayerStats::SetMaxATB() { ATB = 2000.f; }

#pragma endregion

	//----------------------------------------------------------------------------------------------------
	//										ACLOUDSTATE
	//-----------------------------------------------------------------------------------
#pragma region	//	ACLOUDSTATE

	struct AGameState* ACloudState::GetGameState()
	{
		return reinterpret_cast<AGameState*>(reinterpret_cast<__int64>(pad_0000) - Offsets::oGameBase_CloudState);
	}

#pragma endregion

	//----------------------------------------------------------------------------------------------------
	//										AGAMESTATE
	//-----------------------------------------------------------------------------------
#pragma region	//	AGAMESTATE

	struct APlayerStats AGameState::GetPlayerStats(int index) { return this->PartyStats[index]; }

	void AGameState::SetPlayerStats(int index, const APlayerStats newStats) { this->PartyStats[index] = newStats; }

	struct APlayerStats AGameState::GetCloudStats() { return this->CloudState.Stats; }

	void AGameState::SetCloudStats(const APlayerStats newState) { this->CloudState.Stats = newState; }

	struct APlayerAttributes AGameState::GetPlayerAttributes(int index) { return this->PartyAttributes[index]; }

	void AGameState::SetPlayerAttributes(int index, const APlayerAttributes newAttributes) { this->PartyAttributes[index] = newAttributes; }

	struct APlayerAttributes AGameState::GetCloudAttributes() { return GetPlayerAttributes(0); }											//	return this->mPamPartyAttributes[0];

	void AGameState::SetCloudAttributes(const APlayerAttributes newAttributes) { SetPlayerAttributes(0, newAttributes); }	//	this->mPartyAttributes[0] = newAttributes; }
	
	struct AMateria* AGameState::GetMateria()
	{
		return reinterpret_cast<AMateria*>(((__int64)&this->pad_0000 + Offsets::oGameBase_MateriaList));
	}

	struct AItem* AGameState::GetItems()
	{
		return reinterpret_cast<AItem*>(((__int64)&this->pad_0000 + Offsets::oGameBase_ItemsList));
	}

#pragma endregion

	//----------------------------------------------------------------------------------------------------
	//										AGAMEBASE
	//-----------------------------------------------------------------------------------
#pragma region	//	AGAMEBASE

	bool AGameBase::Valid() { return this->MatchState0 <= 2; }

	class AGameState* AGameBase::GetGameState()
	{
		AGameState* result{ nullptr };

		if (this->Valid())
			result = this->pGameState;

		return result;
	}

#pragma endregion

	//----------------------------------------------------------------------------------------------------
	//										ASCENE
	//-----------------------------------------------------------------------------------
#pragma region	//	ASCENE

	void AScene::SetPauseState(bool newState) { this->bPause = newState; }

	bool AScene::GetPauseState() { return this->bPause; }

	void AScene::SetTimeScale(float newScalar) { this->TimeScale = newScalar; }

	float AScene::GetTimeScale() { return this->TimeScale; }

#pragma endregion

	//----------------------------------------------------------------------------------------------------
	//										ON USE ITEM
	//-----------------------------------------------------------------------------------
#pragma region	//	ON USE ITEM

	AGameState* OnUseItem::GetGameState() { return pCloudState->GetGameState(); }
	
	AInventory* OnUseItem::GetInventory() { return reinterpret_cast<AInventory*>(*ppInventory); }

	AItem* OnUseItem::GetCurrentItemSlot() { return GetItemSlot(); }

	AItem* OnUseItem::GetItemSlot(int index)
	{
		/*
			AItemSlot* result{ nullptr };
			auto p = GetInventory();
			auto i = index * sizeof(AItemSlot);
			auto z = reinterpret_cast<long long>(p) + i;
			auto inv = reinterpret_cast<AInventory*>(z);
			AItemSlot* result = &inv->Item;
		*/
		return &reinterpret_cast<AInventory*>(reinterpret_cast<__int64>(GetInventory()) + index * sizeof(AItem))->Item;
	}

	int OnUseItem::GetCurrentItemCount()
	{
		int result{ 0 };

		auto inventory = GetInventory();

		if (inventory)
			result = inventory->Item.Count;

		return result;
	}

#pragma endregion

	//----------------------------------------------------------------------------------------------------
	//										ON SET HEALTH
	//-----------------------------------------------------------------------------------
#pragma region	//	ON SET HEALTH

	OnSetHealth::OnSetHealth() {}
	
	OnSetHealth::OnSetHealth(int i, int hp)
	{
		bool isTakeDmg{ false };
		bool isHealing{ false };
		AGameBase* pGame = AGame::gGameBase;
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
		NewHP = hp;
		Diff = diff;
		bHealing = isHealing;
		bTakingDmg = isTakeDmg;
		PlayerStats = player_stats;
		pGameState = pGameS;
	}

#pragma endregion

	//----------------------------------------------------------------------------------------------------
	//										ON SET MANA
	//-----------------------------------------------------------------------------------
#pragma region	//	ON SET MANA

	OnSetMana::OnSetMana() {}

	OnSetMana::OnSetMana(int i, int mp)
	{
		bool isSubMana{ false };
		bool isHealing{ false };
		AGameBase* pGame = AGame::gGameBase;
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
		NewMP = mp;
		Diff = diff;
		bRestoring = isHealing;
		bUsing = isSubMana;
		PlayerStats = player_stats;
		pGameState = pGameS;
	}

#pragma endregion

	//----------------------------------------------------------------------------------------------------
	//										ATARGET
	//-----------------------------------------------------------------------------------
#pragma region	//	ATARGET

	bool ATarget::IsValid()
	{
		static __int64 TargetEntity_vfTable = g_Engine->g_GameBaseAddr + VtableOffsets::vfTargetEntity;
		__int64 vfTable_addr = *(__int64*)((__int64)&this->Level - 0x8);
		if (!vfTable_addr || vfTable_addr != TargetEntity_vfTable)
			return false;

		return true;
	}

#pragma endregion

	//----------------------------------------------------------------------------------------------------
	//										STARGETINFO
	//-----------------------------------------------------------------------------------
#pragma region	//	STARGETINFO

	STargetInfo::STargetInfo() {}

	STargetInfo::STargetInfo(ATarget* p)
	{
		if (!p)
			return;

		pTarget = p;
		Level = pTarget->Level;
		SpAtkTime = pTarget->SpAtkTime;
		SpAtkTimeMax = pTarget->SpAtkTimeMax;
		AttackRate = pTarget->AttackRate;
		HP = pTarget->HP;
		HPMax = pTarget->HPMax;
		Attack = pTarget->Attack;
		MagicAtk = pTarget->MagicAtk;
		Defense = pTarget->Defense;
		MagicDefense = pTarget->MagicDefense;
		
		bValid = HP > 0;
	}

	void STargetInfo::ClearTarget() { memset(this, 0, sizeof(STargetInfo)); }

	bool STargetInfo::IsCurrentTarget(class ATarget* pCmp) { return pCmp == pTarget; }

	bool STargetInfo::Update()
	{
		bool result{ false };

		if (!bValid || !pTarget)
		{
			bValid = result;
			return result;
		}

		if (pTarget->HP <= 0)
		{
			bValid = result;
			return result;
		}

		return true;
	}

	void STargetInfo::StaggerUpdate(class ATargetStagger* sInfo)
	{
		Stagger = sInfo->Stagger;
		StaggerMax = sInfo->StaggerMax;
	}


#pragma endregion

}