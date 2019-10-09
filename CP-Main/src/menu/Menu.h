#pragma once

#define HEADER "=========================================\n             FLIGHTS DATABASE\n=========================================\n"

#define MENU_SIZE 5
static const char* NOT_SELECTED_OPTIONS[MENU_SIZE] = { "   Open text file", "   Display the sheet", "   Find a record", "   Save as text", "   Exit" };
static const char* SELECTED_OPTIONS[MENU_SIZE] = { "=> Open text file", "=> Display the sheet", "=> Find a record", "=> Save as text", "=> Exit" };

static enum Option
{
	FIRST, SECOND, THIRD, FOURTH, FIFTH
};

void ShowMenu();