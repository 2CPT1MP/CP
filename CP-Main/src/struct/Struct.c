#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

#include "Struct.h"
#include "Menu.h"
#include "Binary.h"


struct Node *first = 0, *last = 0;


long GetTotalPassengerCount()
{
	long passCount = 0;
	for (const struct Node* i = first; i != NULL; i = i->next)
		passCount += i->flight.passengerCount;
	return passCount;
}


float GetTotalExpenses()
{
	float totalExp = 0.0f;
	for (const struct Node* i = first; i != NULL; i = i->next)
		totalExp += i->flight.expenses;
	return totalExp;
}


float GetAvgExpenses()
{
	float totalExp = GetTotalExpenses();
	long passCount = GetTotalPassengerCount();
	return (passCount > 0)? totalExp / passCount : 0.0f ;
}


int AreEqualFlights(const struct Flight* firstFlight, const struct Flight* secondFlight)
{
	return firstFlight->expenses == secondFlight->expenses           &&
		firstFlight->flightNumber == secondFlight->flightNumber      &&
		!wcscmp(firstFlight->flightTitle, secondFlight->flightTitle) &&
		!wcscmp(firstFlight->planeModel, secondFlight->planeModel)   &&
		firstFlight->passengerCount == secondFlight->passengerCount;
}

int GetIndex(const struct Node* node)
{
	int j = 0;
	for (const struct Node* i = first; i != NULL; i = i->next)
	{
		if (node == i)
			return j;
		j++;
	}
}

void SortListByNum()
{
	for (struct Node* i = first; i != NULL; i = i->next)
	{
		for (struct Node* j = first; j->next != NULL; j = j->next)
		{
			if (j->flight.flightNumber > j->next->flight.flightNumber)
			{
				struct Flight t = j->flight;
				j->flight = j->next->flight;
				j->next->flight = t;
			}
		}
	}
}

void DelAll()
{
	if (!first)
		return;
	if (!first->next)
	{
		free(first);
	}
	else {
		for (struct Node* i = first->next; i != NULL; i = i->next)
		{
			free(i->previous);
			if (!i->next)
			{
				free(i);
				break;
			}
		}
	}
	first = last = NULL;
}


struct Node* FindFlightByNum(int flightNumber)
{
	for (struct Node* i = first; i != NULL; i = i->next)
		if (i->flight.flightNumber == flightNumber)
			return i;
	return EOF;
}


