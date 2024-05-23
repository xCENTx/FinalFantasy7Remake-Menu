#pragma once
#include "helper.h"
#include "Console.hpp"
#include "Game.hpp"
#include "Hooking.hpp"
#include "Menu.hpp"

namespace FF7Remake 
{
	class D3D11Window
	{
	private:
		WNDCLASSEX WindowClass;
		HWND WindowHwnd;
		ID3D11Device* m_Device{};
		ID3D11DeviceContext* m_DeviceContext{};
		ID3D11RenderTargetView* m_RenderTargetView{};

		static LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	public:
		bool m_Init{};
		bool b_ImGui_Initialized{};
		WNDPROC m_OldWndProc{};

		explicit D3D11Window() = default;
		~D3D11Window() noexcept;

		bool HijackWindow();
		bool GetWindowContext();
		bool InitWindow();
		bool DeleteWindow();
		bool InitImGui(IDXGISwapChain* swapChain);
		void Overlay(IDXGISwapChain* pSwapChain);
	};
	inline std::unique_ptr<D3D11Window> g_D3D11Window;
}
