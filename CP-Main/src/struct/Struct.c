#include "Struct.h"
#include "..\menu\Menu.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

void AddFlight(const struct Flight* flight)
{
	if (!last)
	{
		first = last = (struct Node*)malloc(sizeof(struct Node));
		first->flight = *flight;
		last->next = 0;
		first->previous = 0;
		return;
	}
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	last->next = temp;
	temp->previous = last;
	last = temp;
	last->next = 0;
	last->flight = *flight;
}

void EraseFlight(const int flightNumber)
{
	for (struct Node* i = first; i != 0; i = i->next)
	{
		if (i->flight.flightNumber == flightNumber)
		{
			if (i->previous == 0)
			{
				first = i->next;
				if (first)
					first->previous = NULL;
				else
					last = first = NULL;
				free(i);
				return;
			}
			if (i->next == 0)
			{
				last = i->previous;
				last->next = NULL;
				free(i);
				return;
			}
			i->previous->next = i->next;
			i->next->previous = i->previous;
			free(i);
			return;
		}
	}
}

void ModifyFlight(const int flightNumber)
{
	for (const struct Node* i = first; i != 0; i = i->next)
	{
		if (i->flight.flightNumber == flightNumber);					// ??????????????????????????
	}
}

static void AlterFlight(struct Node* node)
{
	if (!node)
		return;

	struct Flight flight = node->flight;
	enum EditOption chosenOpt = FL_TITLE;

	while (1)
	{
		HideCursor();
		system("cls");
		SetConsoleColor(0, 15);
		puts("");
		puts(MAIN_HEADER);
		SetConsoleColor(15, 0);
		for (enum EditOption i = FL_NUM; i < EDIT_MENU_SIZE; i++)
		{
			putchar(' ');
			if (i == SAVE)
				printf("\n ");
			if (i == chosenOpt)
			{
				if (i == DEL)
				{
					SetConsoleColor(15, 4);
				}
				else
				{
					if (i == SAVE)
						SetConsoleColor(15, 2);
					else
						SetConsoleColor(0, 14);
				}
			}

			printf("%s", EDIT_OPTIONS[i]);
			if (i == SAVE || i == DEL)
				puts("");
			SetConsoleColor(15, 0);

			switch (i)
			{
			case FL_NUM:
				printf("%d\n", flight.flightNumber);
				break;
			case FL_TITLE:
				puts(flight.flightTitle);
				break;
			case PL_MODEL:
				puts(flight.planeModel);
				break;
			case EXP:
				printf("%f\n", flight.expenses);
				break;
			case PASS:
				printf("%d\n", flight.passengerCount);
				break;
			}
		
		}
		switch (_getch())
		{
		case 72:
			if (chosenOpt - 1 >= FL_NUM)
				chosenOpt--;
			break;
		case 80:
			if (chosenOpt + 1 < EDIT_MENU_SIZE)
				chosenOpt++;
			break;
		case 13:
			break;
		case 27:
			return;
		}
	}
	
	
	
}


void DisplayAll()
{
	struct Node* chosenNode = first;
	
	while (1)
	{
		HideCursor();
		system("cls");
		SetConsoleColor(0, 15);
		puts("");
		puts(MAIN_HEADER);
		SetConsoleColor(7, 0);
		putchar(' ');
		SetConsoleColor(0, 15);
		puts(TABLE_HEADER);
		SetConsoleColor(15, 0);

		for (const struct Node* i = first; i != 0; i = i->next)
		{
			putchar(' ');
			if (i == chosenNode)
				SetConsoleColor(0, 3);
			printf("  %15d%15s %15s %15.2f$  %15d \n", i->flight.flightNumber, i->flight.flightTitle,
				i->flight.planeModel, i->flight.expenses, i->flight.passengerCount);
			SetConsoleColor(15, 0);
		}
		printf("\n ");
		SetConsoleColor(4, 15);
		printf("                       ENTER - Alter record    ESC - back                          \n");
		SetConsoleColor(15, 0);

		switch (_getch())
		{
		case 80:
			if (chosenNode->next)
				chosenNode = chosenNode->next;
			break;
		case 72:
			if (chosenNode->previous)
				chosenNode = chosenNode->previous;
			break;
		case 13:
			puts("");
			AlterFlight(chosenNode);
			break;
		case 27:
			return;
		}
	}
}