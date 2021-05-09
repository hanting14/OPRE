typedef struct Lines
{
	char surName[20];
	char firstName[20];
	char birthYear[5];
	char phoneNumber[12];
	char rich[5];
	char vaccinated[10];
}Line;

void menu();
void getData(Line* data, int size);
void addData(Line** data, int* size);
void modifyData(Line** data, int* size);
void deleteData(Line** data, int* size);
void createList(Line** data, int* size);
void readFile(Line** data, int* size, FILE** file);
void writeFile(Line** data, int* size, FILE** file);
int runDay(Line** data, int* size);
int countVac(Line* data, int size);
void resetVacc(Line** data, int* size);
void handler(int sign);
void getBus(Line** data, int* size, Line** bus);
void get2Busses(Line** data, int* size, Line** bus1, Line** bus2);