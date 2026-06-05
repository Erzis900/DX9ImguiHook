#include "pch.h"
#include "HookManager.h"

static HookManager* g_hookManager = nullptr;

static HRESULT __stdcall EndSceneDetour(IDirect3DDevice9* pDevice) {
	return g_hookManager->OnEndScene(pDevice);
}

HookManager::HookManager(Menu& menu)
	:menu(menu)
{
	g_hookManager = this;
	endScene = D3DHelper::GetEndScene();

	if (!endScene)
		return;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)endScene, EndSceneDetour);
	DetourTransactionCommit();
}

HookManager::~HookManager()
{
	g_hookManager = nullptr;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)endScene, EndSceneDetour);
	DetourTransactionCommit();
}

HRESULT HookManager::OnEndScene(IDirect3DDevice9* pDevice)
{
	if (!menu.IsInit()) {
		menu.InitImgui(pDevice, D3DHelper::GetWindowHandle());
		menu.SetInit(true);
	}

	menu.Draw();

	return endScene(pDevice);
}