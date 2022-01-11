#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 1024
struct _person;
typedef struct _person *position;

typedef struct _person
{
	char name[50];
	char surname[50];
	int birthYear;
	position next;
}person;

position createPerson(char* name, char* surname, int birthYear);
int prependList(char *name, char* surname, int birthYear, position head);
int insertAfter(position last, position newPerson);
int appendList(char*name, char*surname, int birthYear, position head);
int printList(position first);
position findLast(position first);
position findPerson(position first, char*surname);
int delete(position first, char*surname);
position findBefore(position first,char *surname);
int addAfter(char *name, char * surname, int birthYear, char* lastname, position first);
int addBefore(char *name, char * surname, int birthYear, char* lastname, position first);
int sortedInput(position p, position newPerson);
int readFromFile(char* file, position first);
int addToFile(char *file, position head);

int main()
{
	person head = { .name = {0},.surname = {0},.birthYear = 0,.next = NULL };
	position p = &head;
	position newPerson = NULL;
	int i = 0, n = 0;
	int izbor1 = 0, izbor2 = 0;

	char name[MAX] = { 0 };
	char surname[MAX] = { 0 };
	int birthYear = 0;
	char file[MAX] = { 0 };
	char temp[MAX] = { 0 };

	printf("Odaberite:\n"
		"1-unos liste iz datoteke\n"
		"2-samostalan unos vezane liste\n");

		scanf("%d", &izbor1);

		if (izbor1 == 1)
		{
			printf("Unesite ime datoteke:");
			scanf(" %s", file);
			readFromFile(file, p);
			printList(p->next);
		}

		if (izbor1 == 2)
		{
			printf("Unesite koliko osoba zelite unijeti: ");
			scanf("%d", &n);
			for (i = 0; i < n; i++)
			{
				printf("Unesite ime, prezime i godinu rodenja: ");
				scanf(" %s %s %d", name, surname, &birthYear);
				newPerson = createPerson(name, surname, birthYear);
				sortedInput(p, newPerson);
			}
			printf("\n");
			printList(p->next);
			printf("\n");
			printf("Odaberite:\n"
				"1-za dodavanje elementa na pocetak liste \n"
				"2-za dodavanje elementa na kraj liste\n"
				"3-za dodavanje nakon odredenog elementa\n"
				"4-za dodavanje prije odredenog elemnta\n"
				"5-za brisanje elementa iz liste\n"
				"6-za unos liste u datoteku\n"
				"Vas izbor: ");
			scanf("%d", &izbor2);
			printf("\n");
			switch (izbor2)
			{
			case 1:
				printf("Unesite osobu:");
				scanf(" %s %s %d", name, surname, &birthYear);
				prependList(name, surname, birthYear, p);
				printList(p->next);
				break;
			case 2:
				printf("Unesite osobu:");
				scanf(" %s %s %d", name, surname, &birthYear);
				appendList(name, surname, birthYear, p);
				printList(p->next);
				break;
			case 3:
				printf("Unesite novu osobu:");
				scanf(" %s %s %d", name, surname, &birthYear);
				printf("Unesite prezime osobe nakon koje zelite dodati novu osobu: ");
				scanf(" %s", temp);
				addAfterElement(name, surname, birthYear, temp, p->next);
				printList(p->next);
				break;
			case 4:
				printf("Unesite novu osobu:");
				scanf(" %s %s %d", name, surname, &birthYear);
				printf("Unesite prezime osobe prije koje zelite dodati novu osobu: ");
				scanf(" %s", temp);
				addBeforeElement(name, surname, birthYear, temp, p->next);
				printList(p->next);
				break;
			case 5:
				printf("Unesite prezime osobe koju zelite izbrisati iz liste: ");
				scanf(" %s", surname);
				delete(p->next, surname);
				printList(p->next);
				break;
			case 6:
				printf("Unesite ime datoteke: ");
				scanf(" %s", file);
				add_to_file(file, p);
				break;
			default:
				printf("Uneseni broj ne pase niti jednom ponudenom!\n");
			}
		}
		if (izbor1 != 1 && izbor1 != 2)
		{
			printf("Unijeli ste krivu vrijenost!");
			return 1;
		}
			
		


	
	
	return 0;
}

