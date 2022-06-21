#pragma once
#include "helper.h"
#include "Console.hpp"
#include "Game.hpp"
#include "D3D11Window.hpp"

namespace FF7Remake {
	class Hooking
	{
	public:

		explicit Hooking();
		~Hooking() noexcept;
		Hooking(Hooking const&) = delete;
		Hooking(Hooking&&) = delete;
		Hooking& operator=(Hooking const&) = delete;
		Hooking& operator=(Hooking&&) = delete;

		void Hook();
		void Unhook();

		static void __fastcall HookControllerInput(INT64 a1);
		void* m_OriginalCInputHandle{};
		uint64_t m_ControllerInputHandle{};
	};
	inline std::unique_ptr<Hooking> g_Hooking;
}