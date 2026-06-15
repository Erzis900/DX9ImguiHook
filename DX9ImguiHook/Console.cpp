#include "pch.h"
#include "Console.h"

Console::Console()
{
	AllocConsole();
	freopen_s(&fp, "CONOUT$", "w", stdout);
	spdlog::debug("[Console] Opened");
}

Console::~Console()
{
	fclose(fp);
	FreeConsole();
}