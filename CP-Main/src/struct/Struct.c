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
		wprintf(L" Введите данные> ");
		HideCursor(FALSE);
	}
	
	switch (chosenOption)
	{
	case FLIGHT_NUM_OPTION:
		wscanf_s(L"%d", &flight->flightNumber);
		fseek(stdin, 0, SEEK_END);
		break;
	case FLIGHT_TITLE_OPTION:
		fgetws(flight->flightTitle, TITLE_CAPACITY, stdin);
		flight->flightTitle[wcslen(flight->flightTitle) - 1] = 0;
		fseek(stdin, 0, SEEK_END);
		break;
	case PLANE_MODEL_OPTION:
		fgetws(flight->planeModel, PLANE_MODEL_CAPACITY, stdin);
		flight->planeModel[wcslen(flight->planeModel) - 1] = 0;
		fseek(stdin, 0, SEEK_END);
		break;
	case EXPENSES_OPTION:
		wscanf_s(L"%f", &flight->expenses);
		fseek(stdin, 0, SEEK_END);
		break;
	case PASSENGER_COUNT_OPTION:
		wscanf_s(L"%d", &flight->passengerCount);
		fseek(stdin, 0, SEEK_END);
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
	struct Flight flight = { 0, 0, L"Не задано", L"Не задано", 0.0f };
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
			return (struct Flight){ -1, 0, L"Не задано", L"Не задано", 0.0f };
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
	wcsncpy(flight.flightTitle, node->flight.flightTitle, TITLE_CAPACITY);
	wcsncpy(flight.planeModel, node->flight.planeModel, TITLE_CAPACITY);
	enum EditMenuOption chosenOpt = FLIGHT_NUM_OPTION;

	while (TRUE)
	{
		HideCursor(TRUE);
		system("cls");
		SetConsoleColor(0, 15);
		_putws("");
		_putws(MAIN_HEADER);
		SetConsoleColor(15, 0);
		for (enum EditMenuOption i = FLIGHT_NUM_OPTION; i < EDIT_MENU_SIZE; i++)
		{
			putwchar(' ');
			if (i == CANCEL_OPTION)
				NewLine();
				wprintf("\n ");
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

			wprintf(L"%s", EDIT_MENU_OPTIONS[i]);
			if (i == CANCEL_OPTION || i == SAVE_OPTION || i == DELETE_OPTION)
				_putws("");
			SetConsoleColor(15, 0);

			switch (i)
			{
			case FLIGHT_NUM_OPTION:
				wprintf(L"%15d\t", node->flight.flightNumber);
				if (flight.flightNumber != node->flight.flightNumber)
				{
					SetConsoleColor(6, 0);
					wprintf(L"\t| %17d |", flight.flightNumber);
					SetConsoleColor(15, 0);
				}
				_putws("");
				break;
			case FLIGHT_TITLE_OPTION:
				wprintf(L"%15s\t", node->flight.flightTitle);
				if (wcscmp(flight.flightTitle, node->flight.flightTitle))
				{
					SetConsoleColor(6, 0);
					wprintf(L"\t| %17s |", flight.flightTitle);
					SetConsoleColor(15, 0);
				}
				_putws("");
				break;
			case PLANE_MODEL_OPTION:
				wprintf(L"%15s\t", node->flight.planeModel);
				if (wcscmp(flight.planeModel, node->flight.planeModel))
				{
					SetConsoleColor(6, 0);
					wprintf(L"\t| %17s |", flight.planeModel);
					SetConsoleColor(15, 0);
				}
				_putws("");
				break;
			case EXPENSES_OPTION:
				wprintf(L"%14.2f РУБ\t", node->flight.expenses);
				if (flight.expenses != node->flight.expenses)
				{
					SetConsoleColor(6, 0);
					wprintf(L"\t| %16.2f РУБ |", flight.expenses);
					SetConsoleColor(15, 0);
				}
				_putws("");
				break;
			case PASSENGER_COUNT_OPTION:
				wprintf(L"%15d\t", node->flight.passengerCount);
				if (flight.passengerCount != node->flight.passengerCount)
				{
					SetConsoleColor(6, 0);
					wprintf(L"\t| %17d |", flight.passengerCount);
					SetConsoleColor(15, 0);
				}
				_putws("");
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
				wprintf(L"\n Введите данные:> ");
				HideCursor(0);
				wscanf_s(L"%d", &flight.flightNumber);
				HideCursor(1);
				fseek(stdout, 0, SEEK_END);
				continue;
			case FLIGHT_TITLE_OPTION:
				wprintf(L"\n Введите данные:> ");
				HideCursor(0);
				fgetws(flight.flightTitle, TITLE_CAPACITY, stdin);
				flight.flightTitle[wcslen(flight.flightTitle) - 1] = 0;
				fseek(stdin, 0, SEEK_END);
				HideCursor(1);
				continue;
			case PLANE_MODEL_OPTION:
				wprintf(L"\n Введите данные:> ");
				HideCursor(0);
				fgetws(flight.planeModel, PLANE_MODEL_CAPACITY, stdin);
				flight.planeModel[strlen(flight.planeModel) - 1] = 0;
				fseek(stdin, 0, SEEK_END);
				HideCursor(1);
				continue;
			case EXPENSES_OPTION:
				wprintf(L"\n Введите данные:> ");
				HideCursor(0);
				wscanf_s(L"%f", &flight.expenses);
				HideCursor(1);
				fseek(stdout, 0, SEEK_END);
				continue;
			case PASSENGER_COUNT_OPTION:
				wprintf(L"\n Введите данные:> ");
				HideCursor(0);
				wscanf_s(L"%d", &flight.passengerCount);
				HideCursor(1);
				fseek(stdout, 0, SEEK_END);
				continue;
			case SAVE_OPTION:
				if (node->flight.expenses != flight.expenses
					|| node->flight.flightNumber != flight.flightNumber
					|| strcmp(node->flight.flightTitle, flight.flightTitle)
					|| strcmp(node->flight.planeModel, flight.planeModel)
					|| node->flight.passengerCount != flight.passengerCount)
				{
						SetConsoleColor(6, 0);
						wprintf(L"\n [ПОДТВЕРЖДЕНИЕ] Подтвердите номер рейса для реадктирования записи:> ");
						SetConsoleColor(15, 0);
						HideCursor(0);
						wscanf_s(L"%d", &testValue);
						fseek(stdin, 0, SEEK_END);
						HideCursor(1);

						if (testValue == node->flight.flightNumber)
						{
							node->flight = flight;
							SaveData(first);
							SetConsoleColor(10, 0);
							_putws(L" [УСПЕХ] Изменение успешно подтверждено\n");
							putwchar(' ');
							SetConsoleColor(15, 0);
							system("pause");
							return;
						}
						SetConsoleColor(4, 0);
						_putws(L" [ОШИБКА] Операция редактирование отклонена. Неверный номер рейса\n");
						putwchar(' ');
						SetConsoleColor(15, 0);
						system("pause");
						continue;
				}
				
				SetConsoleColor(3, 0);
				_putws(L"\n [УВЕДОМЛЕНИЕ] Не было внесено изменений в запись\n");
				putwchar(' ');
				SetConsoleColor(15, 0);
				system("pause");
				continue;
			case DELETE_OPTION:
				SetConsoleColor(6, 0);
				wprintf(L"\n [ПОДТВЕРЖДЕНИЕ] Подтвердите номер рейса для удаления записи:> ");
				SetConsoleColor(15, 0);
				HideCursor(0);
				wscanf_s(L"%d", &testValue);
				fseek(stdout, 0, SEEK_END);
				HideCursor(TRUE);
				if (testValue == node->flight.flightNumber)
				{
					EraseFlight(node->flight.flightNumber);
					SaveData(first);
					SetConsoleColor(10, 0);
					_putws(L" [УСПЕХ] Операция удаления одобрена\n");
					putwchar(' ');
					SetConsoleColor(15, 0);
					system("pause");
					return;
				} 
				SetConsoleColor(4, 0);
				_putws(L" [ОШИБКА] Операция удаления отклонена. Неверный номер рейса\n");
				putwchar(' ');
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
			_putws("");
			AlterFlight(chosenNode);
			chosenNode = first;
			break;
		case ESC_KEY:
			return;
		}
	}
}