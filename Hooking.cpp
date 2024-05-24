#include "Hooking.hpp"
namespace FF7Remake 
{
	Hooking::Hooking() { MH_Initialize(); }

	Hooking::~Hooking()
	{
		DisableAllHooks();
		RemoveAllHooks();
		MH_Uninitialize();
	}

	void Hooking::Initialize()
	{
		//	Resolve Function Pointers
		pXInput_State				= (g_GameData->g_GameBaseAddr + Offsets::oXinputState);
		pAScene_Update				= (g_GameData->g_GameBaseAddr + Offsets::oSceneUpdate);
		pAPlayerState_SetHealth		= (g_GameData->g_GameBaseAddr + Offsets::oSetHealth);
		pAPlayerState_SetMana		= (g_GameData->g_GameBaseAddr + Offsets::oSetMana);
		pAPlayerState_SubItem		= (g_GameData->g_GameBaseAddr + Offsets::oSubItem);
		pATargetEntity_GetHP		= (g_GameData->g_GameBaseAddr + Offsets::oTargetGetHP);
		pATargetEntity_GetStaggerAmount = (g_GameData->g_GameBaseAddr + Offsets::oTargetGetStaggerAmount);

		if (Console::m_bGUI && g_D3D11Window->GetWindowContext())
		{
			if (pSwapchain_Present)
				CreateHook((LPVOID)pSwapchain_Present, &Swapchain_present_hook, (void**)&Swapchain_present_stub);

			if (pSwapchain_DrawIndexed)
				CreateHook((LPVOID)pSwapchain_DrawIndexed, &Swapchain_DrawIndexed_hook, (void**)&Swapchain_DrawIndexed_stub);

			g_GameData->m_ShowHud = true;
		}

		//	Controller Input Handler
		if (pXInput_State)
			CreateHook((LPVOID)pXInput_State, &XInput_State_hook, (void**)&XInput_State_stub);

		//	Render Scene Update 
		if (pAScene_Update)
			CreateHook((LPVOID)pAScene_Update, &AScene_Update_hook, (void**)&AScene_Update_stub);

		//	Party Set Health Handler
		if (pAPlayerState_SetHealth)
			CreateHook((LPVOID)pAPlayerState_SetHealth, &APlayerState_SetHealth_hook, (void**)&APlayerState_SetHealth_stub);
		
		//	Party Set Mana Handler
		if (pAPlayerState_SetMana)
			CreateHook((LPVOID)pAPlayerState_SetMana, &APlayerState_SetMana_hook, (void**)&APlayerState_SetMana_stub);

		//	Party Sub Item Handler
		if (pAPlayerState_SubItem)
			CreateHook((LPVOID)pAPlayerState_SubItem, &APlayerState_SubItem_hook, (void**)&APlayerState_SubItem_stub);

		//	Target Entity Handler
		if (pATargetEntity_GetHP)
			CreateHook((LPVOID)pATargetEntity_GetHP, &ATargetEntity_GetHP_hook, (void**)&ATargetEntity_GetHP_stub);

		//	Target Entity Stagger Handler
		if (pATargetEntity_GetStaggerAmount)
			CreateHook((LPVOID)pATargetEntity_GetStaggerAmount, &ATargetEntity_GetStaggerAmount_hook, (void**)&ATargetEntity_GetStaggerAmount_stub);

		EnableAllHooks();
	}

	void Hooking::Shutdown()
	{
		if (pSwapchain_Present)
			DisableHook((LPVOID)pSwapchain_Present);

		if (pSwapchain_DrawIndexed)
			DisableHook((LPVOID)pSwapchain_DrawIndexed);

		if (pXInput_State)
			DisableHook((LPVOID)pXInput_State);
		
		if (pAScene_Update)
			DisableHook((LPVOID)pAScene_Update);

		if (pAPlayerState_SetHealth)
			DisableHook((LPVOID)pAPlayerState_SetHealth);

		if (pAPlayerState_SetMana)
			DisableHook((LPVOID)pAPlayerState_SetMana);

		if (pAPlayerState_SubItem)
			DisableHook((LPVOID)pAPlayerState_SubItem);

		if (pATargetEntity_GetHP)
			DisableHook((LPVOID)pATargetEntity_GetHP);

		if (pATargetEntity_GetStaggerAmount)
			DisableHook((LPVOID)pATargetEntity_GetStaggerAmount);

		RemoveAllHooks();
	}

