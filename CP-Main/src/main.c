#include <locale.h>
#include <stdio.h>
#include <Windows.h>

#include "Menu.h"
#include "Struct.h"
#include "Binary.h"
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	SetConsoleTitle("Flights Database");
	ReadData();
	ShowMenu();
	SaveData(first);
	
	return 0;
}