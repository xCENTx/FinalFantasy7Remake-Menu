#include "Engine.h"
#include "Menu.h"

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace FF7Remake 
{
	FILE*				Console::m_pOutStream{ nullptr };
	bool				Console::m_bInit{ false };
	bool				Console::m_bGUI{ false };
	static				uint64_t* MethodsTable{ nullptr };

	//----------------------------------------------------------------------------------------------------
	//										ENGINE
	//-----------------------------------------------------------------------------------
#pragma region //	ENGINE

	Engine::Engine()
	{
		g_Console		= std::make_unique<Console>();
		g_D3D11Window	= std::make_unique<D3D11Window>();
		g_Hooking		= std::make_unique<Hooking>();
	}

	Engine::~Engine()
	{
		g_Hooking.release();
		g_D3D11Window.release();
		g_Console.release();
	}

	void Engine::Init()
	{
		g_GamePid = GetCurrentProcessId();
		g_GameHandle = GetCurrentProcess();
		g_GameWindow = GetForegroundWindow();
		g_GameModule = GetModuleHandle(0);
		g_GameBaseAddr = reinterpret_cast<__int64>(g_GameModule);

		RECT tempRECT;
		GetWindowRect(g_GameWindow, &tempRECT);
		g_GameWidth = tempRECT.right - tempRECT.left;
		g_GameHeight = tempRECT.bottom - tempRECT.top;

		char tempTitle[MAX_PATH];
		GetWindowTextA(g_GameWindow, tempTitle, sizeof(tempTitle));
		g_GameTitle = tempTitle;

		char tempClassName[MAX_PATH];
		GetClassNameA(g_GameWindow, tempClassName, sizeof(tempClassName));
		g_ClassName = tempClassName;

		char tempPath[MAX_PATH];
		GetModuleFileNameExA(g_GameHandle, 0, tempPath, sizeof(tempPath));
		g_GamePath = tempPath;
	}

	bool Engine::GetKeyState(WORD vKey, SHORT delta)
	{
		static int lastTick = 0;

		bool result = ((GetAsyncKeyState(vKey) & 0x8000) && (GetTickCount64() - lastTick) > delta);

		if (result)
			lastTick = GetTickCount64();

		return result;
	}
	
	bool Engine::GamePadGetKeyState(WORD vButton)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		DWORD result = XInputGetState(0, &state);
		if (result == ERROR_SUCCESS)
		{
			if ((state.Gamepad.wButtons & vButton) == vButton)
				return true;
		}
		return false;
	}

#pragma endregion

	//----------------------------------------------------------------------------------------------------
	//										CONSOLE
	//-----------------------------------------------------------------------------------
#pragma region //	CONSOLE

	Console::Console() { }

	Console::~Console() { DestroyConsole(); }

	void Console::InitializeConsole(const char* title, bool GUI)
	{
		if (Console::m_bInit)
		{
			LogError("[!] [Console::InitializeConsole] failed to initialize console .\n");
			return;
		}

		AllocConsole();
		m_pHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		m_pHwnd = GetConsoleWindow();
		freopen_s(&m_pOutStream, "CONOUT$", "w", stdout);
		SetConsoleTitleA(title);
		Console::m_bInit = true;
		Console::m_bGUI = GUI;
		Console::m_bShow = !GUI;
		ShowWindow(m_pHwnd, Console::m_bShow ? SW_SHOW : SW_HIDE);
	}

	void Console::cLog(const char* fmt, EColors Color, ...)
	{
		SetConsoleTextAttribute(m_pHandle, Color);
		va_list arg;
		va_start(arg, Color);
		vfprintf(m_pOutStream, fmt, arg);
		va_end(arg);
		SetConsoleTextAttribute(m_pHandle, EColor_DEFAULT);
	}

	void Console::LogError(const char* fmt, ...)
	{
		SetConsoleTextAttribute(m_pHandle, EColor_red);
		va_list arg;
		va_start(arg, fmt);
		vfprintf(m_pOutStream, fmt, arg);
		va_end(arg);
		SetConsoleTextAttribute(m_pHandle, EColor_DEFAULT);
	}

	void Console::DestroyConsole()
	{
		fclose(m_pOutStream);
		DestroyWindow(m_pHwnd);
		FreeConsole();
		m_bInit = false;
	}

	void Console::Log(const char* fmt, ...)
	{
		if (!m_pOutStream)
			return;

		va_list arg;
		va_start(arg, fmt);
		vfprintf(m_pOutStream, fmt, arg);
		va_end(arg);
	}

	void Console::Clear() { system("cls"); }

