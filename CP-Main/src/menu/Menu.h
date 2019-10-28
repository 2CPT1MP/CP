#pragma once
#include <Windows.h>
#define MAIN_HEADER      L"                              БАЗА ДАННЫХ РЕЙСОВ САМОЛЁТОВ                       "
#define MAIN_HEADER_LINE L"                                                                                 "            

#define ESC_KEY 27
#define ENTER_KEY 13
#define DOWN_ARROW_KEY 80
#define UP_ARROW_KEY 72


#define MAIN_MENU_SIZE 6
static const wchar_t* const MAIN_MENU_OPTIONS[MAIN_MENU_SIZE] = { L"  Открыть файл     ",
																  L"  Показать всё     ",
														          L"  Добавить запись  ",
																  L"  Поиск записи     ", 
																  L"  Сохранить как    ", 
																  L"  Завершить работу "};
enum MainMenuOption
{
	OPEN_OPTION, DISPLAY_OPTION, APPEND_OPTION,
	SEEK_OPTION, SAVE_FILE_OPTION, EXIT_OPTION
};


#define EDIT_MENU_SIZE 8
static const wchar_t* const EDIT_MENU_OPTIONS[EDIT_MENU_SIZE] = { L"  Номер рейса       ",
										                          L"  Наименование      ",
										                          L"  Модель самолёта   ",
																  L"  Растраты          ",
										                          L"  Кол-во пассажиров ",
	                                                              L"  ВЫХОД             ",
	                                                              L"  СОХРАНЕНИЕ        ",
											                      L"  УДАЛЕНИЕ          "};
enum EditMenuOption
{
	FLIGHT_NUM_OPTION, FLIGHT_TITLE_OPTION, PLANE_MODEL_OPTION, EXPENSES_OPTION, 
	PASSENGER_COUNT_OPTION, CANCEL_OPTION, SAVE_OPTION, DELETE_OPTION
};


void ShowMenu();
void DisplayMainHeader();
void DrawEditMenuFrame(enum EditMenuOption chosenOption, const struct Flight* flight);
void SetConsoleColor(int textColor, int bgColor);
void HideCursor(int state);
void NewLine();
void DrawRecordsFrame(struct Node* chosenNode);
COORD GetConsoleCursorPosition();