#pragma once
#include <Engine.h>

namespace DX11Base
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

	class GUI
	{
	public:	//	widget
		static void TextCentered(const std::string& pText);
		static void TextCenteredf(const std::string pText, ...);
		static void Tooltip(const std::string& tip);
		static bool Toggle(const std::string& label, bool* v);

	public:	//	canvas
		static void DrawText_(const ImVec2& pos, const ImColor& color, const std::string& text, const float& szFont = 0.f);
		static void DrawBGText(const ImVec2& pos, const ImColor& color, const std::string& text, const ImColor& background, const float& szFont = 0.f);
		static void DrawBorderText(const ImVec2& pos, const ImColor& color, const std::string& text, const ImColor& border, const float& szFont = 0.f);
		static void DrawTextCentered(const ImVec2& pos, const ImColor& color, const std::string& text, const float& szFont = 0.f);
		static void DrawBGTextCentered(const ImVec2& pos, const ImColor& color, const std::string& text, const ImColor& background, const float& szFont = 0.f);
		static void DrawBorderTextCentered(const ImVec2& pos, const ImColor& color, const std::string& text, const ImColor& border, const float& szFont = 0.f);
		static void Line(const ImVec2& posA, const ImVec2& posB, const ImColor& color, const float& thickness = 1.0f);
		static void Circle(const ImVec2& pos, const ImColor& color, const float& radius, const float& thickness = 1.0f, const float& segments = 64);
		static void CleanLine(const ImVec2& posA, const ImVec2& posB, const ImColor& color, const float& thickness = 1.0f);
		static void CleanCircle(const ImVec2& pos, const ImColor& color, const float& radius, const float& thickness = 1.0f, const float& segments = 64);
	};
}