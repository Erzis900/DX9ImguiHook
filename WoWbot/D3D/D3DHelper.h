#pragma once
#include "pch.h"

constexpr int END_SCENE_INDEX = 42;

using EndSceneT = HRESULT(__stdcall*)(IDirect3DDevice9*);

namespace D3DHelper
{
	BOOL FetchData();
	BOOL FetchEndScene();

	inline EndSceneT endScene = NULL;
	inline HWND hWnd = NULL;
};