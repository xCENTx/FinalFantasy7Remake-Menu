#include "Console.hpp"
namespace FF7Remake 
{
	FILE*				Console::m_pOutStream;
	bool				Console::m_bInit;

	Console::Console() { }

	Console::~Console() { DestroyConsole(); }

	void Console::InitializeConsole(const char* title)
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
		ShowWindow(m_pHwnd, SW_SHOW);
		Console::m_bInit = true;
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
}