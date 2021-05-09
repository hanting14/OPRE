#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <errno.h> 
#include <string.h> 
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <signal.h>
#include "functions.h"

#define HARCRA_FEL SIGUSR1
#define INDULAS SIGUSR2

void menu()
{
	srand(time(NULL));
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
		system("clear");
		do 
		{
			printf("Menu opciók:\n");
			printf("1, Adatok kiírása\n");
			printf("2, Adat felvétel\n");
			printf("3, Adat módosítása\n");
			printf("4, Adat törlése\n");
			printf("5, Teljes lista készítése\n");
			printf("6, Nap lefuttatása\n");
			printf("7, Kilépés\n");
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
			else if (input == 6)
      {
        if (runDay(&data, &size) == 1)
          return;
      }
			else if (input == 14)
        resetVacc(&data, &size);
				
		}while (input != 7);
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
					fscanf(*file, "%s %s %s %s %s %s\n",
				 (*data)[i].surName, (*data)[i].firstName, (*data)[i].birthYear, (*data)[i].phoneNumber, (*data)[i].rich, (*data)[i].vaccinated);
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
		fprintf(*file, "%s %s %s %s %s %s\n",
	 (*data)[i].surName, (*data)[i].firstName, (*data)[i].birthYear, (*data)[i].phoneNumber, (*data)[i].rich, (*data)[i].vaccinated);
	}
}

void getData(Line* data, int size)
{
	printf("\n");
	for (int i = 0; i<size; ++i)
	{
		printf("%d, Név: %s %s, Szül. év: %s, Telefonszám: %s, Fizet?: %s, Oltott?: %s\n",
		i+1, data[i].surName, data[i].firstName, data[i].birthYear, data[i].phoneNumber, data[i].rich, data[i].vaccinated);
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
		strcpy((*data)[(*size)-1].vaccinated, "nem");
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
				strcpy((*data)[i].vaccinated, "nem");
			}
			system("clear");
		}
	}
}


int* create_pipe()
{
    int* pipe1 = (int*)malloc(2*sizeof(int));
    if(pipe(pipe1) == -1){
        printf("Hiba a csovezetek letrehozaskor\n");
        exit(EXIT_FAILURE);
    }
    return pipe1;
}

void write_pipe(int descriptor[2], Line message[5]){
    close(descriptor[0]);
    write(descriptor[1], message, sizeof(Line)*5);
    close(descriptor[1]);
}

void read_pipe(int descriptor[2], Line buffer[5]){
    close(descriptor[1]);
    read(descriptor[0], buffer, sizeof(Line)*5);
    close(descriptor[0]);
}

void delete_pipe(int descriptor[2]){
    free(descriptor);
    descriptor = NULL;
}

void handler(int sign)
{
    printf("HARCRA FEL\n");
}

void handler2(int sign)
{
    //printf("INDULAS\n");
}

