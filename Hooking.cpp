#include "Hooking.hpp"
namespace FF7Remake 
{
	Hooking::Hooking()
	{
		pXInput_State = (g_GameData->g_GameBaseAddr + Offsets::oXinputState);
		pAScene_Update = (g_GameData->g_GameBaseAddr + Offsets::oSceneUpdate);
		pAPlayerState_SubHealth = (g_GameData->g_GameBaseAddr + Offsets::oSubHealth);

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
		if (g_D3D11Window->GetWindowContext())
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

		//	
		if (pAScene_Update)
			CreateHook((LPVOID)pAScene_Update, &AScene_Update_hook, (void**)&AScene_Update_stub);

		//	
		if (pAPlayerState_SubHealth)
			CreateHook((LPVOID)pAPlayerState_SubHealth, &APlayerState_SubHealth_hook, (void**)&APlayerState_SubHealth_stub);

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

		if (g_GameData->bNullDmg)
			return 0;

		//	exec original fn
		return g_Hooking->APlayerState_SubHealth_stub(a1, a2);
	}
}