	bool Hooking::CreateHook(LPVOID lpTarget, LPVOID pDetour, LPVOID* pOrig)
	{
		if (MH_CreateHook(lpTarget, pDetour, pOrig) != MH_OK || MH_EnableHook(lpTarget) != MH_OK)
			return false;
		return true;
	}

	void Hooking::EnableHook(LPVOID lpTarget) { MH_EnableHook(lpTarget); }

	void Hooking::DisableHook(LPVOID lpTarget) { MH_DisableHook(lpTarget); }

	void Hooking::RemoveHook(LPVOID lpTarget) { MH_RemoveHook(lpTarget); }

	void Hooking::EnableAllHooks() { MH_EnableHook(MH_ALL_HOOKS); }

	void Hooking::DisableAllHooks() { MH_DisableHook(MH_ALL_HOOKS); }

	void Hooking::RemoveAllHooks() { MH_RemoveHook(MH_ALL_HOOKS); }

	HRESULT APIENTRY Hooking::Swapchain_present_hook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
	{	
		//	Render Scene
		g_D3D11Window->Overlay(pSwapChain);
		
		return g_Hooking->Swapchain_present_stub(pSwapChain, SyncInterval, Flags);
	}

	void APIENTRY Hooking::Swapchain_DrawIndexed_hook(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
	{
		g_Hooking->Swapchain_DrawIndexed_stub(pContext, IndexCount, StartIndexLocation, BaseVertexLocation);
	}

	__int64 Hooking::XInput_State_hook(__int64 a1)
	{
		///	PORT NOTES
		/*
			//	AOB: 48 8B C4 48 89 58 ? 48 89 70 ? 48 89 78 ? 55 41 54 41 55 41 56 41 57 48 8D 68 ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 44 0F 29 48 ? 44 0F 29 50 ? 44 0F 29 98 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B D9
		*/

		//	Whenever the menu is shown , we wont pass controller inputs to the game
		if (g_GameData->m_ShowMenu)
			return 0;

		g_Hooking->XInput_State_stub(a1);
	}

	void Hooking::AScene_Update_hook(__int64 p)
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
		if (pScene && g_GameData->m_ShowMenu)
		{
			//	pScene->SetPauseState(true);
			pScene->SetTimeScale(0.00f);
		}

		if (pScene && g_GameData->bPauseGame)
			pScene->SetTimeScale(pScene->GetTimeScale() * 0.0f);

		if (pScene && g_GameData->bModTimeScale)
			pScene->SetTimeScale(g_GameData->fTimeScale);

		//	exec original fn
		g_Hooking->AScene_Update_stub(p);
	}

