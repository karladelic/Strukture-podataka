#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 128
#define MAX_LINE 1024

typedef struct _student {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	double bodovi;
}student;

int ProcitajBrojRedakaDatoteke(char * nazivDatoteke) {
	int brojac = 0;
	FILE * datoteka = NULL;
	char buffer[MAX_LINE] = { 0 };

	datoteka = fopen(nazivDatoteke, "r");
	if (!datoteka) {
		printf("Greska!");
		return -1;
	}
	
	while (!feof(datoteka))
	{
		fgets(buffer, MAX_LINE, datoteka);
		brojac++;
	}
	fclose(datoteka);

	return brojac;
}

student* AlocirajMemorijuIProcitajStudente(int brojStudenata, char *nazivDatoteke)
{
	int brojac = 0;
	FILE *datoteka = NULL;
	student * popis = NULL;

	popis = (student*)malloc(brojStudenata * sizeof(student));
	datoteka = fopen(nazivDatoteke, "r");

	if (!datoteka)
	{
		printf("Greska!");
		free(popis);
		return NULL;
	}

	while (!feof(datoteka))
	{
		fscanf(datoteka, " %s %s %lf", popis[brojac].ime, popis[brojac].prezime, &popis[brojac].bodovi);
		brojac++;
	}

	fclose(datoteka);

	return popis;
}

int ispis(char *nazivDatoteke)
{
	int i = 0;
	int brojStudenata = 0;
	student* stud = NULL;

	brojStudenata = ProcitajBrojRedakaDatoteke(nazivDatoteke);
	stud = AlocirajMemorijuIProcitajStudente(brojStudenata, nazivDatoteke);

	double max = stud[0].bodovi;
	for (i = 0; i < brojStudenata; i++)
	{
		if (stud[i].bodovi > max)
			max = stud[i].bodovi;
	}
	for (i = 0; i < brojStudenata; i++) {
		printf("Ime: %s\tPrezime: %s\tApsolutni bodovi: %lf\tRelativni bodovi: %lf\n", stud[i].ime, stud[i].prezime, stud[i].bodovi, (stud[i].bodovi / max) * 100);
	}

	return 0;
}

int main()
{
	int n = 0;
	n = ispis("popis.txt");
	return 0;
}

