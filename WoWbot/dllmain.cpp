// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Application.h"
#include "spdlog/sinks/stdout_color_sinks.h"

static void RunApplication()
{
	Application app;
	app.Run();
}

DWORD WINAPI MainThread(LPVOID parameter)
{
	RunApplication();
	FreeLibraryAndExitThread((HMODULE)parameter, 0);
}

BOOL WINAPI DllMain(HMODULE dllHandle, DWORD callReason, LPVOID reserved)
{
	if (callReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(dllHandle);
		HANDLE threadHandle = CreateThread(NULL, 0, MainThread, dllHandle, 0, NULL);

		if (!threadHandle)
			return FALSE;

		CloseHandle(threadHandle);
	}

	return TRUE;
}