#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

#include "Menu.h"
#include "Struct.h"
#include "Binary.h"
#include "Text.h"


HANDLE outHandle;


void DisplayMainHeader()
{
	SetConsoleCursorPosition(outHandle, (COORD) { 0, 0 });
	SetConsoleColor(15, 0);
	NewLine();
	SetConsoleColor(0, 15);
	wprintf(L"%s", MAIN_HEADER_LINE);
	NewLine();
	wprintf(L"%s", MAIN_HEADER);
	wprintf(L"%s", MAIN_HEADER_LINE);
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
	NewLine();
	SetConsoleColor(3, BLACK_COLOR);
	wprintf(L"  ДОБАВЛЕНИЕ НОВОГО РЕЙСА ");
	NewLine();
	SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
	
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
					SetConsoleColor(0, 15);
		}
		wprintf(L"%s", EDIT_MENU_OPTIONS[i]);

		SetConsoleColor(15, 0);

		switch (i)
		{
		case FLIGHT_NUM_OPTION:
			wprintf(L"%20d  ", flight->flightNumber);
			break;
		case FLIGHT_TITLE_OPTION:
			wprintf(L"%20s  ", flight->flightTitle);
			break;
		case PLANE_MODEL_OPTION:
			wprintf(L"%20s  ", flight->planeModel);
			break;
		case EXPENSES_OPTION:
			wprintf(L"%20.2f  ", flight->expenses);
			break;
		case PASSENGER_COUNT_OPTION:
			wprintf(L"%20d  ", flight->passengerCount);
			break;
		}
		SetConsoleColor(15, 0);
		NewLine();
	}
	WipeRows();
}



struct Node* lastChosenNode = -1;
void DrawRecordsFrame(struct Node* chosenNode)
{
	DisplayMainHeader();
	SetConsoleColor(3, BLACK_COLOR);
	NewLine();
	wprintf(L"%s", TABLE_HEADER);
	SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
	NewLine();
	int j = 1;
	if (chosenNode != first)
		SetConsoleColor(15, 0);
	else
		SetConsoleColor(8, 0);
	wprintf(L"\x2191");
	SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
	NewLine();
	if (HasAdditionalElms(chosenNode))
	{
		lastChosenNode = chosenNode;

	}

	if (lastChosenNode == -1)
		lastChosenNode = first;

	for (const struct Node* i = lastChosenNode; i != 0; i = i->next)
	{
		if (j > 10)
		{
			SetConsoleColor(15, 0);
			wprintf(L"\x2193");
			NewLine();
			break;
		}
		
		
		if (i == chosenNode)
		{
			SetConsoleColor(15, 0);
			wprintf(L"\x2588 ");
			SetConsoleColor(0, 15);
		}else
			wprintf(L"\x2591 ");
		wprintf(L" %6d %19s %17s %12.2f %10d ", i->flight.flightNumber, i->flight.flightTitle,
			i->flight.planeModel, i->flight.expenses, i->flight.passengerCount);
		SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
		if (j <= 10 && i == last) {
			NewLine();
			SetConsoleColor(8, 0);
			wprintf(L"\x2193");
		}
		NewLine();
		j++;
	}
	NewLine();
	SetConsoleColor(0, 15);
	wprintf(L"             ENTER - Перейти к записи        ESC - Вернутся назад");
	NewLine();
	SetConsoleColor(15, 0);
	WipeRows();
}


void DrawMainMenuFrame(enum MainMenuOption chosenOption)
{
	DisplayMainHeader();
	SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
	NewLine();

	for (enum MainMenuOption i = OPEN_OPTION; i < MAIN_MENU_SIZE; i++)
	{
		if (i == chosenOption) {
			SetConsoleColor(0, 15);
			wprintf(L"%s", MAIN_MENU_OPTIONS[i]);
			SetConsoleColor(15, 0);
			NewLine();
		}
		else
		{
			wprintf(L"%s", MAIN_MENU_OPTIONS[i]);
			NewLine();
		}
	}
	WipeRows();
}

