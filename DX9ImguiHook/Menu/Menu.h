#pragma once

class Menu
{
public:
	~Menu();

	void InitImgui(IDirect3DDevice9* pDevice, HWND hWnd);
	void Draw();

	bool IsInit() const { return init; }
	void SetInit(bool newValue) { init = newValue; }
	void Toggle() { open = !open; }
	bool IsOpen() const { return open; }

private:
	bool init = false;
	bool open = true;
};