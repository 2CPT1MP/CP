#pragma once
#define TABLE_HEADER "    FLIGHT NUMBER | FLIGHT TITLE |   PLANE MODEL |       EXPENSES |     PASSENGERS "

#define TITLE_CAPACITY 15
#define PLANE_MODEL_CAPACITY 15
struct Flight
{
	int flightNumber, passengerCount;
	char flightTitle[TITLE_CAPACITY], planeModel[PLANE_MODEL_CAPACITY];
	float expenses;
};

struct Node
{
	struct Flight flight;
	struct Node *next, *previous;
} extern *first, *last;

void AddFlight(const struct Flight* flight);
void EraseFlight(const int flightNumber);
void DisplayAll();
struct Flight MakeFlight();