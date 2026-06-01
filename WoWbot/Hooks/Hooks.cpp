#include "pch.h"
#include "Hooks.h"
#include "D3D/D3DHelper.h"

HRESULT __stdcall EndSceneDetour(IDirect3DDevice9* pDevice) {
	if (GetAsyncKeyState(VK_END))
		Hooks::isUnload = true;

	return D3DHelper::endScene(pDevice);
}

void Hooks::Hook() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)D3DHelper::endScene, EndSceneDetour);
	DetourTransactionCommit();
}

void Hooks::Unhook()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)D3DHelper::endScene, EndSceneDetour);
	DetourTransactionCommit();
}