void PrintAlterationFlightValues(const struct Flight* newFlight, const struct Flight* originalFlight, const enum EditMenuOption menuOption)
{
	switch (menuOption)
	{
	case FLIGHT_NUM_OPTION:
		wprintf(L"%20d  ", originalFlight->flightNumber);
		if (newFlight->flightNumber != originalFlight->flightNumber)
		{
			SetConsoleColor(YELLOW_COLOR, BLACK_COLOR);
			wprintf(L"\"%d\"", newFlight->flightNumber);
			SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
		}
		break;
	case FLIGHT_TITLE_OPTION:
		wprintf(L"%20s  ", originalFlight->flightTitle);
		if (wcscmp(originalFlight->flightTitle, newFlight->flightTitle))
		{
			SetConsoleColor(YELLOW_COLOR, BLACK_COLOR);
			wprintf(L"\"%s\"", newFlight->flightTitle);
			SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
		}
		break;
	case PLANE_MODEL_OPTION:
		wprintf(L"%20s  ", originalFlight->planeModel);
		if (wcscmp(originalFlight->planeModel, newFlight->planeModel))
		{
			SetConsoleColor(YELLOW_COLOR, BLACK_COLOR);
			wprintf(L"\"%s\"", newFlight->planeModel);
			SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
		}
		break;
	case EXPENSES_OPTION:
		wprintf(L"%20.2f  ", originalFlight->expenses);
		if (originalFlight->expenses != newFlight->expenses)
		{
			SetConsoleColor(YELLOW_COLOR, BLACK_COLOR);
			wprintf(L"\"%.2f\"", newFlight->expenses);
			SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
		}
		break;
	case PASSENGER_COUNT_OPTION:
		wprintf(L"%20d  ", originalFlight->passengerCount);
		if (originalFlight->passengerCount != newFlight->passengerCount)
		{
			SetConsoleColor(YELLOW_COLOR, BLACK_COLOR);
			wprintf(L"\"%d\"", newFlight->passengerCount);
			SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
		}
		break;
	}
}



void DisplayAlterationOptions(const struct Flight* newFlight, const struct Flight* originalFlight, const enum EditMenuOption chosenOption)
{
	NewLine();
	SetConsoleColor(3, BLACK_COLOR);
	wprintf(L"  РЕДАКТИРОВАНИЕ РЕЙСА ");
	SetConsoleColor(WHITE_COLOR, BLACK_COLOR);

	for (enum EditMenuOption i = FLIGHT_NUM_OPTION; i < EDIT_MENU_SIZE; i++)
	{
		if (i == CANCEL_OPTION)
			NewLine();
		NewLine();

		if (i == chosenOption)
		{
			switch (i)
			{
			case DELETE_OPTION:
				SetConsoleColor(WHITE_COLOR, RED_COLOR);
				break;
			case SAVE_OPTION:
				SetConsoleColor(BLACK_COLOR, GREEN_COLOR);
				break;
			case CANCEL_OPTION:
				SetConsoleColor(BLACK_COLOR, YELLOW_COLOR);
				break;
			default:
				SetConsoleColor(BLACK_COLOR, WHITE_COLOR);
				break;
			}
		}
		wprintf(EDIT_MENU_OPTIONS[i]);
		SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
		PrintAlterationFlightValues(newFlight, originalFlight, i);
	}
}


void DrawFlightAlterationFrame(const struct Flight* newFlight, const struct Flight* originalFlight, const enum EditMenuOption chosenOption)
{
	DisplayMainHeader();
	DisplayAlterationOptions(newFlight, originalFlight, chosenOption);
	SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
	NewLine();
	NewLine();
	NewLine();
	SetConsoleColor(3, BLACK_COLOR);
	wprintf(L"  СТАТИСТИКА ПО РЕЙСУ ");
	NewLine();
	SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
	wprintf(L"  Перевозка одного пассажира %11.2f РУБ", (originalFlight->passengerCount > 0) ? originalFlight->expenses / originalFlight->passengerCount : 0);
	NewLine();

	WipeRows();
}


