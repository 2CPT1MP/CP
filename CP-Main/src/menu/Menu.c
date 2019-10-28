#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

#include "Menu.h"
#include "Struct.h"
#include "Binary.h"


HANDLE outHandle;


void DisplayMainHeader()
{
	SetConsoleCursorPosition(outHandle, (COORD) { 0, 0 });
	SetConsoleColor(15, 0);
	NewLine();
	SetConsoleColor(0, 15);
	printf("%s", MAIN_HEADER_LINE);
	NewLine();
	printf("%s", MAIN_HEADER);
	printf("%s", MAIN_HEADER_LINE);
	NewLine();
	SetConsoleColor(15, 0);
	NewLine();
}


void WipeRows()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(outHandle, &info);
	COORD winPos = (COORD) { info.srWindow.Right, info.srWindow.Bottom };
	for (COORD cursorPos = GetConsoleCursorPosition(); cursorPos.Y < winPos.Y; cursorPos.Y++)
		NewLine();
	SetConsoleCursorPosition(outHandle, (COORD) { info.dwCursorPosition.X, info.dwCursorPosition.Y });
}


void DrawEditMenuFrame(enum EditMenuOption chosenOption, const struct Flight* flight)
{
	for (enum EditMenuOption i = FLIGHT_NUM_OPTION; i < EDIT_MENU_SIZE - 1; i++)
	{
		if (i == CANCEL_OPTION)
			NewLine();
		if (i == DELETE_OPTION)
			continue;
		if (i == chosenOption)
		{
			if (i == SAVE_OPTION)
				SetConsoleColor(0, 2);
			else
				if (i == CANCEL_OPTION)
					SetConsoleColor(0, 6);
				else
					SetConsoleColor(0, 14);
		}
		printf("%s", EDIT_MENU_OPTIONS[i]);

		SetConsoleColor(15, 0);

		switch (i)
		{
		case FLIGHT_NUM_OPTION:
			printf("%15d\t", flight->flightNumber);
			break;
		case FLIGHT_TITLE_OPTION:
			printf("%15s\t", flight->flightTitle);
			break;
		case PLANE_MODEL_OPTION:
			printf("%15s\t", flight->planeModel);
			break;
		case EXPENSES_OPTION:
			printf("%15.2f$\t", flight->expenses);
			break;
		case PASSENGER_COUNT_OPTION:
			printf("%15d\t", flight->passengerCount);
			break;
		}
		SetConsoleColor(15, 0);
		NewLine();
	}
	WipeRows();
}


void DrawRecordsFrame(struct Node* chosenNode)
{
	DisplayMainHeader();
	SetConsoleColor(0, 9);
	printf("%s", TABLE_HEADER);
	NewLine();
	SetConsoleColor(15, 0);

	for (const struct Node* i = first; i != 0; i = i->next)
	{
		if (i == chosenNode)
			SetConsoleColor(0, 14);
		printf("  %15d%15s %15s %15.2f$  %15d ", i->flight.flightNumber, i->flight.flightTitle,
			i->flight.planeModel, i->flight.expenses, i->flight.passengerCount);
		NewLine();
		SetConsoleColor(15, 0);
	}
	NewLine();
	SetConsoleColor(0, 15);
	printf("                    ENTER - Edit record          ESC - Go back                          ");
	NewLine();
	SetConsoleColor(15, 0);
	WipeRows();
}


void DrawMainMenuFrame(enum MainMenuOption chosenOption)
{
	DisplayMainHeader();

	for (enum MainMenuOption i = OPEN_OPTION; i < MAIN_MENU_SIZE; i++)
	{
		if (i == chosenOption) {
			SetConsoleColor(0, 14);
			printf("%s", MAIN_MENU_OPTIONS[i]);
			SetConsoleColor(15, 0);
			NewLine();
		}
		else
		{
			printf("%s", MAIN_MENU_OPTIONS[i]);
			NewLine();
		}
	}
	WipeRows();
}


static void Run(const enum Option chosenOption)
{
	struct Flight flight;
	int isDuplicate = FALSE;
	switch (chosenOption)
	{
	case OPEN_OPTION:
		
		/*ADD CODE HERE*/
		
		break;
	case DISPLAY_OPTION:
		HideCursor(TRUE);              
		DisplayAll();
		break;
	case APPEND_OPTION:
		while (TRUE)
		{
			flight = MakeFlight();
			if (flight.flightNumber == -1)
				break;
			if (flight.flightNumber)
			{
				for (struct Node* i = first; i != 0; i = i->next)
				{
					if (i->flight.flightNumber == flight.flightNumber)
					{
						isDuplicate = TRUE;
						break;
					}
				}
				if (!isDuplicate)
				{
					AddFlight(&flight);
					SaveData(first);
					SetConsoleColor(10, 0);
					NewLine();
					printf(" [SUCCESS] Successfully added");
				}
				else {
					SetConsoleColor(4, 0);
					NewLine();
					printf(" [FAILURE] Not added. Duplicate ID found");
				}
			}
			else
			{
				SetConsoleColor(4, 0);
				NewLine();
				printf(" [FAILURE] Not added. Invalid flight info");
			}
			SetConsoleColor(15, 0);
			NewLine();
			WipeRows();
			_getch();
			continue;
		}
	case SEEK_OPTION:

		break;
	case SAVE_OPTION:
		

	case EXIT_OPTION:
		if (SaveData(first) != -1)
			exit(0);
		else
			
			/*OTHERWISE*/;
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


void NewLine()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(outHandle, &info);
	COORD winPos = (COORD) { info.dwSize.X, info.dwSize.Y };

	for (COORD cursorPos = GetConsoleCursorPosition(); cursorPos.X < winPos.X; cursorPos.X++)
		putchar(' ');

}


void ShowMenu()
{
	outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	enum MainMenuOption chosenOption = OPEN_OPTION;
	do
	{
		HideCursor(TRUE);
		DrawMainMenuFrame(chosenOption);
		
		switch (getch())
		{
		case UP_ARROW_KEY:
			if (chosenOption - 1 >= OPEN_OPTION)
				chosenOption--;
			break;
		case DOWN_ARROW_KEY:
			if (chosenOption + 1 < MAIN_MENU_SIZE)
				chosenOption++;
			break;
		case ENTER_KEY:
			Run(chosenOption);
			break;
		}
	} while (TRUE);
}