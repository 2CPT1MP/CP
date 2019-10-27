#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

#include "Menu.h"
#include "Struct.h"


static Run(enum Option chosenOption)
{
	struct Flight flight;
	int isDuplicate = 0;
	switch (chosenOption)
	{
	case OPEN_OPTION:

		break;
	case DISPLAY_OPTION:
		HideCursor(1);
		system("cls");                  
		SetConsoleColor(0, 15);
		puts("");
		puts(MAIN_HEADER);
		SetConsoleColor(7, 0);
		DisplayAll();
		break;
	case APPEND_OPTION:
		flight = MakeFlight();
		if (flight.flightNumber)
		{
			struct Node* i = first;
			for (struct Node* i = first; i != 0; i = i->next) 
			{
				if (i->flight.flightNumber == flight.flightNumber) 
				{
					isDuplicate = 1;
					break;
				}
			}
			if (!isDuplicate)
				AddFlight(&flight);
		}
		break;
	case SEEK_OPTION:

		break;
	case SAVE_OPTION:

		break;
	case EXIT_OPTION:

		break;
	}
}

void SetConsoleColor(int textColor, int bgColor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
}

COORD GetConsoleCursorPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi))
		return cbsi.dwCursorPosition;
	else
		return (COORD){0, 0};
}

void HideCursor(int hide)
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 25;
	info.bVisible = !hide;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void ShowMenu()
{
	enum MainMenuOption chosenOption = OPEN_OPTION;
	do
	{
		HideCursor(1);
		system("cls");                 
		SetConsoleColor(0, 15);
		puts("");
		puts(MAIN_HEADER);
		SetConsoleColor(15, 0);
		
		for (enum MainMenuOption i = OPEN_OPTION; i < MAIN_MENU_SIZE; i++)
		{
			putchar(' ');
			if (i == chosenOption) {
				SetConsoleColor(0, 15);
				puts(MAIN_MENU_OPTIONS[i]);
				SetConsoleColor(15, 0);
			}
			else
				puts(MAIN_MENU_OPTIONS[i]);
		}
	
		switch (getch())
		{
		case 72:
			if (chosenOption - 1 >= OPEN_OPTION)
				chosenOption--;
			break;
		case 80:
			if (chosenOption + 1 < MAIN_MENU_SIZE)
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