	//	sets hp to party members by traditional game mechanics
	__int64 Hooking::APlayerState_SetHealth_hook(unsigned __int8 index, int health)
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
			.text:0000000140AFB6F3 loc_140AFB6F3:                          ; CODE XREF: APlayerState_SubHealth+25↑j						//
			.text:0000000140AFB6F3                 mov     rax, [rcx]																	//
			.text:0000000140AFB6F6                 xor     r8d, r8d																		//
			.text:0000000140AFB6F9                 mov     edx, 0B6DF0h																	//
			.text:0000000140AFB6FE                 call    qword ptr [rax+10h]															//
			.text:0000000140AFB701                 test    rax, rax																		//
			.text:0000000140AFB704                 jz      short loc_140AFB70E															//
			.text:0000000140AFB706                 mov     rcx, rax																		//
			.text:0000000140AFB709                 call    sub_140B26300																//
			.text:0000000140AFB70E																										//
			.text:0000000140AFB70E loc_140AFB70E:                          ; CODE XREF: APlayerState_SubHealth+44↑j						//
			.text:0000000140AFB70E                 mov     cs:qword_1457B9268, rax														//
			.text:0000000140AFB715																										//
			.text:0000000140AFB715 loc_140AFB715:                          ; CODE XREF: APlayerState_SubHealth+19↑j						//
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
			.text:0000000140AFB73C loc_140AFB73C:                          ; CODE XREF: APlayerState_SubHealth+5F↑j						//
			.text:0000000140AFB73C                                         ; APlayerState_SubHealth+68↑j								//
			.text:0000000140AFB73C                 mov     rbx, [rsp+28h+arg_0]															//
			.text:0000000140AFB741                 add     rsp, 20h																		//
			.text:0000000140AFB745                 pop     rdi																			//
			.text:0000000140AFB746                 retn
		*/

		//	Generate a structure based on the input params
		//	- Party Member Index & Stats
		auto pSetHealth = OnSetHealth(index, health);

		if (g_Console->m_bVerbose && pSetHealth.mDiff > 0)
			Console::Log("[+] [Hooking::APlayerState_SetHealth_hook(%d, %d)]\n- diff: %d\n- isTakeDmg: %d\n- isHealing: %d\n- origHealth: %d / %d\n- newHealth: %d / %d\n- bNullDmg: %d\n\n", 
				index, health, pSetHealth.mDiff, pSetHealth.bTakingDmg, pSetHealth.bHealing, health + pSetHealth.mDiff, pSetHealth.mPlayerStats.MaxHP, health, pSetHealth.mPlayerStats.MaxHP, g_GameData->bNullDmg);
		
		//	prevent damage to party member
		if (g_GameData->bNullDmg && pSetHealth.bTakingDmg)
			return 0;

