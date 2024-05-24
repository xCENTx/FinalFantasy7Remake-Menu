#pragma once
#include "helper.h"
#include "Console.hpp"
#include "Game.hpp"
#include "D3D11Window.hpp"

namespace FF7Remake {
	class Hooking
	{
	public:
		void Initialize();
		void Shutdown();
		bool CreateHook(LPVOID pTarget, LPVOID pDetour, LPVOID* pOrig);
		void EnableHook(LPVOID pTarget);
		void EnableAllHooks();
		void DisableHook(LPVOID pTarget);
		void RemoveHook(LPVOID pTarget);
		void DisableAllHooks();
		void RemoveAllHooks();


		//	Hook is applied in D3D11Window
		typedef HRESULT(APIENTRY* IDXGISwapChainPresent)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
		static HRESULT APIENTRY Swapchain_present_hook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
		IDXGISwapChainPresent Swapchain_present_stub = 0;
		__int64 pSwapchain_Present = 0;

		//	Hook is applied in D3D11Window
		typedef void(APIENTRY* ID3D11DrawIndexed)(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
		static void APIENTRY Swapchain_DrawIndexed_hook(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
		ID3D11DrawIndexed Swapchain_DrawIndexed_stub = 0;
		__int64 pSwapchain_DrawIndexed = 0;


		typedef __int64(__fastcall* XInput_State)(__int64);
		static __int64 __fastcall XInput_State_hook(__int64 a1);
		XInput_State XInput_State_stub = 0;
		__int64 pXInput_State = 0;


		typedef void(__fastcall*AScene_Update)(__int64);
		static void __fastcall AScene_Update_hook(__int64 p);
		AScene_Update AScene_Update_stub = 0;
		__int64 pAScene_Update = 0;


		typedef __int64(__fastcall*APlayerState_SubHealth)(unsigned __int8, int);
		static __int64 __fastcall APlayerState_SubHealth_hook(unsigned __int8 a1, int a2);
		APlayerState_SubHealth APlayerState_SubHealth_stub = 0;
		__int64 pAPlayerState_SubHealth = 0;

		//	constructor
		explicit Hooking();
		~Hooking() noexcept;
	};
	inline std::unique_ptr<Hooking> g_Hooking;
}