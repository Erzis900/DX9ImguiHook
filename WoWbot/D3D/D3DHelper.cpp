#include "pch.h"
#include "D3DHelper.h"

static BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	DWORD pid = NULL;
	GetWindowThreadProcessId(hWnd, &pid);

	if (pid == GetCurrentProcessId()) {
		*(HWND*)lParam = hWnd;
		return FALSE;
	}

	return TRUE;
}

static HWND GetWindowHandle()
{
	HWND hWnd = NULL;
	EnumWindows(EnumWindowsProc, (LPARAM)&hWnd);

	return hWnd;
}

EndSceneT D3DHelper::GetEndScene()
{
	IDirect3D9* d3dInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3dInterface)
		return NULL;

	D3DPRESENT_PARAMETERS d3dPp = {};
	d3dPp.Windowed = TRUE;
	d3dPp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPp.hDeviceWindow = GetWindowHandle();

	LPDIRECT3DDEVICE9 d3dDevice = NULL;

	if (FAILED(d3dInterface->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dPp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPp, &d3dDevice)))
	{
		d3dInterface->Release();
		return NULL;
	}

	uintptr_t* vTable = *reinterpret_cast<uintptr_t**>(d3dDevice);
	EndSceneT endScene = (EndSceneT)vTable[END_SCENE_INDEX];
	
	d3dDevice->Release();
	d3dInterface->Release();

	return endScene;
}