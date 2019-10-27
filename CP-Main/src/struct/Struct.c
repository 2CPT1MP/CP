#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

#include "Struct.h"
#include "Menu.h"
#include "binary/Binary.h"

struct Node extern *first = 0, *last = 0;


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

struct Flight MakeFlight()
{
	struct Flight flight = { 0 };
	enum EditMenuOption chosenOpt = FLIGHT_NUM_OPTION;

	while (1)
	{
		HideCursor(1);
		system("cls");
		SetConsoleColor(0, 15);
		puts("");
		puts(MAIN_HEADER);
		SetConsoleColor(15, 0);
		for (enum EditMenuOption i = FLIGHT_NUM_OPTION; i < EDIT_MENU_SIZE - 1; i++)
		{
			putchar(' ');
			if (i == CANCEL_OPTION)
				printf("\n ");
			if (i == DELETE_OPTION)
				continue;
			if (i == chosenOpt)
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
			if (i == CANCEL_OPTION || i == SAVE_OPTION)
				puts("");
			SetConsoleColor(15, 0);

			switch (i)
			{
			case FLIGHT_NUM_OPTION:
				printf("%15d\t\n", flight.flightNumber);
				break;
			case FLIGHT_TITLE_OPTION:
				printf("%15s\t\n", flight.flightTitle);
				break;
			case PLANE_MODEL_OPTION:
				printf("%15s\t\n", flight.planeModel);
				break;
			case EXPENSES_OPTION:
				printf("%15.2f$\t\n", flight.expenses);
				break;
			case PASSENGER_COUNT_OPTION:
				printf("%15d\t\n", flight.passengerCount);
				break;
			}
		}
		switch (_getch())
		{
		case 72:
			if (chosenOpt - 1 >= FLIGHT_NUM_OPTION)
				chosenOpt--;
			break;
		case 80:
			if (chosenOpt + 1 < EDIT_MENU_SIZE - 1)
				chosenOpt++;
			break;
		case 13:
			switch (chosenOpt)
			{
			case FLIGHT_NUM_OPTION:
				printf("\n Data> ");
				HideCursor(0);
				scanf_s("%d", &flight.flightNumber);
				HideCursor(1);
				while (getchar() != '\n');
				continue;
			case FLIGHT_TITLE_OPTION:
				printf("\n Data> ");
				HideCursor(0);
				fgets(flight.flightTitle, TITLE_CAPACITY, stdin);
				flight.flightTitle[strlen(flight.flightTitle) - 1] = 0;
				fseek(stdin, 0, SEEK_END);
				HideCursor(1);
				continue;
			case PLANE_MODEL_OPTION:
				printf("\n Data> ");
				HideCursor(0);
				fgets(flight.planeModel, PLANE_MODEL_CAPACITY, stdin);
				flight.planeModel[strlen(flight.planeModel) - 1] = 0;
				fseek(stdin, 0, SEEK_END);
				HideCursor(1);
				continue;
			case EXPENSES_OPTION:
				printf("\n Data> ");
				HideCursor(0);
				scanf_s("%f", &flight.expenses);
				HideCursor(1);
				while (getchar() != '\n');
				continue;
			case PASSENGER_COUNT_OPTION:
				printf("\n Data> ");
				HideCursor(0);
				scanf_s("%d", &flight.passengerCount);
				HideCursor(1);
				while (getchar() != '\n');
				continue;
			case SAVE_OPTION:
				return flight;
			case CANCEL_OPTION:
				return (struct Flight) {0};
			}
		case 27:
			return;
		}
	}
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

static void AlterFlight(struct Node* node)
{
	if (!node)
		return;

	struct Flight flight = node->flight;
	strcpy(flight.flightTitle, node->flight.flightTitle);
	strcpy(flight.planeModel, node->flight.planeModel);
	enum EditMenuOption chosenOpt = FLIGHT_NUM_OPTION;

	while (1)
	{
		HideCursor(1);
		system("cls");
		SetConsoleColor(0, 15);
		puts("");
		puts(MAIN_HEADER);
		SetConsoleColor(15, 0);
		for (enum EditMenuOption i = FLIGHT_NUM_OPTION; i < EDIT_MENU_SIZE; i++)
		{
			putchar(' ');
			if (i == CANCEL_OPTION)
				printf("\n ");
			if (i == chosenOpt)
			{
				if (i == DELETE_OPTION)
				{
					SetConsoleColor(15, 4);
				}
				else
				{
					if (i == SAVE_OPTION)
						SetConsoleColor(0, 2);
					else
						if (i == CANCEL_OPTION)
							SetConsoleColor(0, 6);
						else
							SetConsoleColor(0, 14);
				}
			}

			printf("%s", EDIT_MENU_OPTIONS[i]);
			if (i == CANCEL_OPTION || i == SAVE_OPTION || i == DELETE_OPTION)
				puts("");
			SetConsoleColor(15, 0);

			switch (i)
			{
			case FLIGHT_NUM_OPTION:
				printf("%15d\t", node->flight.flightNumber);
				if (flight.flightNumber != node->flight.flightNumber)
				{
					SetConsoleColor(6, 0);
					printf("\t| %17d |", flight.flightNumber);
					SetConsoleColor(15, 0);
				}
				puts("");
				break;
			case FLIGHT_TITLE_OPTION:
				printf("%15s\t", node->flight.flightTitle);
				if (strcmp(flight.flightTitle, node->flight.flightTitle))
				{
					SetConsoleColor(6, 0);
					printf("\t| %17s |", flight.flightTitle);
					SetConsoleColor(15, 0);
				}
				puts("");
				break;
			case PLANE_MODEL_OPTION:
				printf("%15s\t", node->flight.planeModel);
				if (strcmp(flight.planeModel, node->flight.planeModel))
				{
					SetConsoleColor(6, 0);
					printf("\t| %17s |", flight.planeModel);
					SetConsoleColor(15, 0);
				}
				puts("");
				break;
			case EXPENSES_OPTION:
				printf("%14.2f$\t", node->flight.expenses);
				if (flight.expenses != node->flight.expenses)
				{
					SetConsoleColor(6, 0);
					printf("\t| %16.2f$ |", flight.expenses);
					SetConsoleColor(15, 0);
				}
				puts("");
				break;
			case PASSENGER_COUNT_OPTION:
				printf("%15d\t", node->flight.passengerCount);
				if (flight.passengerCount != node->flight.passengerCount)
				{
					SetConsoleColor(6, 0);
					printf("\t| %17d |", flight.passengerCount);
					SetConsoleColor(15, 0);
				}
				puts("");
				break;
			}
		}
		int testValue = 0;
		switch (_getch())
		{
		case 72:
			if (chosenOpt - 1 >= FLIGHT_NUM_OPTION)
				chosenOpt--;
			break;
		case 80:
			if (chosenOpt + 1 < EDIT_MENU_SIZE)
				chosenOpt++;
			break;
		case 13:
			switch (chosenOpt)
			{
			case FLIGHT_NUM_OPTION:
				printf("\n Data> ");
				HideCursor(0);
				scanf_s("%d", &flight.flightNumber);
				HideCursor(1);
				while (getchar() != '\n');
				continue;
			case FLIGHT_TITLE_OPTION:
				printf("\n Data> ");
				HideCursor(0);
				fgets(flight.flightTitle, TITLE_CAPACITY, stdin);
				flight.flightTitle[strlen(flight.flightTitle) - 1] = 0;
				fseek(stdin, 0, SEEK_END);
				HideCursor(1);
				continue;
			case PLANE_MODEL_OPTION:
				printf("\n Data> ");
				HideCursor(0);
				fgets(flight.planeModel, PLANE_MODEL_CAPACITY, stdin);
				flight.planeModel[strlen(flight.planeModel) - 1] = 0;
				fseek(stdin, 0, SEEK_END);
				HideCursor(1);
				continue;
			case EXPENSES_OPTION:
				printf("\n Data> ");
				HideCursor(0);
				scanf_s("%f", &flight.expenses);
				HideCursor(1);
				while (getchar() != '\n');
				continue;
			case PASSENGER_COUNT_OPTION:
				printf("\n Data> ");
				HideCursor(0);
				scanf_s("%d", &flight.passengerCount);
				HideCursor(1);
				while (getchar() != '\n');
				continue;
			case SAVE_OPTION:
				if (node->flight.expenses != flight.expenses
					|| node->flight.flightNumber != flight.flightNumber
					|| strcmp(node->flight.flightTitle, flight.flightTitle)
					|| strcmp(node->flight.planeModel, flight.planeModel)
					|| node->flight.passengerCount != flight.passengerCount)
				{
						SetConsoleColor(6, 0);
						printf("\n [CONFIRMATION] Enter Flight Number> ");
						SetConsoleColor(15, 0);
						HideCursor(0);
						scanf_s("%d", &testValue);
						while (getchar() != '\n');
						HideCursor(1);

						if (testValue == node->flight.flightNumber)
						{
							node->flight = flight;
							SaveData(first);
							SetConsoleColor(10, 0);
							puts(" [SUCCESS] Edit confirmed\n");
							putchar(' ');
							SetConsoleColor(15, 0);
							system("pause");
							return;
						}
						SetConsoleColor(4, 0);
						puts(" [FAILURE] Invalid Confirmation Key\n");
						putchar(' ');
						SetConsoleColor(15, 0);
						system("pause");
						continue;
				}
				
				SetConsoleColor(3, 0);
				puts("\n [INFO] No changes were made\n");
				putchar(' ');
				SetConsoleColor(15, 0);
				system("pause");
				continue;
			case DELETE_OPTION:
				SetConsoleColor(6, 0);
				printf("\n [CONFIRMATION] Enter Flight Number> ");
				SetConsoleColor(15, 0);
				HideCursor(0);
				scanf_s("%d", &testValue);
				while (getchar() != '\n');
				HideCursor(1);
				if (testValue == node->flight.flightNumber)
				{
					EraseFlight(node->flight.flightNumber);
					SaveData(first);
					SetConsoleColor(10, 0);
					puts(" [SUCCESS] Deletion was successful\n");
					putchar(' ');
					SetConsoleColor(15, 0);
					system("pause");
					return;
				} 
				SetConsoleColor(4, 0);
				puts(" [FAILURE] Invalid Confirmation Key\n");
				putchar(' ');
				SetConsoleColor(15, 0);
				system("pause");
				continue;
			case CANCEL_OPTION:
				return;
			}
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
		HideCursor(1);
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
			if (chosenNode && chosenNode->next)
				chosenNode = chosenNode->next;
			break;
		case 72:
			if (chosenNode && chosenNode->previous)
				chosenNode = chosenNode->previous;
			break;
		case 13:
			puts("");
			AlterFlight(chosenNode);
			chosenNode = first;
			break;
		case 27:
			return;
		}
	}
}