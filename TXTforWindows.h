#pragma once
#include "TextPurpose.h"
#include <Windows.h>


namespace Cname {
	enum class CnameColor : int {
		Black = 0,
		Blue = 9,
		Red = 12,
		Yellow = 14,
		Aqua = 11,
		Green = 10,
		Purple = 13,
		Gray = 8,
		White = 15
	};

}

inline void cls() 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE) return;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD charsWritten;
	DWORD consoleSize;

	if(!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
	consoleSize = csbi.dwSize.X * csbi.dwSize.Y;

	FillConsoleOutputCharacter(hConsole, ' ', consoleSize, { 0, 0 }, &charsWritten);


	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, consoleSize, { 0, 0 }, &charsWritten);


	SetConsoleCursorPosition(hConsole, { 0, 0 });
}



