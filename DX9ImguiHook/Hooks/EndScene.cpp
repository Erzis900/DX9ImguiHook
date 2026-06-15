#include "pch.h"
#include "HookManager.h"

HRESULT HookManager::OnEndScene(IDirect3DDevice9* pDevice)
{
	if (unload)
		return endScene(pDevice);

	if (!menu.IsInit()) {
		D3DDEVICE_CREATION_PARAMETERS params = {};
		pDevice->GetCreationParameters(&params);
		focusWindow = params.hFocusWindow;

		wndProc = (WNDPROC)SetWindowLongPtr(focusWindow, GWLP_WNDPROC, (LONG_PTR)WndProcDetour);

		menu.InitImgui(pDevice, focusWindow);
		menu.SetInit(true);
	}

	spdlog::debug("Hello from EndScene hook, logged by spdlog");
	menu.Draw();

	return endScene(pDevice);
}