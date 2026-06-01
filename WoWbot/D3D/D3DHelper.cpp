#include "pch.h"
#include "D3DHelper.h"

static BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	DWORD pid;
	GetWindowThreadProcessId(hWnd, &pid);

	if (pid == lParam) {
		D3DHelper::hWnd = hWnd;
		return FALSE;
	}

	return TRUE;
}

BOOL D3DHelper::FetchData()
{
	EnumWindows(EnumWindowsProc, GetCurrentProcessId());
	if (!hWnd) {
		spdlog::error("Window handle not found");
		return false;
	}

	if (!FetchEndScene()) {
		spdlog::error("EndScene fetch failed");
		return false;
	}
	
	return true;
}

BOOL D3DHelper::FetchEndScene()
{
	IDirect3D9* d3dInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3dInterface)
		return FALSE;

	D3DPRESENT_PARAMETERS d3dPp = {};
	d3dPp.Windowed = TRUE;
	d3dPp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPp.hDeviceWindow = hWnd;

	LPDIRECT3DDEVICE9 d3dDevice = NULL;

	if (FAILED(d3dInterface->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dPp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPp, &d3dDevice)))
	{
		d3dInterface->Release();
		return FALSE;
	}

	uintptr_t* vTable = *reinterpret_cast<uintptr_t**>(d3dDevice);
	D3DHelper::endScene = reinterpret_cast<EndSceneT>(vTable[END_SCENE_INDEX]);

	d3dDevice->Release();
	d3dInterface->Release();

	return TRUE;
}