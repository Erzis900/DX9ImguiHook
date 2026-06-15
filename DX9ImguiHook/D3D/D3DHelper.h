#pragma once

constexpr int END_SCENE_INDEX = 42;

using EndSceneT = HRESULT(__stdcall*)(IDirect3DDevice9*);

namespace D3DHelper
{
	EndSceneT GetEndScene();
}