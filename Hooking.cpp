#include "Hooking.hpp"
namespace FF7Remake 
{
	Hooking::Hooking()
	{
		pXInput_State = (g_GameData->g_GameBaseAddr + Offsets::oXinputState);
		pAScene_Update = (g_GameData->g_GameBaseAddr + Offsets::oSceneUpdate);
		pAPlayerState_SubHealth = (g_GameData->g_GameBaseAddr + Offsets::oSubHealth);
		pAPlayerState_SubItem = (g_GameData->g_GameBaseAddr + Offsets::oSubItem);

		MH_Initialize();
	}

	Hooking::~Hooking()
	{
		DisableAllHooks();
		RemoveAllHooks();
		MH_Uninitialize();
	}

	void Hooking::Initialize()
	{
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

		//	Party Sub Health Handler
		if (pAPlayerState_SubHealth)
			CreateHook((LPVOID)pAPlayerState_SubHealth, &APlayerState_SubHealth_hook, (void**)&APlayerState_SubHealth_stub);

		//	Party Sub Item Handler
		if (pAPlayerState_SubItem)
			CreateHook((LPVOID)pAPlayerState_SubItem, &APlayerState_SubItem_hook, (void**)&APlayerState_SubItem_stub);

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

		if (pAPlayerState_SubHealth)
			DisableHook((LPVOID)pAPlayerState_SubHealth);

		if (pAPlayerState_SubItem)
			DisableHook((LPVOID)pAPlayerState_SubItem);

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
		if (p && pScene && g_GameData->bPauseGame && g_GameData->m_ShowMenu)
		{
			//	pScene->SetPauseState(true);
			pScene->SetTimeScale(0.00f);
		}

		if (p && pScene && g_GameData->bModTimeScale)
			pScene->SetTimeScale(g_GameData->fTimeScale);

		//	exec original fn
		g_Hooking->AScene_Update_stub(p);
	}

	__int64 Hooking::APlayerState_SubHealth_hook(unsigned __int8 a1, int a2)
	{
		///	PORT NOTES
		/*

			// AOB:	E8 ? ? ? ? 0F B6 CB E8 ? ? ? ? 8B D0
			//	STUB:	__int64 __fastcall APlayerState_SubHealth(unsigned __int8, int)
			//	INSTRUCTION:	*(_DWORD *)(((unsigned __int64)a1 << 6) + result + 0x30) = a2;
			//	ASM:	mov     [rcx+rax+30h], edi

			{

			}

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

		if (g_Console->m_bVerbose)
			Console::Log("[+] [Hooking::APlayerState_SubHealth_hook(%d, %d)]\n", a1, a2);

		if (g_GameData->bNullDmg)
			return 0;

		//	exec original fn
		return g_Hooking->APlayerState_SubHealth_stub(a1, a2);
	}

	struct AComponents
	{
		struct AInventory*		pItems;				//0x0000
		char					pad_0008[120];		//0x0008
	};	//Size: 0x0080

	struct OnUseItem
	{
		char					pad_0000[24];		//0x0000
		struct APlayerStats*	pStats;				//0x0018
		char					pad_0020[40];		//0x0020
		struct AComponents*		pComponents;		//0x0048
		char					pad_0050[48];		//0x0050
	};	//Size: 0x0080

	__int64 Hooking::APlayerState_SubItem_hook(__int64 p, int id)
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

			{
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
			}
		*/

		///	Get Item Count
		//	DWORD count{ 0 };
		//	auto pUse = reinterpret_cast<OnUseItem*>(p);
		//	if (pUse && pUse->pComponents)
		//	{
		//		AInventory* pInventory = pUse->pComponents->pItems;
		//		if (pInventory)
		//			count = pInventory->Item.Count;
		//	}

		if (g_Console->m_bVerbose)
			Console::Log("[+] [Hooking::APlayerState_SubItem(0x%llX, %d)]\n", p, id);

		if (g_GameData->bNullItem)
			return 0;

		//	exec original fn
		return g_Hooking->APlayerState_SubItem_stub(p, id);
	}
}
