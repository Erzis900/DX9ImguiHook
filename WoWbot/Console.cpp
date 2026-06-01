#include "pch.h"
#include "Console.h"

void Console::Init()
{
	AllocConsole();
	freopen_s(&fp, "CONOUT$", "w", stdout);
}

void Console::Shutdown()
{
	fclose(fp);
	FreeConsole();
}