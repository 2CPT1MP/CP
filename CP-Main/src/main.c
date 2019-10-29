#include <locale.h>
#include <stdio.h>
#include <Windows.h>


#include "Menu.h"
#include "Struct.h"
#include "Binary.h"
#include <locale.h>
#include <io.h>
#include <fcntl.h>

int main()
{
	setlocale(LC_ALL, "Rus");
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	SetConsoleTitle("Flights Database");
	ReadData();
	ShowMenu();
	SaveData(first);
	return 0;
}