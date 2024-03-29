﻿#pragma once
#include <Windows.h>
#define MAIN_HEADER      L"                              БАЗА ДАННЫХ РЕЙСОВ САМОЛЁТОВ                       "
#define MAIN_HEADER_LINE L"                                                                                 "            

#define ESC_KEY 27
#define ENTER_KEY 13
#define DOWN_ARROW_KEY 80
#define UP_ARROW_KEY 72


#define MAIN_MENU_SIZE 8
static const wchar_t* const MAIN_MENU_OPTIONS[MAIN_MENU_SIZE] = { L"  Импорт рейсов        ",
																  L"  Просмотр рейсов      ",
														          L"  Добавление рейса     ",
																  L"  Сортировка рейсов    ",
																  L"  Поиск рейса          ",
	                                                              L"  Статистика по рейсам ",
																  L"  Экспорт рейсов       ", 
																  L"  Завершение работы    "};
enum MainMenuOption
{
	OPEN_OPTION, DISPLAY_OPTION, APPEND_OPTION, SORT_OPTION,
	SEEK_OPTION, STAT_OPTION, SAVE_FILE_OPTION, EXIT_OPTION,
};


#define EDIT_MENU_SIZE 8
static const wchar_t* const EDIT_MENU_OPTIONS[EDIT_MENU_SIZE] = { L"  Номер рейса    \t",
										                          L"  Наименование   \t",
										                          L"  Авиалайнер     \t",
																  L"  Общие затраты  \t",
										                          L"  Пассажиры      \t",
	                                                              L"  ОТМЕНА         \t",
	                                                              L"  СОХРАНЕНИЕ     \t",
											                      L"  УДАЛЕНИЕ       \t"};
enum EditMenuOption
{
	FLIGHT_NUM_OPTION, FLIGHT_TITLE_OPTION, PLANE_MODEL_OPTION, EXPENSES_OPTION, 
	PASSENGER_COUNT_OPTION, CANCEL_OPTION,  SAVE_OPTION,        DELETE_OPTION
};

enum ConsoleColor
{
	WHITE_COLOR = 15, BLACK_COLOR = 0, RED_COLOR = 4, 
	GREEN_COLOR = 2,  YELLOW_COLOR= 6, BLUE_COLOR = 3
};


void ShowMenu();
void WipeRows();
void DisplayMainHeader();
void DrawFlightAlterationFrame(const struct Flight* newFlight, const struct Flight* originalFlight, const enum EditMenuOption chosenOption);
void DrawEditMenuFrame(enum EditMenuOption chosenOption, const struct Flight* flight);
void SetConsoleColor(int textColor, int bgColor);
void HideCursor(int state);
void NewLine();
void DrawRecordsFrame(struct Node* chosenNode, int seekMode);
COORD GetConsoleCursorPosition();