#pragma once
#define MAIN_HEADER "                                                                                    \n"\
					"                                                                                    \n"\
				    "                                  FLIGHTS DATABASE                                  \n"\
                    "                                                                                    \n"\
                    "                                                                                    \n"

#define MENU_SIZE 5
static const char* OPTIONS[MENU_SIZE] = { " Open file     ",
                                          " Display sheet ", 
	                                      " Find records  ", 
	                                      " Save text     ", 
	                                      " Exit program  "};

#define EDIT_MENU_SIZE 7
static const char* EDIT_OPTIONS[EDIT_MENU_SIZE] = { " Flight Number ",
										            " Flight Title  ",
										            " Plane Model   ",
										            " Expenses      ",
										            " Passengers    ",
	                                                " SAVE          ",
											        " DELETE        "};

enum EditOption
{
	FL_NUM, FL_TITLE, PL_MODEL, EXP, PASS, SAVE, DEL
};


enum Option
{
	FIRST, SECOND, THIRD, FOURTH, FIFTH
};

void ShowMenu();
void SetConsoleColor(int textColor, int bgColor);
void HideCursor();