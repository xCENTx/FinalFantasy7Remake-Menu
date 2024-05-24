#pragma once
#include "helper.h"

namespace FF7Remake {

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
		HANDLE			m_pHandle{ 0 };
		HWND			m_pHwnd{ 0 };
		bool			m_bShow{ true };

	public:
		void			InitializeConsole(const char* title);
		void			cLog(const char* fmt, EColors Color = EColor_DEFAULT, ...);
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
}