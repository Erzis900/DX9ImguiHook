#include "pch.h"
#include "HookManager.h"

static HookManager* g_hookManager = NULL;

static HRESULT __stdcall EndSceneDetour(IDirect3DDevice9* pDevice) {
	return g_hookManager->OnEndScene(pDevice);
}

LRESULT __stdcall WndProcDetour(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return g_hookManager->OnWndProc(hWnd, msg, wParam, lParam);
}

HookManager::HookManager(Menu& menu)
	:menu(menu)
{
	endScene = D3DHelper::GetEndScene();

	if (!endScene)
		return;

	g_hookManager = this;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)endScene, EndSceneDetour);
	DetourTransactionCommit();
}

HookManager::~HookManager()
{
	if (!g_hookManager) {
		return;
	}

	SetWindowLongPtr(focusWindow, GWLP_WNDPROC, (LONG_PTR)wndProc);

	g_hookManager = NULL;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)endScene, EndSceneDetour);
	DetourTransactionCommit();
}