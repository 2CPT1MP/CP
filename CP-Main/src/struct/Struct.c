#include "Struct.h"
#include <stdlib.h>
#include <stdio.h>

void AddFlight(const struct Flight* flight)
{
	if (!last)
	{
		first = last = (struct Node*)malloc(sizeof(struct Node));
		first->flight = *flight;
		last->next = 0;
		first->previous = 0;
		return;
	}
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	last->next = temp;
	temp->previous = last;
	last = temp;
	last->next = 0;
	last->flight = *flight;
}

void EraseFlight(const int flightNumber)
{
	for (struct Node* i = first; i != 0; i = i->next)
	{
		if (i->flight.flightNumber == flightNumber)
		{
			if (i->previous == 0)
			{
				first = i->next;
				free(i);
				return;
			}
			if (i->next == 0)
			{
				last = i->previous;
				free(i);
				return;
			}
			i->previous->next = i->next;
			free(i);
		}
	}
}

void ModifyFlight(const int flightNumber)
{
	for (const struct Node* i = first; i != 0; i = i->next)
	{
		if (i->flight.flightNumber == flightNumber);					// ??????????????????????????
	}
}

void DisplayAll()
{
	puts(TABLE_HEADER);
	for (const struct Node* i = first; i != 0; i = i->next)
	{
		printf("%d	%s	%s	%f	%d\n", i->flight.flightNumber, i->flight.flightTitle, 
				i->flight.planeModel, i->flight.expenses, i->flight.passengerCount);
	}
}