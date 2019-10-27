#include "Menu.h"
#include "Struct.h"


int main()
{
	// Read from BINARY
	struct Flight f = {2490, 215, "SH-NY", "BOEING-777", 1250.0};
	struct Flight f1 = { 1517, 280, "NY-TX", "BOEING-777", 2000.0 };
	struct Flight f2 = { 1200, 120, "TX-HS", "BOEING-777", 1550.0 };
	struct Flight f3 = { 1666, 58, "NJ-TX", "BOEING-777", 6000.0 };
	struct Flight f4 = { 3656, 35, "AL-CA", "BOEING-777", 2250.0 };
	struct Flight f5 = { 5212, 40, "DE-UK", "BOEING-777", 1235.0 };
	struct Flight f6 = { 1190, 215, "SH-NY", "BOEING-777", 1250.0 };
	struct Flight f7 = { 1817, 280, "NY-TX", "BOEING-777", 2000.0 };
	struct Flight f8 = { 1900, 120, "TX-HS", "BOEING-777", 1550.0 };
	struct Flight f9 = { 1116, 58, "NJ-TX", "BOEING-777", 6000.0 };
	struct Flight f10 = { 9656, 35, "AL-CA", "BOEING-777", 2250.0 };

	AddFlight(&f);
	AddFlight(&f1);
	AddFlight(&f2);
	AddFlight(&f3);
	AddFlight(&f4);
	AddFlight(&f5);
	AddFlight(&f6);
	AddFlight(&f7);
	AddFlight(&f8);
	AddFlight(&f9);
	AddFlight(&f10);

	ShowMenu();
	// Save
}