int HasAdditionalElms(const struct Node* node)
{
	int count = 0;
	for (struct Node* i = node; i != NULL; i = i->next)
		count++;
	if (count > 9)
		return 1;
	else
		return 0;
}


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
		SetConsoleColor(GREEN_COLOR, BLACK_COLOR);
		NewLine();
		wprintf(L"  Введите данные> ");
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
		return FALSE;
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
		WipeRows();

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
			SelectField(chosenOption, &flight);
			if (chosenOption == SAVE_OPTION || chosenOption == CANCEL_OPTION)
				return flight;
			else
				continue;
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
	
	struct Flight newFlight = node->flight;
	enum EditMenuOption chosenOption = FLIGHT_NUM_OPTION;

	while (TRUE)
	{
		DrawFlightAlterationFrame(&newFlight, &node->flight, chosenOption);

		int testValue = 0;
		switch (_getch())
		{
		case UP_ARROW_KEY:
			if (chosenOption - 1 >= FLIGHT_NUM_OPTION)
				chosenOption--;
			break;
		case DOWN_ARROW_KEY:
			if (chosenOption + 1 < EDIT_MENU_SIZE)
				chosenOption++;
			break;
		case ENTER_KEY:
			WipeRows();
			switch (chosenOption)
			{
			case FLIGHT_NUM_OPTION:
				NewLine();
				SetConsoleColor(BLUE_COLOR, BLACK_COLOR);
				wprintf(L"  Введите данные> ");
				HideCursor(FALSE);
				wscanf_s(L"%d", &newFlight.flightNumber);
				SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
				HideCursor(TRUE);
				while (getwchar() != '\n');
				continue;
			case FLIGHT_TITLE_OPTION:
				NewLine();
				SetConsoleColor(BLUE_COLOR, BLACK_COLOR);
				wprintf(L"  Введите данные> ");
				HideCursor(FALSE);
				fgetws(newFlight.flightTitle, TITLE_CAPACITY, stdin);
				SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
				newFlight.flightTitle[wcslen(newFlight.flightTitle) - 1] = 0;
				fseek(stdin, 0, SEEK_END);
				HideCursor(TRUE);
				continue;
			case PLANE_MODEL_OPTION:
				NewLine(FALSE);
				SetConsoleColor(BLUE_COLOR, BLACK_COLOR);
				wprintf(L"  Введите данные> ");
				HideCursor(FALSE);
				fgetws(newFlight.planeModel, PLANE_MODEL_CAPACITY, stdin);
				SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
				newFlight.planeModel[wcslen(newFlight.planeModel) - 1] = 0;
				fseek(stdin, 0, SEEK_END);
				HideCursor(TRUE);
				continue;
			case EXPENSES_OPTION:
				NewLine();
				SetConsoleColor(BLUE_COLOR, BLACK_COLOR);
				wprintf(L"  Введите данные> ");
				HideCursor(FALSE);
				wscanf_s(L"%f", &newFlight.expenses);
				SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
				HideCursor(TRUE);
				while (getwchar() != '\n');
				continue;
			case PASSENGER_COUNT_OPTION:
				NewLine();
				SetConsoleColor(BLUE_COLOR, BLACK_COLOR);
				wprintf(L"  Введите данные> ");
				HideCursor(FALSE);
				wscanf_s(L"%d", &newFlight.passengerCount);
				SetConsoleColor(BLUE_COLOR, BLACK_COLOR);
				HideCursor(TRUE);
				while (getwchar() != '\n');
				continue;
			case SAVE_OPTION:
				if (!AreEqualFlights(&node->flight, &newFlight))
				{
						SetConsoleColor(YELLOW_COLOR, BLACK_COLOR);
						NewLine();
						wprintf(L" [ПОДТВЕРЖДЕНИЕ] Подтвердите номер рейса для редактирования записи> ");
						SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
						HideCursor(FALSE);
						wscanf_s(L"%d", &testValue);
						fseek(stdin, 0, SEEK_END);
						HideCursor(TRUE);

						if (testValue == node->flight.flightNumber)
						{
							node->flight = newFlight;
							SaveData(first);
							SetConsoleColor(GREEN_COLOR, BLACK_COLOR);
							wprintf(L" [УСПЕХ] Изменение успешно подтверждено");
							NewLine();
							SetConsoleColor(BLUE_COLOR, BLACK_COLOR);
							wprintf(L" [ИНФОРМАЦИЯ] Нажмите любую клавишу чтобы продолжить");
							SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
							NewLine();
							_getwch();
							return;
						}
						SetConsoleColor(RED_COLOR, BLACK_COLOR);
						wprintf(L" [ОШИБКА] Операция редактирование отклонена. Неверный номер рейса");
						NewLine();
						SetConsoleColor(BLUE_COLOR, BLACK_COLOR);
						wprintf(L" [ИНФОРМАЦИЯ] Нажмите любую клавишу чтобы продолжить");
						SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
						NewLine();
						_getwch();
						continue;
				}
				SetConsoleColor(BLUE_COLOR, BLACK_COLOR);
				NewLine();
				wprintf(L" [УВЕДОМЛЕНИЕ] Не было внесено изменений в запись");
				NewLine();
				SetConsoleColor(BLUE_COLOR, BLACK_COLOR);
				wprintf(L" [ИНФОРМАЦИЯ] Нажмите любую клавишу чтобы продолжить");
				SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
				NewLine();
				_getwch();
				continue;
			case DELETE_OPTION:
				SetConsoleColor(YELLOW_COLOR, BLACK_COLOR);
				NewLine();
				wprintf(L" [ПОДТВЕРЖДЕНИЕ] Подтвердите номер рейса для удаления записи> ");
				SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
				HideCursor(FALSE);
				wscanf_s(L"%d", &testValue);
				fseek(stdin, 0, SEEK_END);
				HideCursor(TRUE);
				if (testValue == node->flight.flightNumber)
				{
					EraseFlight(node->flight.flightNumber);
					SaveData(first);
					SetConsoleColor(10, 0);
					wprintf(L" [УСПЕХ] Операция удаления одобрена");
					NewLine();
					SetConsoleColor(BLUE_COLOR, BLACK_COLOR);
					wprintf(L" [ИНФОРМАЦИЯ] Нажмите любую клавишу чтобы продолжить");
					SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
					NewLine();
					_getch();
					return;
				} 
				SetConsoleColor(4, 0);
				wprintf(L" [ОШИБКА] Операция удаления отклонена. Неверный номер рейса");
				NewLine();
				SetConsoleColor(BLUE_COLOR, BLACK_COLOR);
				wprintf(L" [ИНФОРМАЦИЯ] Нажмите любую клавишу чтобы продолжить");
				SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
				NewLine();
				_getch();
				continue;
			case CANCEL_OPTION:
				return;
			}
		case ESC_KEY:
			return;
		}
	}
}


void DisplayRecords(struct Node* chosenNode, int seekMode)
{
	while (TRUE)
	{
		HideCursor(TRUE);
		DrawRecordsFrame(chosenNode, seekMode);

		switch (_getch())
		{
		case DOWN_ARROW_KEY:
			if (chosenNode && chosenNode->next && !seekMode)
				chosenNode = chosenNode->next;
			break;
		case UP_ARROW_KEY:
			if (chosenNode && chosenNode->previous && !seekMode)
				chosenNode = chosenNode->previous;
			break;
		case ENTER_KEY:
			AlterFlight(chosenNode);
			chosenNode = first;
			return;
		case ESC_KEY:
			return;
		}
	}
}