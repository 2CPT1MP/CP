#pragma once
#define TABLE_HEADER "---------------------------------------------------------------------------\n"\
					  "FLIGHT NUMBER    FLIGHT TITLE    PLANE MODEL    EXPENSES    PASSENGER COUNT\n"\
					 "---------------------------------------------------------------------------"

#define TITLE_CAPACITY 35
#define PLANE_MODEL_LEN 6
static struct Flight
{
	int flightNumber, passengerCount;
	char flightTitle[TITLE_CAPACITY], planeModel[PLANE_MODEL_LEN];
	double expenses;
};

static struct Node
{
	struct Flight flight;
	struct Node *next, *previous;
} *first = 0, *last = 0;

void AddFlight(const struct Flight* flight);
void EraseFlight(const int flightNumber);
void ModifyFlight(const int flightNumber);
void DisplayAll();