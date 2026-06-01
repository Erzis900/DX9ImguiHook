// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "D3D/D3DHelper.h"
#include "Console.h"
#include "Hooks/Hooks.h"

DWORD WINAPI MainThread(LPVOID parameter)
{
	spdlog::set_level(spdlog::level::debug);

	Console::Init();

	if (!D3DHelper::FetchData())
	{
		spdlog::error("D3DHelper data fetch failed");
		return -1;
	}

	Hooks::Hook();

	while (!Hooks::isUnload) {
		Sleep(50);
	}

	Hooks::Unhook();
	Console::Shutdown();

	FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(parameter), 0);

	return 0;
}

BOOL WINAPI DllMain(HMODULE dllHandle, DWORD callReason, LPVOID reserved)
{
	if (callReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(dllHandle);
		CreateThread(NULL, 0, MainThread, dllHandle, 0, NULL);
	}

	return TRUE;
}

