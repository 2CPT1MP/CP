#include "Menu.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void ShowMenu()
{
	enum Option chosenOption = FIRST;

	do
	{
		system("cls");
		puts(HEADER);
		for (short i = 0; i < MENU_SIZE; i++)
		{
			if (i == chosenOption)
				puts(SELECTED_OPTIONS[i]);
			else
				puts(NOT_SELECTED_OPTIONS[i]);
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
		}
	} while (1);

}