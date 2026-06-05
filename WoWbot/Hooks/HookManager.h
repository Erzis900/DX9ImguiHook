#pragma once
#include "../D3D/D3DHelper.h"
#include "../Menu/Menu.h"

class HookManager
{
public:
	HookManager(Menu& menu);
	~HookManager();

	HRESULT OnEndScene(IDirect3DDevice9* device);

private:
	EndSceneT endScene;
	Menu& menu;
};