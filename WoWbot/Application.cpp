#include "pch.h"
#include "Application.h"

Application::Application()
	:hookManager(menu)
{
	spdlog::set_level(spdlog::level::debug);
}

void Application::Run()
{
	while (!hookManager.IsUnload())
	{
		Sleep(50);
	}
}