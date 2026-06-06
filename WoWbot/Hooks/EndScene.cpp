#include "pch.h"
#include "HookManager.h"
#include <iostream>

HRESULT HookManager::OnEndScene(IDirect3DDevice9* pDevice)
{
	if (!menu.IsInit()) {
		D3DDEVICE_CREATION_PARAMETERS params = {};
		pDevice->GetCreationParameters(&params);
		focusWindow = params.hFocusWindow;

		wndProc = (WNDPROC)SetWindowLongPtr(focusWindow, GWLP_WNDPROC, (LONG_PTR)WndProcDetour);

		menu.InitImgui(pDevice, focusWindow);
		menu.SetInit(true);
	}

	spdlog::debug("test");
	menu.Draw();

	return endScene(pDevice);
}