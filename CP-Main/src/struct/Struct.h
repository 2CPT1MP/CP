﻿#pragma once
#define TABLE_HEADER L"  № РЕЙСА      НАЗВАНИЕ РЕЙСА\tМОДЕЛЬ САМОЛЁТА\t   РАССТРАТЫ  ПАССАЖИРЫ"

#define TITLE_CAPACITY 19
#define PLANE_MODEL_CAPACITY 19
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
void DisplayRecords(struct Node* chosenRecord, int seekMode);
struct Flight MakeFlight();
struct Node* FindFlightByNum(int flightNumber);
int GetIndex(const struct Node* node);
void SortListByNum();
void DelAll();
int HasAdditionalElms(const struct Node* node);
long GetTotalPassengerCount();
float GetTotalExpenses();
float GetAvgExpenses();