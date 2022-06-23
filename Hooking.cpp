#include "Hooking.hpp"
namespace FF7Remake {
	Hooking::Hooking()
	{
		MH_Initialize();
#if DEBUG
		g_Console->printdbg("Hooking::Initialized\n", g_Console->color.pink);
#endif
		m_ControllerInputHandle = (og_GameBase + g_GameData->offsets.aXinputState);
		return;
	}

	void Hooking::HookControllerInput(INT64 a1)
	{
		//	Whenever the menu is shown , we wont pass controller inputs to the game
		if (g_GameVariables->m_ShowMenu)
			return;

		reinterpret_cast<decltype(&HookControllerInput)>(g_Hooking->m_OriginalCInputHandle)(a1);
	}

	void Hooking::Hook()
	{
		g_GameVariables->Init();
		g_D3D11Window->Hook();

		//	Controller Input Handler
		if (m_ControllerInputHandle)
			MH_CreateHook((LPVOID)m_ControllerInputHandle, &HookControllerInput, &m_OriginalCInputHandle);

		MH_EnableHook(MH_ALL_HOOKS);

#if DEBUG
		g_Console->printdbg("Hooking::Hook Initialized\n", g_Console->color.pink);
#endif

		//	Clear Console
		//	Hide Console
		//  Show an ImGui notification bubble to the user
		system("cls");
		g_Console->ACTIVE = TRUE;
		g_Console->m_ShowConsole = FALSE;
		g_GameVariables->m_ShowHud = TRUE;
		return;
	}

	void Hooking::Unhook()
	{
		//	Begin Unhook Procedure
		g_D3D11Window->Unhook();
		MH_DisableHook((LPVOID)m_ControllerInputHandle);	//	Disable our controller hook, otherwise we will crash :D
		MH_RemoveHook(MH_ALL_HOOKS);
		g_Console->DestroyConsole();
		return;
	}

	Hooking::~Hooking()
	{
		MH_RemoveHook(MH_ALL_HOOKS);
	}
}
