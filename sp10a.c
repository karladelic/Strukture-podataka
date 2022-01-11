#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_SIZE 128
#define MAX_LINE 1024

struct _stablo;
typedef struct _stablo* position;
typedef struct _stablo
{
	char name[MAX_SIZE];
	int populacija;
	position left;
	position right;
}stablo;

struct _cvor;
typedef struct _cvor* pozicija;
typedef struct _cvor
{
	char ime[MAX_SIZE];
	position root;
	pozicija next;
}cvor;

int readFile(char* name, pozicija head);
int insertSorted(pozicija new, pozicija head);
int insertAfter(pozicija before, pozicija new);
int printList(pozicija first);
position readFileForTree(char* name, position root);
position insertToTree(position new, position current);
position createNewTreeElement(char* name, int number);
int printTree(position current);
position findCities(position current, int number);
int findCountry(pozicija head, char* country, int number);

int main()
{
	cvor head = { .ime = { 0 },.root = NULL,.next = NULL };
	pozicija p = &head;
	char ime[MAX_SIZE] = { 0 };
	int number;
	readFile("Drzave.txt", p);

	printf("Unesite drzavu i broj stanovnika: \nDrzava: ");
	scanf(" %s", ime);
	printf("Broj stanovnika: ");
	scanf("%d", &number);

	findCountry(p, ime, number);

	return 0;
}
int findCountry(pozicija head, char* country, int number)
{
	pozicija temp = head->next;

	while (temp != NULL && strcmp(country, temp->ime) != 0)
		temp = temp->next;

	if (temp)
	{
		printf("Gradovi u %s koji imaju vecu populaciju od %d: \n", country, number);
		temp->root = findCities(temp->root, number);
	}

	else
		printf("Nema drzave u datoteci!\n");

	return 0;
}
position findCities(position current, int number)
{
	if (current == NULL)
	{
		return NULL;
	}

	else if (current->populacija < number)
	{
		current->right = findCities(current->right, number);
	}
	else if (current->populacija >= number)
	{
		current->left = findCities(current->left, number);
		printf("Ime:%s  Populacija: %d\n", current->name, current->populacija);
		current->right = findCities(current->right, number);
	}

	return current;
}
int readFile(char* name, pozicija head)
{
	char buffer[MAX_LINE] = { 0 };
	char ime[MAX_LINE] = { 0 };
	FILE* pfile = NULL;

	pfile = fopen(name, "r");
	if (!pfile)
	{
		printf("Greska pri otvaranju datoteke!\n");
		return -1;
	}

	while (!feof(pfile))
	{
		pozicija new = NULL;
		new = (pozicija)malloc(sizeof(cvor));
		if (!new)
		{
			perror("Greska u alokaciji!\n");
			return -1;
		}

		fgets(buffer, MAX_SIZE, pfile);

		if (sscanf(buffer, " %s %s", new->ime, ime) == 2)
		{
			new->root = NULL;
			new->root = readFileForTree(ime, new->root);
			insertSorted(new, head);
		}
	}
	fclose(pfile);
	return 0;
}

position readFileForTree(char* name, position root)
{
	char buffer[MAX_LINE] = { 0 };
	FILE* pfile = NULL;
	pfile = fopen(name, "r");
	if (!pfile)
	{
		printf("Greska pri otvaranju datoteke!\n");
		return -1;
	}

	while (!feof(pfile))
	{
		int number;
		char country[MAX_SIZE] = { 0 };
		position new = NULL;

		fgets(buffer, MAX_SIZE, pfile);
		if (sscanf(buffer, " %s %d", country, &number) == 2)
		{
			new = createNewTreeElement(country, number);
			root = insertToTree(new, root);
		}
	}
	fclose(pfile);
	return root;
}
int insertSorted(pozicija new, pozicija head)
{
	pozicija temp = head;
	while (temp->next != NULL && strcmp(temp->next->ime, new->ime) < 0)
		temp = temp->next;

	insertAfter(temp, new);

	return 0;
}
int insertAfter(pozicija before, pozicija new)
{
	new->next = before->next;
	before->next = new;

	return 0;
}
int printList(pozicija first)
{
	while (first)
	{
		printf("\nIme:%s\nGradovi:\n", first->ime);
		if (first->root)
			printTree(first->root);

		else
			printf("Nema gradova u stablu!\n");

		first = first->next;
	}
	return 0;
}
position insertToTree(position new, position current)
{
	if (current == NULL)
	{
		return new;
	}
	else if (current->populacija > new->populacija)
	{
		current->left = insertToTree(new, current->left);
	}
	else if (current->populacija < new->populacija)
	{
		current->right = insertToTree(new, current->right);
	}
	else
	{
		if (strcmp(current->name, new->name) > 0)
		{
			current->left = insertToTree(new, current->left);
		}

		else if (strcmp(current->name, new->name) < 0)
		{
			current->right = insertToTree(new, current->right);
		}
		else 
			free(new);
	}
	return current;
}
position createNewTreeElement(char* name, int number)
{
	position new = NULL;

	new = (position)malloc(sizeof(stablo));
	if (!new)
	{
		perror("Greska pri alokaciji!\n");
		return NULL;
	}

	strcpy(new->name, name);
	new->populacija = number;
	new->left = NULL;
	new->right = NULL;

	return new;
}
int printTree(position current)
{
	if (NULL == current)
		return 0;

	printTree(current->left);
	printf("%s %d\n", current->name, current->populacija);
	printTree(current->right);

	return 0;
}