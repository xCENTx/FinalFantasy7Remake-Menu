#pragma once
#include "helper.h"
#include "Game.hpp"
#include "D3D11Window.hpp"
namespace FF7Remake 
{
	class Menu
	{
	public:
		void Draw();
		void MainMenu();
		void HUD();
		void Loops();

		//	constructor
		Menu()  noexcept = default;
		~Menu() noexcept = default;
	};
	inline std::unique_ptr<Menu> g_Menu;
}