		//	exec original fn
		return g_Hooking->APlayerState_SetHealth_stub(index, health);
	}

	//	sets mp to party members by traditional game mechanics
	__int64 Hooking::APlayerState_SetMana_hook(unsigned __int8 index, int mana)
	{
		///	PORT NOTES
		/*
			// AOB:	E8 ? ? ? ? 48 83 C6 ? 48 3B F5 0F 85 ? ? ? ? 4C 8B 74 24 ? 48 8B 7C 24 ? 48 8B 5C 24 ? 48 83 C4
			//	STUB:	__int64 __fastcall APlayerState_SetMp(unsigned __int8 a1, int a2)
			//	INSTRUCTION:	*(_DWORD *)(result + ((unsigned __int64)a1 << 6) + 56) = a2;
			//	ASM:	mov [rax+rcx+38],edi


			.text:0000000140AFB8D0 ; __int64 __fastcall APlayerState_SetMp(unsigned __int8, int)
			.text:0000000140AFB8D0 APlayerState_SetMp proc near            ; CODE XREF: sub_1409498C0+4↑j
			.text:0000000140AFB8D0                                         ; sub_1409A1BA0+ED↑p ...
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
			.text:0000000140AFB903 loc_140AFB903:                          ; CODE XREF: APlayerState_SetMp+25↑j
			.text:0000000140AFB903                 mov     rax, [rcx]
			.text:0000000140AFB906                 xor     r8d, r8d
			.text:0000000140AFB909                 mov     edx, 0B6DF0h
			.text:0000000140AFB90E                 call    qword ptr [rax+10h]
			.text:0000000140AFB911                 test    rax, rax
			.text:0000000140AFB914                 jz      short loc_140AFB91E
			.text:0000000140AFB916                 mov     rcx, rax
			.text:0000000140AFB919                 call    sub_140B26300
			.text:0000000140AFB91E
			.text:0000000140AFB91E loc_140AFB91E:                          ; CODE XREF: APlayerState_SetMp+44↑j
			.text:0000000140AFB91E                 mov     cs:qword_1457B9268, rax
			.text:0000000140AFB925
			.text:0000000140AFB925 loc_140AFB925:                          ; CODE XREF: APlayerState_SetMp+19↑j
			.text:0000000140AFB925                 cmp     bl, 8
			.text:0000000140AFB928                 jnb     short loc_140AFB943
			.text:0000000140AFB92A                 mov     rax, [rax+0B6D80h]
			.text:0000000140AFB931                 movzx   ecx, bl
			.text:0000000140AFB934                 shl     rcx, 6
			.text:0000000140AFB938                 mov     rax, [rax+3E60h]
			.text:0000000140AFB93F                 mov     [rax+rcx+38h], edi
			.text:0000000140AFB943
			.text:0000000140AFB943 loc_140AFB943:                          ; CODE XREF: APlayerState_SetMp+58↑j
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

		if (g_Console->m_bVerbose && pSetMana.mDiff > 0)
			Console::Log("[+] [Hooking::APlayerState_SetMana_hook(%d, %d)]\n- diff: %d\n- isUsingMana: %d\n- isHealingMana: %d\n- origMana: %d / %d\n- newMana: %d / %d\n- bNullMgk: %d\n\n", 
				index, mana, pSetMana.mDiff, pSetMana.bUsingMana, pSetMana.bHealing, mana + pSetMana.mDiff, pSetMana.mPlayerStats.MaxMP, mana, pSetMana.mPlayerStats.MaxMP, g_GameData->bNullMgk);

		//	prevent damage to party member
		if (g_GameData->bNullMgk && pSetMana.bUsingMana)
			return 0;

		//	exec original fn
		return g_Hooking->APlayerState_SetMana_stub(index, mana);
	}

	__int64 Hooking::APlayerState_SubItem_hook(__int64 p, int index)
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
			.text:0000000140B1CAF0 APlayerState_SubItem proc near          ; CODE XREF: sub_140B020A0+F0↑p
			.text:0000000140B1CAF0                                         ; DATA XREF: .rdata:0000000144FCFB14↓o ...
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
			.text:0000000140B1CB1D loc_140B1CB1D:                          ; DATA XREF: .rdata:0000000144FCFB14↓o
			.text:0000000140B1CB1D                                         ; .rdata:0000000144FCFB24↓o ...
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
			.text:0000000140B1CB50 loc_140B1CB50:                          ; CODE XREF: APlayerState_SubItem+72↓j
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
			.text:0000000140B1CB66 loc_140B1CB66:                          ; CODE XREF: APlayerState_SubItem+63↑j
			.text:0000000140B1CB66                 mov     rcx, cs:qword_1457F5148
			.text:0000000140B1CB6D                 test    rcx, rcx
			.text:0000000140B1CB70                 jnz     short loc_140B1CB7E
			.text:0000000140B1CB72                 call    sub_141C22CC0
			.text:0000000140B1CB77                 mov     rcx, cs:qword_1457F5148
			.text:0000000140B1CB7E
			.text:0000000140B1CB7E loc_140B1CB7E:                          ; CODE XREF: APlayerState_SubItem+80↑j
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
			.text:0000000140B1CBA7 loc_140B1CBA7:                          ; CODE XREF: APlayerState_SubItem+A1↑j
			.text:0000000140B1CBA7                 mov     rcx, r14
			.text:0000000140B1CBAA
			.text:0000000140B1CBAA loc_140B1CBAA:                          ; CODE XREF: APlayerState_SubItem+B5↑j
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
			.text:0000000140B1CBCC loc_140B1CBCC:                          ; CODE XREF: APlayerState_SubItem+41↑j
			.text:0000000140B1CBCC                                         ; APlayerState_SubItem+4A↑j ...
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
			.text:0000000140B1CBF6 loc_140B1CBF6:                          ; CODE XREF: APlayerState_SubItem+E6↑j
			.text:0000000140B1CBF6                 test    rbx, rbx
			.text:0000000140B1CBF9                 jz      short loc_140B1CC20
			.text:0000000140B1CBFB                 mov     rcx, cs:qword_1457F5148
			.text:0000000140B1CC02                 test    rcx, rcx
			.text:0000000140B1CC05                 jnz     short loc_140B1CC13
			.text:0000000140B1CC07                 call    sub_141C22CC0
			.text:0000000140B1CC0C                 mov     rcx, cs:qword_1457F5148
			.text:0000000140B1CC13
			.text:0000000140B1CC13 loc_140B1CC13:                          ; CODE XREF: APlayerState_SubItem+115↑j
			.text:0000000140B1CC13                 mov     rax, [rcx]
			.text:0000000140B1CC16                 mov     rdx, rbx
			.text:0000000140B1CC19                 call    qword ptr [rax+20h]
			.text:0000000140B1CC1C                 mov     [rsi+48h], r14
			.text:0000000140B1CC20
			.text:0000000140B1CC20 loc_140B1CC20:                          ; CODE XREF: APlayerState_SubItem+109↑j
			.text:0000000140B1CC20                 mov     rbx, [rsp+28h+arg_0]
			.text:0000000140B1CC25                 mov     r14, [rsp+28h+arg_8]
			.text:0000000140B1CC2A
			.text:0000000140B1CC2A loc_140B1CC2A:                          ; CODE XREF: APlayerState_SubItem+27↑j
			.text:0000000140B1CC2A                                         ; DATA XREF: .pdata:0000000145A771BC↓o ...
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
		AItemSlot* v12 = reinterpret_cast<AItemSlot*>(*v11);		// ItemSlot
		int sub_amount = *((__int32*)v11 + 3);						// sub amount
		int v13 = v12->count - sub_amount;							// sub item new amount

		if (g_Console->m_bVerbose)
			Console::Log("[+] [Hooking::APlayerState_SubItem(0x%llX, %d)]\n- subAmount: %d\n- origCount: %d\n- newCount: %d\n- bNullItem: %d\n\n", 
				p, index, sub_amount, v12->count, v13, g_GameData->bNullItem);

		if (g_GameData->bNullItem)
		{
			auto result = g_Hooking->APlayerState_SubItem_stub(p, index);

			//	Set new amount ( revert change )
			v12->count = (v13 + sub_amount);

			return result;
		}

		//	exec original fn
		return g_Hooking->APlayerState_SubItem_stub(p, index);
	}

	struct ATarget
	{
		int		Level;			//0x0008
		float	SpAtkTime;		//0x000C
		float	SpAtkTimeMax;	//0x0010
		float	AttackRate;		//0x0014
		int		HP;				//0x0018
		int		HPMax;			//0x001C
		char	pad_0020[8];	//0x0020
		int		Attack;			//0x0028
		int		MagicAtk;		//0x002C
		int		Defense;		//0x0030
		int		MagicDefense;	//0x0034
		char	pad_0038[8];	//0x0038

		//	
		virtual void Function0();
		virtual int GetLevel() = 0;
		virtual void SetLevel(int lvl);
		virtual float GetSpAtkTime() = 0;
		virtual void SetSpAtkTime(float time);
		virtual float GetSpAtkTimeMax() = 0;
		virtual void SetSpAtkTimeMax(float maxTime);
		virtual float GetAttackRate() = 0;
		virtual void SetAttackRate(float rate);
		virtual int GetHP() = 0;
		virtual void SetHP(int hp);
		virtual int GetHPMax() = 0;
		virtual void SetHPMax(int mp);
		virtual void Function13();
		virtual void Function14();
		virtual void Function15();
		virtual void Function16();
		virtual void Function17();
		virtual void Function18();
		virtual int GetAttack() = 0;
		virtual void SetAttack(int atk);
		virtual int GetMagicAtk() = 0;
		virtual void SetMagicAtk(int atk);
		virtual int GetDefense() = 0;
		virtual void SetDefense(int def);
		virtual int GetMagicDef() = 0;
		virtual void SetMagicDef(int def);
		virtual void Function27();
		virtual void Function28();
		virtual void Function29();
		virtual void Function30();
		virtual void Function31();
		virtual void Function32();
		virtual void Function33();
		virtual void Function34();
		virtual void Function35();
		virtual void Function36();

		bool IsValid();
	};	//Size: 0x0040
	
	bool ATarget::IsValid()
	{
		static __int64 TargetEntity_vfTable = g_GameData->g_GameBaseAddr + 0x4B3E5E8;
		__int64 vfTable_addr = *(__int64*)((__int64)&this->Level - 0x8);
		if (!vfTable_addr || vfTable_addr != TargetEntity_vfTable)
			return false;

		return true;
	}

	__int64 Hooking::ATargetEntity_GetHP_hook(__int64 p)
	{
		static bool bEditing{ false };	//	used so can call this function without stack overflow
		auto pTarget = reinterpret_cast<ATarget*>(p);
		if (!bEditing && pTarget && pTarget->IsValid())
		{
			bEditing = true;

			//	target health is restored ( note: target can still die if damage taken is > maxhp )
			if (g_GameData->bNullTargetDmg)
			{
				auto hp_max = pTarget->GetHPMax();
				auto hp = pTarget->GetHP();	//	recursion
				if (hp < hp_max)
					pTarget->SetHP(hp_max);
			}

			//	target is killed
			if (g_GameData->bKillTarget)
			{
				//	if (g_GameData->bMaxTargetLevel)
				//	{
				if (pTarget->GetLevel() != 9999)
					pTarget->SetLevel(9999);
					//	g_GameData->bMaxTargetLevel = false;
				//	}

				if (pTarget->GetHP() > 0)
					pTarget->SetHP(0);

				g_GameData->bKillTarget = false;
			}

			//	target wont attack player
			if (g_GameData->bNoTargetAttack)
			{
				if (pTarget->GetAttackRate() > 0.0f)
					pTarget->SetAttackRate(0.0f);
				if (pTarget->GetSpAtkTimeMax() > 0.0f)
					pTarget->SetSpAtkTimeMax(0.0f);
				
				//	g_GameData->bNoTargetAttack = false;
			}

			//	prevents targets from attacking , sets max level and sets health to 0
			if (g_GameData->bXpFarn)
			{
				if (pTarget->GetLevel() != 9999)
					pTarget->SetLevel(9999);

				if (pTarget->GetAttackRate() > 0.0f)
					pTarget->SetAttackRate(0.0f);

				if (pTarget->GetSpAtkTimeMax() > 0.0f)
					pTarget->SetSpAtkTimeMax(0.0f);

				if (pTarget->GetDefense() > 0)
					pTarget->SetDefense(0);
				
				if (pTarget->GetMagicDef() > 0)
					pTarget->SetMagicDef(0);

				if (pTarget->GetHP() > 0)//	recursion
					pTarget->SetHP(0);
			}

			bEditing = false;
		}
		return g_Hooking->ATargetEntity_GetHP_stub(p);
	}

	struct ATargetStagger
	{
		unsigned char pad_0000[0xCF8];	//	0x0000
		float Stagger;					//	0x0CF8
		float StaggerMax;				//	0x0CFC
	};
	__int64 Hooking::ATargetEntity_GetStaggerAmount_hook(__int64 a1)
	{
		if (g_GameData->bXpFarn || g_GameData->bTargetAlwaysStagger)
		{
			auto pEnt = reinterpret_cast<ATargetStagger*>(a1);
			if (pEnt)
				pEnt->Stagger = pEnt->StaggerMax;
		}

		return g_Hooking->ATargetEntity_GetStaggerAmount_stub(a1);
	}
}
