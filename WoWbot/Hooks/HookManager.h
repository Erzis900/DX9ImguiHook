#pragma once
#include "../D3D/D3DHelper.h"
#include "../Menu/Menu.h"

LRESULT __stdcall WndProcDetour(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class HookManager
{
public:
	HookManager(Menu& menu);
	~HookManager();

	HRESULT OnEndScene(IDirect3DDevice9* device);
	LRESULT OnWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	HWND focusWindow = NULL;
	EndSceneT endScene = NULL;
	WNDPROC wndProc = NULL;

	Menu& menu;
};