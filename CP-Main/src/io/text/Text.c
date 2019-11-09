#include "Text.h"
#include <wchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include "Struct.h"
#include "Menu.h"

int SaveAsText(const wchar_t* filename)
{
	FILE* fStream = _wfopen(filename, L"wt, ccs=UNICODE");
	if (!fStream)
		return -1;

	_setmode(_fileno(fStream), _O_U16TEXT);

	/*fwprintf(fStream, L"%20s\t%20s\t%20s\t%20s\t%20s\n\n", L"НОМЕР АВИАРЕЙСА", L"НАИМЕНОВАНИЕ РЕЙСА",
	L"МОДЕЛЬ САМОЛЁТА", L"ОБЩИЕ ЗАТРАТЫ", L"КОЛ-ВО ПАССАЖИРОВ");*/

	for (struct Node* i = first; i != NULL; i = i->next)
	{
		fwprintf_s(fStream, L"\"%d\"\t\"%s\"\t\"%s\"\t\"%.2f\"\t\"%d\"\n", i->flight.flightNumber, i->flight.flightTitle,
			i->flight.planeModel, i->flight.expenses, 
			i->flight.passengerCount);
	}
	fclose(fStream);
	return 0;
}

int ReadText(const wchar_t* filename)
{
	FILE* fStream = _wfopen(filename, L"rt, ccs=UNICODE");
	if (!fStream)
		return -1;
	DelAll();

	_setmode(_fileno(fStream), _O_U16TEXT);

	wchar_t inputChar = getwc(fStream);
	wchar_t* stopstr = (wchar_t*)malloc(sizeof(wchar_t) * 40);
	int fieldNum = 1;
	int isDuplicate = FALSE;
	struct Flight f = {0, 0, 0, 0, 0};
	while (!feof(fStream))
	{
		if (inputChar == '\"')
		{
			wchar_t charArray[TITLE_CAPACITY] = { 0 };
			inputChar = getwc(fStream);
			for (int i = 0; i < TITLE_CAPACITY, inputChar != '\"'; i++)
			{
				charArray[i] = inputChar;
				inputChar = getwc(fStream);
			}
			inputChar = getwc(fStream);
			int intIn;
			float floatIn;
			switch (fieldNum)
			{
			case 1:
				f.flightNumber = wcstol(charArray, stopstr, 10, "Rus");
				fieldNum++;
				break;
			case 2:
				wcscpy(f.flightTitle, charArray);
				fieldNum++;
				break;
			case 3:
				wcscpy(f.planeModel, charArray);
				fieldNum++;
				break;
			case 4:
				f.expenses = wcstof(charArray, stopstr);
				fieldNum++;
				break;
			case 5:
				f.passengerCount = wcstol(charArray, stopstr, 10, "Rus");
				/*VALIDATING AND ADDING STUFF*/

				for (struct Node* i = first; i != 0; i = i->next)
				{
					if (i->flight.flightNumber == f.flightNumber)
					{
						isDuplicate = TRUE;
						break;
					}
				}
				if (isDuplicate == FALSE && f.flightNumber > 0)
					AddFlight(&f);
				isDuplicate = FALSE;
				fieldNum = 1;
				break;
			}

		}
		inputChar = getwc(fStream);
	}
	fclose(fStream);
	return 0;
}

