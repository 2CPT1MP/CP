#pragma once
#define TABLE_HEADER L"     НОМЕР РЕЙСА | НАИМЕНОВАНИЕ |   МОДЕЛЬ САМОЛЁТА |       РАССТРАТЫ | ПАССАЖИРЫ"

#define TITLE_CAPACITY 15
#define PLANE_MODEL_CAPACITY 15
struct Flight
{
	int flightNumber, passengerCount;
	wchar_t flightTitle[TITLE_CAPACITY], planeModel[PLANE_MODEL_CAPACITY];
	float expenses;
};

struct Node
{
	struct Flight flight;
	struct Node *next, *previous;
} extern *first, *last;

void AddFlight(const struct Flight* flight);
void EraseFlight(const int flightNumber);
void DisplayRecords(struct Node* chosenRecord);
struct Flight MakeFlight();
struct Node* FindFlightByNum(int flightNumber);