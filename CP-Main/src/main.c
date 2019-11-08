#include <locale.h>
#include <stdio.h>
#include <Windows.h>
#include "Menu.h"
#include "Struct.h"
#include "Binary.h"
#include <locale.h>
#include <io.h>
#include <fcntl.h>
#include "Text.h"


void SetFontInfo()
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;              
	cfi.dwFontSize.Y = 25;                  
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy(cfi.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}


int main()
{
	SetFontInfo();
	setlocale(LC_ALL, "Rus");
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	SetConsoleTitle("Flights Database");
	ReadData();
	ShowMenu();
	SaveData(first);
	return 0;
}