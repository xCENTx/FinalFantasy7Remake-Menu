#pragma once
#include "helper.h"

namespace FF7Remake 
{
	class Engine
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
	public:
		void								Init();

	public:
		static bool							GetKeyState(WORD v, SHORT delta);
		static bool							GamePadGetKeyState(WORD combinationButtons);

		Engine();
		~Engine();
	};
	inline std::unique_ptr<Engine> g_Engine;

	class Console
	{
	public:
		enum EColors : int
		{
			EColor_dark_blue = 1,
			EColor_dark_green,
			EColor_dark_teal,
			EColor_dark_red,
			EColor_dark_pink,
			EColor_dark_yellow,
			EColor_dark_white,
			EColor_dark_gray,
			EColor_blue,
			EColor_green,
			EColor_teal,
			EColor_red,
			EColor_pink,
			EColor_yellow,
			EColor_white,
			EColor_DEFAULT = EColor_white
		};

	public:
		static FILE*	m_pOutStream;
		static bool		m_bInit;
		static bool		m_bGUI;
		HANDLE			m_pHandle{ 0 };
		HWND			m_pHwnd{ 0 };
		bool			m_bShow{ true };
		bool			m_bVerbose{ false };

	public:
		void			InitializeConsole(const char* title, bool bGUI = true);
		void			cLog(const char* fmt, const EColors Color = EColor_DEFAULT, ...);
		void			LogError(const char* fmt, ...);
		void			DestroyConsole();

	public:
		static void		Log(const char* fmt, ...);
		static void		Clear();

		//	constructor
		explicit Console();
		~Console();
	};
	inline std::unique_ptr<Console> g_Console;

	class D3D11Window
	{
	private:
		WNDCLASSEX				WindowClass;
		HWND					WindowHwnd;
		ID3D11Device*			m_Device{};
		ID3D11DeviceContext*	m_DeviceContext{};
		ID3D11RenderTargetView* m_RenderTargetView{};
	
	private:
		static LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	public:
		bool					m_Init{};
		bool					b_ImGui_Initialized{};
		WNDPROC					m_OldWndProc{};

	public:
		bool					HijackWindow();
		bool					GetWindowContext();
		bool					InitWindow();
		bool					DeleteWindow();
		bool					InitImGui(IDXGISwapChain* swapChain);
		void					Overlay(IDXGISwapChain* pSwapChain);


		//	constructor
		explicit D3D11Window() = default;
		~D3D11Window() noexcept;
	};
	inline std::unique_ptr<D3D11Window> g_D3D11Window;

	class Hooking
	{
	public:
		void Initialize();
		void Shutdown();
		static bool CreateHook(LPVOID pTarget, LPVOID pDetour, LPVOID* pOrig);
		static void EnableHook(LPVOID pTarget);
		static void EnableAllHooks();
		static void DisableHook(LPVOID pTarget);
		static void RemoveHook(LPVOID pTarget);
		static void DisableAllHooks();
		static void RemoveAllHooks();


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


		//	constructor
		explicit Hooking();
		~Hooking() noexcept;
	};
	inline std::unique_ptr<Hooking> g_Hooking;

}