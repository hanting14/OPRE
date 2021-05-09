#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void menu()
{
	FILE* file;
	file = fopen("./vaccine_data", "r");
	int input = 0;
	Line* data = (Line*)malloc(sizeof(Line)*0);
	int size = 0;
	if (data == NULL)
		printf("Nem sikerült a memória lefoglalás");
	else
	{
		if (file != NULL)
			readFile(&data, &size, &file);
		do 
		{
			printf("Menu opciók:\n");
			printf("1, Adatok kiírása\n");
			printf("2, Adat felvétel\n");
			printf("3, Adat módosítása\n");
			printf("4, Adat törlése\n");
			printf("5, Teljes lista készítése\n");
			printf("6, Kilépés\n");
			scanf("%d", &input);
			system("clear");
			if (input == 1)
				getData(data, size);
			else if (input == 2)
				addData(&data, &size);
			else if (input == 3)
				modifyData(&data, &size);
			else if (input == 4)
				deleteData(&data, &size);
			else if (input == 5)
				createList(&data, &size);
		}while (input != 6);
		file = fopen("./vaccine_data", "w");
		writeFile(&data, &size, &file);
	}
	fclose(file);
	free(data);
}

void readFile(Line** data, int* size, FILE** file)
{
	if (*file != NULL) 
	{
		fscanf(*file, "%d\n", size);
		if (*size > 0)
		{
			*data = (Line*)realloc(*data, ((*size)+1)*(sizeof(Line)));
			if (*data == NULL)
				printf("Nem sikerült a memória lefoglalás\n");
			else
			{
				for (int i = 0; i<(*size); ++i)
				{
					fscanf(*file, "%s %s %s %s %s\n",
				 (*data)[i].surName, (*data)[i].firstName, (*data)[i].birthYear, (*data)[i].phoneNumber, (*data)[i].rich);
				}
			}
		}
	}
}

void writeFile(Line** data, int* size, FILE** file)
{
	fprintf(*file, "%d\n", *size);
	for (int i = 0; i<(*size); ++i)
	{
		fprintf(*file, "%s %s %s %s %s\n",
	 (*data)[i].surName, (*data)[i].firstName, (*data)[i].birthYear, (*data)[i].phoneNumber, (*data)[i].rich);
	}
}

void getData(Line* data, int size)
{
	printf("\n");
	for (int i = 0; i<size; ++i)
	{
		printf("%d, Név: %s %s, Szül. év: %s, Telefonszám: %s, Fizet?: %s\n",
		i+1, data[i].surName, data[i].firstName, data[i].birthYear, data[i].phoneNumber, data[i].rich);
	}
	printf("\n");
}

void addData(Line** data, int* size)
{
	*data = (Line*)realloc(*data, ((*size)+1)*(sizeof(Line)));
	if (*data == NULL)
		printf("Nem sikerült a memória lefoglalás\n");
	else
	{
		(*size)++;
		printf("Adja meg a vezetéknevét:\n");
		printf("(max 20 karakter lehet)\n");
		scanf("%s", (*data)[(*size)-1].surName);
		printf("Adja meg a keresztnevét:\n");
		printf("(max 20 karakter lehet)\n");
		scanf("%s", (*data)[(*size)-1].firstName);
		printf("Adja meg a születési évét:\n");
		printf("(max 4 karakter lehet)\n");
		scanf("%s", (*data)[(*size)-1].birthYear);
		printf("Adja meg a telefonszámát:\n");
		printf("(max 11 karakter lehet)\n");
		scanf("%s", (*data)[(*size)-1].phoneNumber);
		printf("Adja meg hogy hajlandó-e fizetni is:\n");
		printf("(igen/nem)\n");
		scanf("%s", (*data)[(*size)-1].rich);
		system("clear");
	}	
}

void modifyData(Line** data, int* size)
{
	if (*size == 0)
		printf("Nem tud mit módosítani, mert nincs semmi adat elmentve.\n");
	else
	{
		getData(*data, *size);
		printf("Hányadik sort szeretné módosítani?\n");
		int k = -1;
		scanf("%d", &k);
		if (k == -1)
			printf("Nem sikerült beolvasni az adott számot");
		else
		{
			printf("Adja meg az új vezetéknevét:\n");
			printf("(max 20 karakter lehet)\n");
			scanf("%s", (*data)[k-1].surName);
			printf("Adja meg az új keresztnevét:\n");
			printf("(max 20 karakter lehet)\n");
			scanf("%s", (*data)[k-1].firstName);
			printf("Adja meg az új születési évét:\n");
			printf("(max 4 karakter lehet)\n");
			scanf("%s", (*data)[k-1].birthYear);
			printf("Adja meg az új telefonszámát:\n");
			printf("(max 11 karakter lehet)\n");
			scanf("%s", (*data)[k-1].phoneNumber);
			printf("Adja meg hogy hajlandó-e fizetni is:\n");
			printf("(igen/nem)\n");
			scanf("%s", (*data)[k-1].rich);
			system("clear");
		}
	}
}

void deleteData(Line** data, int* size)
{
	if (*size == 0)
		printf("Nem tud mit törölni, mert nincs semmi adat elmentve.\n");
	else
	{
		getData(*data, *size);
		printf("Hányadik sort szeretné törölni?\n");
		int k = -1;
		scanf("%d", &k);
		if (k == -1)
			printf("Nem sikerült beolvasni az adott számot");
		else
		{
			for (int i = k-1; i<(*size)-1; ++i)
			{
				(*data)[i] = (*data)[i+1];
			}
			*data = (Line*)realloc(*data, ((*size)-1)*(sizeof(Line)));
			if (*data == NULL && *size > 1)
				printf("Nem sikerült a memória lefoglalás\n");
			else
			{
				(*size)--;
				system("clear");
			}
		}
	}
}

void createList(Line** data, int* size)
{
	int s = -1;
	do
	{
		printf("Milyen hosszú listát szeretne készíteni?\n");
		scanf("%d", &s);
		if (s < 0)
			printf("Adjon meg egy nullánál nagyobb számot.\n");
	}while(s < 0);
	if (s > 0)
	{
		*size = s;
		*data = (Line*)realloc(*data, ((*size))*(sizeof(Line)));
		if (*data == NULL)
			printf("Nem sikerült a memória lefoglalás\n");
		else
		{
			for (int i = 0; i<(*size); ++i)
			{
				printf("Adja meg a %d. vezetéknevét:\n", i+1);
				printf("(max 20 karakter lehet)\n");
				scanf("%s", (*data)[i].surName);
				printf("Adja meg a %d. keresztnevét:\n", i+1);
				printf("(max 20 karakter lehet)\n");
				scanf("%s", (*data)[i].firstName);
				printf("Adja meg a %d. születési évét:\n", i+1);
				printf("(max 4 karakter lehet)\n");
				scanf("%s", (*data)[i].birthYear);
				printf("Adja meg a %d. telefonszámát:\n", i+1);
				printf("(max 11 karakter lehet)\n");
				scanf("%s", (*data)[i].phoneNumber);
				printf("Adja meg hogy hajlandó-e fizetni is (%d. sor):\n", i+1);
				printf("(igen/nem)\n");
				scanf("%s", (*data)[i].rich);
			}
		}
	}
}