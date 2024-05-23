#pragma once
#include "helper.h"
#include "Game.hpp"
#include "D3D11Window.hpp"
namespace FF7Remake {
	class Menu
	{
	public:
		Menu()  noexcept = default;
		~Menu() noexcept = default;

		void Draw();
		void MainMenu();
		void HUD();
		void Loops();
	};
	inline std::unique_ptr<Menu> g_Menu;
}
