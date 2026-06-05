#include "pch.h"
#include "Application.h"

Application::Application()
	:hookManager(menu)
{
}

void Application::Run()
{
	while (running)
	{
		if (GetAsyncKeyState(VK_END) & 1)
			running = false;

		Sleep(50);
	}
}