static void Run(const enum Option chosenOption)
{
	struct Flight flight;
	struct Node* nodeAddress;
	int isDuplicate = FALSE;
	int inputInt = 0;
	wchar_t inputStr[40] = { 0 };
	switch (chosenOption)
	{
	case OPEN_OPTION:
		NewLine();
		NewLine();
		SetConsoleColor(GREEN_COLOR, BLACK_COLOR);
		wprintf(L"  Исходный файл> ");
		SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
		HideCursor(FALSE);
		fgetws(inputStr, 39, stdin);
		fseek(stdin, 0, SEEK_END);
		for (long i = 0; i < sizeof(inputStr) / sizeof(wchar_t); i++)
			if (inputStr[i] == '\n')
			{
				inputStr[i] = '\0';
				break;
			}
		HideCursor(TRUE);
		if (ReadText(inputStr) == -1)
		{
			NewLine();
			SetConsoleColor(RED_COLOR, BLACK_COLOR);
			wprintf(L" [ОШИБКА] Невозможно открыть файл");
			NewLine();
			SetConsoleColor(BLUE_COLOR, BLACK_COLOR);
			wprintf(L" [ИНФОРМАЦИЯ] Нажмите любую клавишу чтобы продолжить");
			NewLine();
			_getch();
			SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
		}
		else {
			SetConsoleColor(GREEN_COLOR, BLACK_COLOR);
			NewLine();
			wprintf(L" [УСПЕХ] Импорт завершён ");
			NewLine();
			SetConsoleColor(BLUE_COLOR, BLACK_COLOR);
			wprintf(L" [ИНФОРМАЦИЯ] Нажмите любую клавишу чтобы продолжить");
			SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
			NewLine();
			WipeRows();
			_getch();
		}
		break;
	case DISPLAY_OPTION:
		HideCursor(TRUE);
		DisplayRecords(first);
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
					SetConsoleColor(GREEN_COLOR, BLACK_COLOR);
					NewLine();
					wprintf(L" [УСПЕХ] Запись была добавлена ");
					NewLine();
					SetConsoleColor(BLUE_COLOR, BLACK_COLOR);
					wprintf(L" [ИНФОРМАЦИЯ] Нажмите любую клавишу чтобы продолжить");
					SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
					NewLine();
					WipeRows();
					_getch();
					return;

				}
				else {
					SetConsoleColor(RED_COLOR, BLACK_COLOR);
					NewLine();
					wprintf(L" [ОШИБКА] Запись не добавлена. Введённый номер рейса уже существует ");
					NewLine();
					SetConsoleColor(BLUE_COLOR, BLACK_COLOR);
					wprintf(L" [ИНФОРМАЦИЯ] Нажмите любую клавишу чтобы продолжить");
				}
			}
			else
			{
				SetConsoleColor(4, 0);
				NewLine();
				wprintf(L" [ОШИБКА] Запись не добавлена. Предоставлена неверная информация о рейсе ");
				NewLine();
				SetConsoleColor(BLUE_COLOR, BLACK_COLOR);
				wprintf(L" [ИНФОРМАЦИЯ] Нажмите любую клавишу чтобы продолжить");
			}
			SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
			NewLine();
			WipeRows();
			_getch();
			continue;
		}
		break;
	case SEEK_OPTION:
		NewLine();
		NewLine();
		SetConsoleColor(GREEN_COLOR, BLACK_COLOR);
		wprintf(L"  Номер рейса> ");
		SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
		HideCursor(FALSE);
		wscanf_s(L"%d", &inputInt);
		getwc(stdin);
		HideCursor(TRUE);
		nodeAddress = FindFlightByNum(inputInt);
		if (nodeAddress != EOF)
			DisplayRecords(nodeAddress);
		else
		{
			NewLine();
			SetConsoleColor(YELLOW_COLOR, BLACK_COLOR);
			wprintf(L" [ПРЕДУПРЕЖДЕНИЕ] Рейс не найден");
			NewLine();
			SetConsoleColor(BLUE_COLOR, BLACK_COLOR);
			wprintf(L" [ИНФОРМАЦИЯ] Нажмите любую клавишу чтобы продолжить");
			SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
			NewLine();
			_getch();
		}
		break;
	case SAVE_FILE_OPTION:
		NewLine();
		NewLine();
		SetConsoleColor(GREEN_COLOR, BLACK_COLOR);
		wprintf(L"  Конечный файл> ");
		SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
		HideCursor(FALSE);
		fgetws(inputStr, 39, stdin);
		fseek(stdin, 0, SEEK_END);
		for (long i = 0; i < sizeof(inputStr) / sizeof(wchar_t); i++)
			if (inputStr[i] == '\n')
			{
				inputStr[i] = '\0';
				break;
			}
		HideCursor(TRUE);
		if (SaveAsText(inputStr) == -1)
		{
			NewLine();
			SetConsoleColor(RED_COLOR, BLACK_COLOR);
			wprintf(L" [ОШИБКА] Ошибка при попытке доступа");
			NewLine();
			SetConsoleColor(BLUE_COLOR, BLACK_COLOR);
			wprintf(L" [ИНФОРМАЦИЯ] Нажмите любую клавишу чтобы продолжить");
			SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
			NewLine();
			_getch();
		}
		else {
			SetConsoleColor(GREEN_COLOR, BLACK_COLOR);
			NewLine();
			wprintf(L" [УСПЕХ] Успешное сохранение ");
			NewLine();
			SetConsoleColor(BLUE_COLOR, BLACK_COLOR);
			wprintf(L" [ИНФОРМАЦИЯ] Нажмите любую клавишу чтобы продолжить");
			SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
			NewLine();
			WipeRows();
			_getch();
		}
		break;
	case EXIT_OPTION:
		if (SaveData(first) != -1)
			exit(0);
		else
		{
			NewLine();
			SetConsoleColor(RED_COLOR, BLACK_COLOR);
			wprintf(L" [ОШИБКА] Невозможно сохранить изменения");
			NewLine();
			SetConsoleColor(BLUE_COLOR, BLACK_COLOR);
			wprintf(L" [ИНФОРМАЦИЯ] Нажмите любую клавишу чтобы продолжить");
			SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
			NewLine();
			_getch();
		}
		break;

	case SORT_OPTION:
		SortListByNum();
		NewLine();
		SetConsoleColor(GREEN_COLOR, BLACK_COLOR);
		wprintf(L" [УСПЕХ] Сортировка по номеру рейса прошла успешно");
		NewLine();
		SetConsoleColor(BLUE_COLOR, BLACK_COLOR);
		wprintf(L" [ИНФОРМАЦИЯ] Нажмите любую клавишу чтобы продолжить");
		SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
		NewLine();
		_getch();
		break;
	case STAT_OPTION:
		DisplayMainHeader();
		NewLine();
		SetConsoleColor(3, BLACK_COLOR);
		wprintf(L"  СТАТИСТИКА ПО РЕЙСАМ ");
		NewLine();
		SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
		wprintf(L"  Общее число пассажиров   %30d", GetTotalPassengerCount());
		NewLine();
		wprintf(L"  Общие затраты по рейсам  %30.2f", GetTotalExpenses());
		NewLine();
		wprintf(L"  Затраты на пассажира     %30.2f", GetAvgExpenses());
		WipeRows();
		NewLine();
		SetConsoleColor(BLUE_COLOR, BLACK_COLOR);
		NewLine();
		NewLine();
		wprintf(L" [ИНФОРМАЦИЯ] Нажмите любую клавишу чтобы продолжить");
		SetConsoleColor(WHITE_COLOR, BLACK_COLOR);
		NewLine();
		_getch();
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


void NewLine()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(outHandle, &info);
	COORD winPos = (COORD) { info.dwSize.X, info.dwSize.Y };

	for (COORD cursorPos = GetConsoleCursorPosition(); cursorPos.X < winPos.X; cursorPos.X++)
		putwchar(' ');

}


void ShowMenu()
{
	outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	enum MainMenuOption chosenOption = OPEN_OPTION;
	do
	{
		HideCursor(TRUE);
		DrawMainMenuFrame(chosenOption);
		WipeRows();
		
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