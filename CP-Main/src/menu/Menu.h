#pragma once
#include <Windows.h>
#define MAIN_HEADER "                                                                                    \n"\
					"                                                                                    \n"\
				    "                                  FLIGHTS DATABASE                                  \n"\
                    "                                                                                    \n"\
                    "                                                                                    \n"


#define MAIN_MENU_SIZE 6
static const char* const MAIN_MENU_OPTIONS[MAIN_MENU_SIZE] = { " Open file     ",
															   " Display sheet ",
														       " Append record ",
														       " Find records  ", 
														       " Save text     ", 
														       " Exit program  "};
enum MainMenuOption
{
	OPEN_OPTION, DISPLAY_OPTION, APPEND_OPTION,
	SEEK_OPTION, SAVE_FILE_OPTION, EXIT_OPTION
};


#define EDIT_MENU_SIZE 8
static const char* const EDIT_MENU_OPTIONS[EDIT_MENU_SIZE] = { " Flight Number ",
										                       " Flight Title  ",
										                       " Plane Model   ",
										                       " Expenses      ",
										                       " Passengers    ",
	                                                           " CANCEL        ",
	                                                           " SAVE          ",
											                   " DELETE        "};
enum EditMenuOption
{
	FLIGHT_NUM_OPTION, FLIGHT_TITLE_OPTION, PLANE_MODEL_OPTION, EXPENSES_OPTION, 
	PASSENGER_COUNT_OPTION, CANCEL_OPTION, SAVE_OPTION, DELETE_OPTION
};


void ShowMenu();
void SetConsoleColor(int textColor, int bgColor);
void HideCursor(int state);
COORD GetConsoleCursorPosition();