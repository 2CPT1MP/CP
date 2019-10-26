#include "menu/Menu.h"

#include "struct/Struct.h"

int main()
{
	// Read from BINARY
	struct Flight f = {1, 1, "1", "1", 1.0};
	struct Flight f1 = { 2, 2, "2", "2", 2.0 };
	struct Flight f2 = { 3, 3, "3", "3", 3.0 };
	struct Flight f3 = { 4, 4, "4", "4", 4.0 };
	struct Flight f4 = { 5, 5, "5", "5", 5.0 };
	struct Flight f5 = { 6, 6, "6", "6", 6.0 };
	
	AddFlight(&f);
	AddFlight(&f1);
	AddFlight(&f2);
	AddFlight(&f3);
	AddFlight(&f4);
	AddFlight(&f5);

	



	ShowMenu();
	// Save
}