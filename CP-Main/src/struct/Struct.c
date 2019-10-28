#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

#include "Struct.h"
#include "Menu.h"
#include "Binary.h"

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


int SelectField(enum EditMenuOption chosenOption, struct Flight* flight)
{
	if (chosenOption >= FLIGHT_NUM_OPTION &&
		chosenOption <= PASSENGER_COUNT_OPTION)
	{
		SetConsoleColor(3, 0);
		NewLine();
		printf(" Data> ");
		HideCursor(FALSE);
	}
	
	switch (chosenOption)
	{
	case FLIGHT_NUM_OPTION:
		scanf_s("%d", &flight->flightNumber);
		while (getchar() != '\n');
		break;
	case FLIGHT_TITLE_OPTION:
		fgets(flight->flightTitle, TITLE_CAPACITY, stdin);
		flight->flightTitle[strlen(flight->flightTitle) - 1] = 0;
		fseek(stdin, 0, SEEK_END);
		break;
	case PLANE_MODEL_OPTION:
		fgets(flight->planeModel, PLANE_MODEL_CAPACITY, stdin);
		flight->planeModel[strlen(flight->planeModel) - 1] = 0;
		fseek(stdin, 0, SEEK_END);
		break;
	case EXPENSES_OPTION:
		scanf_s("%f", &flight->expenses);
		while (getchar() != '\n');
		break;
	case PASSENGER_COUNT_OPTION:
		scanf_s("%d", &flight->passengerCount);
		while (getchar() != '\n');
		break;
	case CANCEL_OPTION:
		flight->flightNumber = -1;
		return;
	case SAVE_OPTION:
		HideCursor(TRUE);
		NewLine();
		return TRUE;
	}
	HideCursor(TRUE);
	NewLine();
	return FALSE;
}


struct Flight MakeFlight()
{
	struct Flight flight = { 0, 0, "?", "?", 0.0f };
	enum EditMenuOption chosenOption = FLIGHT_NUM_OPTION;

	while (TRUE)
	{
		HideCursor(TRUE);
		DisplayMainHeader();
		DrawEditMenuFrame(chosenOption, &flight);

		switch (_getch())
		{
		case UP_ARROW_KEY:
			if (chosenOption - 1 >= FLIGHT_NUM_OPTION)
				chosenOption--;
			break;
		case DOWN_ARROW_KEY:
			if (chosenOption + 1 < EDIT_MENU_SIZE - 1)
				chosenOption++;
			break;
		case ENTER_KEY:
			if (SelectField(chosenOption, &flight))
				return flight;
			break;
		case ESC_KEY:
			return (struct Flight){ -1, 0, "[UNDEFINED]", "[UNDEFINED]", 0.0f };
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

	while (TRUE)
	{
		HideCursor(TRUE);
		system("cls");
		SetConsoleColor(0, 15);
		puts("");
		puts(MAIN_HEADER);
		SetConsoleColor(15, 0);
		for (enum EditMenuOption i = FLIGHT_NUM_OPTION; i < EDIT_MENU_SIZE; i++)
		{
			putchar(' ');
			if (i == CANCEL_OPTION)
				NewLine();
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
		case UP_ARROW_KEY:
			if (chosenOpt - 1 >= FLIGHT_NUM_OPTION)
				chosenOpt--;
			break;
		case DOWN_ARROW_KEY:
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
				HideCursor(TRUE);
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
		case ESC_KEY:
			return;
		}
	}
}


void DisplayAll()
{
	struct Node* chosenNode = first;
	while (TRUE)
	{
		HideCursor(TRUE);
		DrawRecordsFrame(chosenNode);

		switch (_getch())
		{
		case DOWN_ARROW_KEY:
			if (chosenNode && chosenNode->next)
				chosenNode = chosenNode->next;
			break;
		case UP_ARROW_KEY:
			if (chosenNode && chosenNode->previous)
				chosenNode = chosenNode->previous;
			break;
		case ENTER_KEY:
			puts("");
			AlterFlight(chosenNode);
			chosenNode = first;
			break;
		case ESC_KEY:
			return;
		}
	}
}