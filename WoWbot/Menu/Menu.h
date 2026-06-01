#pragma once

namespace Menu
{
	void Init(IDirect3DDevice9* pDevice);
	void Draw();
	void Shutdown();

	inline bool isInit = false;
}