#pragma once
#define MAIN_HEADER "                                                        \n"\
				    "                    FLIGHTS DATABASE                    \n"\
                    "                                                        \n"

#define MENU_SIZE 5
static const char* OPTIONS[MENU_SIZE] = { " Open file     ",
                                          " Display sheet ", 
	                                      " Find records  ", 
	                                      " Save text     ", 
	                                      " Exit program  "};

static enum Option
{
	FIRST, SECOND, THIRD, FOURTH, FIFTH
};

void ShowMenu();