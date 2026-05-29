// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

DWORD WINAPI MainThread(LPVOID parameter)
{
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

