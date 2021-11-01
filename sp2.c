#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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

int main()
{
	person head = { .name = {0},.surname = {0},.birthYear = 0,.next = NULL };
	position p = &head;
	position temp = NULL;
	char firstName[50] = "First_name";
	char firstSurname[50] = "First_surname";
	int firstBirthYear = 1980;
	char secondName[50] = "Second_name";
	char secondSurname[50] = "Second_surname";
	int secondBirthYear = 1990;

	prependList(firstName, firstSurname, firstBirthYear, p);
	appendList(secondName, secondSurname, secondBirthYear, p);
	printList(p->next);
	printf("\n");

	temp = findPerson(p->next, secondSurname);
	printList(temp);
	printf("\n");

	delete(p->next, secondSurname);
	printList(p->next);

	
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
