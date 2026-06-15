#include "pch.h"
#include "HookManager.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT HookManager::OnWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_KEYDOWN) {
		switch (wParam) {
		case VK_INSERT:
			menu.Toggle();
			break;
		case VK_END:
			unload = true;
			break;
		}
	}

	if (menu.IsOpen() && !unload) {
		ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		return true;
	}

	return CallWindowProc(wndProc, hWnd, msg, wParam, lParam);
}