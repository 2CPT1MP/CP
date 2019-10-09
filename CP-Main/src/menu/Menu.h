#pragma once

#define HEADER "========================================\n            FLIGHTS DATABASE\n========================================\n"

const char* NOT_SELECTED[] = { "    Open text file", "    Display the sheet", "    Find a record", "    Save as text", "    Exit" };
const char* SELECTED[] = { "=>  Open text file", "=>  Display the sheet", "=>  Find a record", "=>  Save as text", "=>  Exit" };

void ShowMenu();