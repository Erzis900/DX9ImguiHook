#pragma once

class Menu
{
public:
	~Menu();

	void InitImgui(IDirect3DDevice9* pDevice, HWND hWnd);
	void Draw();

	bool IsInit() const { return init; }
	void SetInit(bool newValue) { init = newValue; }

private:
	bool init = false;
};