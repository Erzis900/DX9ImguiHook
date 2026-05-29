// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

BOOL WINAPI DllMain(HMODULE dllHandle, DWORD callReason, LPVOID reserved)
{
    if (callReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(dllHandle);

    }

    return TRUE;
}

