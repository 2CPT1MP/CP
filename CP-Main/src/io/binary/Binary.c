#include <stdio.h>
#include "Binary.h"
#include "Struct.h"
#include <io.h>
#include <fcntl.h>

int SaveData(struct Node* head)
{
	FILE* fileStream = fopen(DATABASE_FILE, "wb");
	if (!fileStream)
		return -1;

	_setmode(_fileno(fileStream), _O_U16TEXT);

	for (const struct Node* i = first; i != 0; i = i->next)
		fwrite(&i->flight, sizeof(struct Flight), 1, fileStream);
	fclose(fileStream);
	return 0;
}

int ReadData()
{
	FILE* fileStream = fopen(DATABASE_FILE, "rb");
	if (!fileStream)
		return -1;
	_setmode(_fileno(fileStream), _O_U16TEXT);
	struct Flight flight = {0};

	while (fread(&flight, sizeof(flight), 1, fileStream) > 0)
		AddFlight(&flight);
	fclose(fileStream);
	return 0;
}