#pragma endregion


	//----------------------------------------------------------------------------------------------------
	//										D3DWINDOW
	//-----------------------------------------------------------------------------------
#pragma region	//	D3DWINDOW

	D3D11Window::D3D11Window() {}

	D3D11Window::~D3D11Window()  { m_Init = false; }

	LRESULT D3D11Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (g_Engine->m_ShowMenu)
		{
			ImGui_ImplWin32_WndProcHandler((HWND)g_D3D11Window->m_OldWndProc, msg, wParam, lParam);
			return true;
		}
		return CallWindowProc((WNDPROC)g_D3D11Window->m_OldWndProc, hWnd, msg, wParam, lParam);
	}

	HRESULT APIENTRY D3D11Window::Swapchain_present_hook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
	{
		g_D3D11Window->Overlay(pSwapChain);

		return g_D3D11Window->Swapchain_present_stub(pSwapChain, SyncInterval, Flags);
	}

	HRESULT APIENTRY D3D11Window::Swapchain_ResizeBuffers_hook(IDXGISwapChain* p, UINT bufferCount, UINT Width, UINT Height, DXGI_FORMAT fmt, UINT scFlags)
	{
		//  Get new data & release render target
		g_D3D11Window->m_pSwapChain = p;
		g_D3D11Window->m_RenderTargetView->Release();
		g_D3D11Window->m_RenderTargetView = nullptr;

		//  get fn result
		HRESULT result = g_D3D11Window->Swapchain_ResizeBuffers_stub(p, bufferCount, Width, Height, fmt, scFlags);

		// Get new render target
		ID3D11Texture2D* backBuffer;
		p->GetBuffer(0, __uuidof(ID3D11Texture2D*), (LPVOID*)&backBuffer);
		if (backBuffer)
		{
			g_D3D11Window->m_Device->CreateRenderTargetView(backBuffer, 0, &g_D3D11Window->m_RenderTargetView);
			backBuffer->Release();
		}

		//  Reset ImGui 
		if (g_D3D11Window->b_ImGui_Initialized)
		{
			ImGuiIO& io = ImGui::GetIO();
			io.DisplaySize = ImVec2(static_cast<float>(Width), static_cast<float>(Height));
		}

		return result;
	}

	bool D3D11Window::HookD3D()
	{
		if (GetD3DContext())
		{
			Hooking::CreateHook((void*)MethodsTable[8], &Swapchain_present_hook, (void**)&Swapchain_present_stub);
			Hooking::CreateHook((void*)MethodsTable[13], &Swapchain_ResizeBuffers_hook, (void**)&Swapchain_ResizeBuffers_stub);
			m_Init = true;
			return true;
		}
		return false;
	}

	void D3D11Window::UnhookD3D()
	{
		SetWindowLongPtr(g_Engine->g_GameWindow, GWLP_WNDPROC, (LONG_PTR)m_OldWndProc);
		Hooking::DisableHook((void*)MethodsTable[8]);
		Hooking::DisableHook((void*)MethodsTable[13]);
		free(MethodsTable);
	}

	bool D3D11Window::GetD3DContext()
	{
		if (!InitWindow())
			return false;

		HMODULE D3D11Module = GetModuleHandleA("d3d11.dll");

		D3D_FEATURE_LEVEL FeatureLevel;
		const D3D_FEATURE_LEVEL FeatureLevels[] = { D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_11_0 };

		DXGI_RATIONAL RefreshRate;
		RefreshRate.Numerator = 60;
		RefreshRate.Denominator = 1;

		DXGI_MODE_DESC BufferDesc;
		BufferDesc.Width = 100;
		BufferDesc.Height = 100;
		BufferDesc.RefreshRate = RefreshRate;
		BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		DXGI_SAMPLE_DESC SampleDesc;
		SampleDesc.Count = 1;
		SampleDesc.Quality = 0;

		DXGI_SWAP_CHAIN_DESC SwapChainDesc;
		SwapChainDesc.BufferDesc = BufferDesc;
		SwapChainDesc.SampleDesc = SampleDesc;
		SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		SwapChainDesc.BufferCount = 1;
		SwapChainDesc.OutputWindow = WindowHwnd;
		SwapChainDesc.Windowed = 1;
		SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		IDXGISwapChain* SwapChain;
		ID3D11Device* Device;
		ID3D11DeviceContext* Context;
		if (D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0, 0, FeatureLevels, 1, D3D11_SDK_VERSION, &SwapChainDesc, &SwapChain, &Device, &FeatureLevel, &Context) < 0)
		{
			DeleteWindow();
			return true;
		}

		MethodsTable = (uint64_t*)::calloc(205, sizeof(uint64_t));
		memcpy(MethodsTable, *(uint64_t**)SwapChain, 18 * sizeof(uint64_t));
		memcpy(MethodsTable + 18, *(uint64_t**)Device, 43 * sizeof(uint64_t));
		memcpy(MethodsTable + 18 + 43, *(uint64_t**)Context, 144 * sizeof(uint64_t));
		Sleep(1000);

		//	INIT NOTICE
		Beep(300, 300);

		SwapChain->Release();
		SwapChain = 0;
		Device->Release();
		Device = 0;
		Context->Release();
		Context = 0;
		DeleteWindow();
		return true;
	}

	bool D3D11Window::InitWindow()
	{
		WindowClass.cbSize = sizeof(WNDCLASSEX);
		WindowClass.style = CS_HREDRAW | CS_VREDRAW;
		WindowClass.lpfnWndProc = DefWindowProc;
		WindowClass.cbClsExtra = 0;
		WindowClass.cbWndExtra = 0;
		WindowClass.hInstance = GetModuleHandle(0);
		WindowClass.hIcon = 0;
		WindowClass.hCursor = 0;
		WindowClass.hbrBackground = 0;
		WindowClass.lpszMenuName = 0;
		WindowClass.lpszClassName = L"MJ";
		WindowClass.hIconSm = 0;
		RegisterClassEx(&WindowClass);
		WindowHwnd = CreateWindow(WindowClass.lpszClassName, L"DX11 Window", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, 0, 0, WindowClass.hInstance, 0);
		if (!WindowHwnd)
			return false;
		return true;
	}

	bool D3D11Window::DeleteWindow()
	{
		DestroyWindow(WindowHwnd);
		UnregisterClass(WindowClass.lpszClassName, WindowClass.hInstance);
		if (WindowHwnd != 0)
			return false;
		return true;
	}

	bool D3D11Window::InitImGui(IDXGISwapChain* swapChain)
	{
		if (SUCCEEDED(swapChain->GetDevice(__uuidof(ID3D11Device), (void**)&m_Device))) {
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantTextInput || ImGui::GetIO().WantCaptureKeyboard;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
			io.IniFilename = 0;
			ImGui::StyleColorsDark();
			m_Device->GetImmediateContext(&m_DeviceContext);

			DXGI_SWAP_CHAIN_DESC Desc;
			swapChain->GetDesc(&Desc);
			g_Engine->g_GameWindow = Desc.OutputWindow;

			ID3D11Texture2D* BackBuffer;
			swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer);
			m_Device->CreateRenderTargetView(BackBuffer, NULL, &m_RenderTargetView);
			BackBuffer->Release();

			ImGui_ImplWin32_Init(g_Engine->g_GameWindow);
			ImGui_ImplDX11_Init(m_Device, m_DeviceContext);
			ImGui_ImplDX11_CreateDeviceObjects();
			ImGui::GetIO().ImeWindowHandle = g_Engine->g_GameWindow;
			m_OldWndProc = (WNDPROC)SetWindowLongPtr(g_Engine->g_GameWindow, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc);
			b_ImGui_Initialized = true;
			m_pSwapChain = swapChain;
			pImGui = GImGui;
			pViewport = pImGui->Viewports[0];
			return true;
		}
		b_ImGui_Initialized = false;
		return false;
	}

	void D3D11Window::Overlay(IDXGISwapChain* pSwapChain)
	{
		if (!b_ImGui_Initialized)
			InitImGui(pSwapChain);

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		ImGui::GetIO().MouseDrawCursor = g_Engine->m_ShowMenu;

		Menu::Draw();

		ImGui::EndFrame();
		ImGui::Render();
		m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, 0);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

#pragma endregion


	//----------------------------------------------------------------------------------------------------
	//										HOOKING
	//-----------------------------------------------------------------------------------
#pragma region //	HOOKING

	Hooking::Hooking() 
	{ 
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
		//	@TODO: should be included as an init method for d3dwindow class
		if (Console::m_bGUI && g_D3D11Window->HookD3D())
			g_Engine->m_ShowHud = true;

		EnableAllHooks();
	}

	void Hooking::Shutdown()
	{
		//	@TODO: should be included as a shutdown method for d3dwindow class
		if (Console::m_bGUI && g_D3D11Window->m_Init)
			g_D3D11Window->UnhookD3D();

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

#pragma endregion

}