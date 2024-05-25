#pragma once
#include "helper.h"
namespace FF7Remake 
{
	class Menu
	{
	public:
		static void Draw();
		static void MainMenu();
		static void HUD();
		static void Loops();

		//	constructor
		Menu()  noexcept = default;
		~Menu() noexcept = default;
	};
}