int runDay(Line** data, int* size)
{
  int* bus1to = create_pipe();
  int* bus2to = create_pipe();
  int* bus1from = create_pipe();
  int* bus2from = create_pipe();
  //printf("%d", countVac(*data, *size));
	if (countVac(*data, *size) >= 10)
	{
		struct sigaction act;

		memset(&act, 0, sizeof(act));
		act.sa_handler = handler;

		sigaction(HARCRA_FEL,  &act, 0);
		//signal(HARCRA_FEL, handler);
		pid_t bus1Child = fork();
		if (bus1Child == 0)
		{
			signal(INDULAS, handler2);
			//pause();
    		//sleep(1);
			kill(getppid(), HARCRA_FEL);
			//sleep(1);
			pause();
			//gyerek
			//printf("%d %d\n", getpid(), getppid());
			Line* bus1 = (Line*)malloc(sizeof(Line)*5);
			read_pipe(bus1to, bus1);
			pause();
			printf("\nAdott embereket várjuk az első buszhoz:\n");
			getData(bus1, 5);

			for(int i = 0; i<5; ++i)
			{
				int r = rand() % 100;
				if (r <= 90)
					strcpy(bus1[i].vaccinated, "OLTVA");
			}

			write_pipe(bus1from, bus1);

			return 1;
		}
		else if (bus1Child == -1)
		{
			printf("Could not fork\n");
            exit(EXIT_FAILURE);
		}
		else
		{
			pause();
			pid_t bus2Child = fork();
			if (bus2Child == 0)
			{
				//kill(bus1Child, INDULAS);
				//pause();
				//sleep(1);
				kill(getppid(), HARCRA_FEL);
				signal(INDULAS, handler2);
				//sleep(2);
				//gyerek
				//printf("%d %d\n", getpid(), getppid());
				Line* bus2 = (Line*)malloc(sizeof(Line)*5);
				read_pipe(bus2to, bus2);
				printf("\nAdott embereket várjuk a második buszhoz:\n");
				getData(bus2, 5);
				kill(bus1Child, INDULAS);
				for(int i = 0; i<5; ++i)
				{
					int r = rand() % 100;
					if (r <= 90)
						strcpy(bus2[i].vaccinated, "OLTVA");
				}

				write_pipe(bus2from, bus2);

				return 1;
			}
			else if (bus2Child == -1)
			{
				printf("Could not fork\n");
				exit(EXIT_FAILURE);
			}
			else
			{
				//pause();
				pause();
				Line* bus1 = (Line*)malloc(sizeof(Line)*5);
				Line* bus2 = (Line*)malloc(sizeof(Line)*5);
				get2Busses(data, size, &bus1, &bus2);
				//printf("%d %d %d\n", getpid(), bus1Child, bus2Child);
				printf("\nAdott telefonszámokra küld SMS-t:\n");
				for (int i = 0; i<5; ++i)
					printf("Telefonszám: %s\n", bus1[i].phoneNumber);
				for (int i = 0; i<5; ++i)
					printf("Telefonszám: %s\n", bus2[i].phoneNumber);
				kill(bus1Child, INDULAS);
				kill(bus2Child, INDULAS);

				write_pipe(bus1to, bus1);
				write_pipe(bus2to, bus2);

				read_pipe(bus1from, bus1);
				read_pipe(bus2from, bus2);

				int j = 0;
				for (int i = 0; i<(*size) && j<5; ++i)
				{
					if (strcmp(bus1[j].phoneNumber, (*data)[i].phoneNumber) == 0 && strcmp("OLTVA", bus1[j].vaccinated) == 0)
					{
						(*data)[i] = bus1[j];
						++j;
					}
				}
				j = 0;
				for (int i = 0; i<(*size) && j<5; ++i)
				{
					if (strcmp(bus2[j].phoneNumber, (*data)[i].phoneNumber) == 0 && strcmp("OLTVA", bus2[j].vaccinated) == 0)
					{
						(*data)[i] = bus2[j];
						++j;
					}
				}

				//sleep(3);
				
				free(bus1);
				free(bus2);
				
				printf("Vége a napnak!\n\n");
				return 0;
			}
		}
	}
	else if (countVac(*data, *size) > 4)
	{
		pid_t bus1Child = fork();
		if (bus1Child == 0)
		{
    		//sleep(2);
			kill(getppid(), HARCRA_FEL);
			signal(INDULAS, handler2);
			pause();
			//gyerek
			//printf("%d %d\n", getpid(), getppid());
			Line* bus1 = (Line*)malloc(sizeof(Line)*5);
			read_pipe(bus1to, bus1);
			printf("\nAdott embereket várjuk az első buszhoz:\n");
			getData(bus1, 5);

			for(int i = 0; i<5; ++i)
			{
				int r = rand() % 100;
				if (r < 90)
					strcpy(bus1[i].vaccinated, "OLTVA");
			}

			write_pipe(bus1from, bus1);

			return 1;
		}
		else 
		{
			signal(HARCRA_FEL, handler);
			pause();
			Line* bus1 = (Line*)malloc(sizeof(Line)*5);
			getBus(data, size, &bus1);
			//printf("%d %d %d\n", getpid(), bus1Child, bus2Child);
			printf("\nAdott telefonszámokra küld SMS-t:\n");
			for (int i = 0; i<5; ++i)
				printf("Telefonszám: %s\n", bus1[i].phoneNumber);
			kill(bus1Child, INDULAS);

			write_pipe(bus1to, bus1);

			read_pipe(bus1from, bus1);

			int j = 0;
			for (int i = 0; i<(*size) && j<5; ++i)
			{
				if (strcmp(bus1[j].phoneNumber, (*data)[i].phoneNumber) == 0 && strcmp("OLTVA", bus1[j].vaccinated) == 0)
				{
					(*data)[i] = bus1[j];
					++j;
				}
			}

			//sleep(3);
			
			free(bus1);
			
			printf("Vége a napnak!\n\n");
			return 0;
		}
	}
	else
	{
		printf("Nem indul egy busz sem, mert nincs elég ember.\n");
	}
}

int countVac(Line* data, int size)
{
	int c = 0;
	for (int i = 0; i<size; ++i)
	{
		if (strcmp("nem", data[i].vaccinated) == 0)
			c++;
	}
	return c;
}

void resetVacc(Line** data, int* size)
{
	for (int i = 0; i<*size; ++i)
		strcpy((*data)[i].vaccinated, "nem");
}

void get2Busses(Line** data, int* size, Line** bus1, Line** bus2)
{
  int pass = 0;
  int i;
  for (i = 0; i<*size && pass < 5; ++i)
  {
    if (strcmp("nem", (*data)[i].vaccinated) == 0)
    {
      (*bus1)[pass] = (*data)[i];
      ++pass;
    }
  }
  for (pass = 0; i<*size && pass < 5; ++i)
  {
    if (strcmp("nem", (*data)[i].vaccinated) == 0)
    {
      (*bus2)[pass] = (*data)[i];
      ++pass;
    }
  }
}

void getBus(Line** data, int* size, Line** bus1)
{
  int pass = 0;
  int i;
  for (i = 0; i<*size && pass < 5; ++i)
  {
    if (strcmp("nem", (*data)[i].vaccinated) == 0)
    {
      (*bus1)[pass] = (*data)[i];
      ++pass;
    }
  }
}