int prependList(char* name, char *surname, int birthYear, position head)
{
	position newPerson = NULL;
	newPerson = createPerson(name, surname, birthYear);
	if (!newPerson)
	{
		return -1;
	}
	
	insertAfter(head, newPerson);

	return 0;
}

position createPerson(char *name, char *surname, int birthYear)
{
	position newPerson = NULL;

	newPerson = (position)malloc(sizeof(person));
	if (!newPerson)
	{
		perror("Can't allocate memory.\n");
		return NULL;
	}
	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	return newPerson;
}

int insertAfter(position last, position newPerson)
{
	newPerson->next = last->next;
	last->next = newPerson;

	return 0;
}

int appendList(char*name, char* surname, int birthYear, position head)
{
	position newPerson = NULL;
	position last = NULL;

	newPerson = createPerson(name, surname, birthYear);

	if (!newPerson)
	{
		return -1;
	}

	last = findLast(head);
	insertAfter(last, newPerson);

	return 0;

}

int printList(position first)
{
	position temp = first;
	while (temp)
	{
		printf("Name: %s, surname: %s, birth year: %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}
	return 0;
}

position findPerson (position first,char *surname)
{
	position temp = first;

	while (temp)
	{
		if (strcmp(temp->surname, surname) == 0)
			return 0;
		temp = temp->next;
	
	}
	return NULL;
}

position findLast(position first)
{
	position temp = first;

	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	return temp;
}

int delete(position first, char*surname)
{
	position del = first;
	position before = findBefore(first, surname);

	if (!before)
	{
		perror("No surname.\n");
			return -1;
	}

	del = before->next;
	before->next = del->next;
	free(del);

	return 0;

}

position findBefore(position first, char *surname)
{
	position before = first;
	while (before)
	{
		if (strcmp(before->next->surname, surname) == 0)
			return before;
		before = before->next;

	}

	return 0;
}


int addAfter(char*name, char*surname, int birthYear, char *lastname, position first)
{
	position newPerson = NULL;
	position element = NULL;

	newPerson = createPerson(name, surname, birthYear);
	if (!newPerson)
	{
		return -1;
	}

	element = findPerson(first, lastname);

	insertAfter(element, newPerson);

	return 0;
}

int addBefore(char*name, char *surname, int birthYear, char *lastname, position first)
{
	position newPerson = NULL;
	position element = NULL;

	newPerson = createPerson(name, surname, birthYear);

	if (!newPerson)
	{
		return -1;
	}

	element = findBefore(first, lastname);

	insertAfter(element, newPerson);

	return 0;
}


int addToFile(char *file, position head)
{
	position temp = head;
	FILE *pfile = NULL;

	pfile = fopen(file, "w");
	if (!pfile)
	{
		perror("File can't open.\n");
		return -1;
	}

	while (temp->next != NULL)
	{
		fprintf(pfile, " %s %s %d\n", temp->next->name, temp->next->surname, temp->next->birthYear);
		temp = temp->next;
	}

	fclose(pfile);
	
	return 0;
}

int sortedInput(position p, position newPerson)
{
	while (p->next != NULL && strcmp(p->next->surname, newPerson->surname) < 0)
	{
		p = p->next;
	}

	insertAfter(p, newPerson);

	return 0;
}


int readFromFile(char *file, position head)
{
	position temp = head;
	FILE *pfile = NULL;
	char buffer[MAX] = { 0 };

	pfile = fopen(file, "r");

	if (!pfile)
	{
		perror("File can't open.\n");
		return -1;
	}

	while (!feof(pfile))
	{
		position newPerson = NULL;
		newPerson = (position)malloc(sizeof(person));
		if (!newPerson)
		{
			perror("Can't allocate memory.\n");
			return -1;
		}

		fgets(buffer, MAX, pfile);
		if (sscanf(buffer, " %s %s %d", newPerson->name, newPerson->surname, &newPerson->birthYear) == 3)
		{
			insertAfter(temp, newPerson);
			temp = temp->next;
		}

	}

	fclose(pfile);

	return 0;
}
