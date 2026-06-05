#pragma once

class Console
{
public:
	Console();
	~Console();

private:
	FILE* fp = NULL;
};