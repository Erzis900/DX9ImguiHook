#pragma once
#include "Console.h"
#include "Hooks/HookManager.h"
#include "Menu/Menu.h"

class Application
{
public:
	Application();
	void Run();

private:
	Console console;
	HookManager hookManager;
	Menu menu;

	bool running = true;
};