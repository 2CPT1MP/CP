#include "Menu.h"
#include "Struct.h"
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

static Run(enum Option option)
{
	switch (option)
	{
	case FIRST:
		break;
	case SECOND:
		HideCursor();
		system("cls");                  
		SetConsoleColor(0, 15);
		puts("");
		puts(MAIN_HEADER);
		SetConsoleColor(7, 0);
		DisplayAll();
		break;
	case THIRD:
		break;
	case FOURTH:
		break;
	case FIFTH:
		break;
	}
}

void SetConsoleColor(int textColor, int bgColor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
}

void HideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void ShowMenu()
{
	enum Option chosenOption = FIRST;
	do
	{
		HideCursor();
		system("cls");                 
		SetConsoleColor(0, 15);
		puts("");
		puts(MAIN_HEADER);
		SetConsoleColor(15, 0);
		
		for (short i = 0; i < MENU_SIZE; i++)
		{
			putchar(' ');
			if (i == chosenOption) {
				
				SetConsoleColor(0, 15);
				puts(OPTIONS[i]);
				SetConsoleColor(15, 0);
			}
			else
				puts(OPTIONS[i]);
		}
	
		switch (getch())
		{
		case 72:
			if (chosenOption - 1 >= FIRST)
				chosenOption--;
			break;
		case 80:
			if (chosenOption + 1 < MENU_SIZE)
				chosenOption++;
			break;
		case 13:
			Run(chosenOption);
			break;
		case 27:
			break;
		}
	} while (1);
}