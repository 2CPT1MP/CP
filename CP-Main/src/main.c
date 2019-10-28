#include <locale.h>
#include <stdio.h>
#include <Windows.h>

#include "Menu.h"
#include "Struct.h"
#include "Binary.h"


int main()
{
	SetConsoleTitle("Flights Database");
	ReadData();
	ShowMenu();
	SaveData(first);
	
	return 0;
}