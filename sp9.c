#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 128
#define MAX_LINE 128
#define upper 90
#define lower 10

struct _cvor;
typedef struct _cvor * stablo;
typedef struct _cvor {
	int number;
	stablo left;
	stablo right;
}cvor;

struct _stog;
typedef struct _stog *position;
typedef struct _stog {
	int el;
	position next;
}stog;

stablo insert(stablo current, stablo new);
stablo createNew(int number, stablo current);
int printInOrder(stablo current);
int replace(stablo current);
int DeleteAll(stablo current);
int PopStog(position head);
int PushStog(position head, int element);
int addToFile(position head, stablo root, char*name);
int addToStog(position head, stablo current);

int main()
{
	stablo root = NULL;
	srand((unsigned)time(NULL));
	int i = 0, n;
	stog head;
	head.el = 0;
	head.next = NULL;
	char name[MAX_SIZE] = { 0 };

	printf("Enter file name : ");
	scanf(" %s", name);

	int niz[10] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };

	for (i = 0; i < 10; i++)
	{
		root = createNew(niz[i], root);
	}

	printInOrder(root);
	printf("\n");

	addToStog(&head, root);
	addToFile(&head, root, name);

	replace(root);

	printInOrder(root);
	printf("\n");

	addToStog(&head, root);
	addToFile(&head, root, name);

	DeleteAll(root);

	root = NULL;
	printf("\nEnter the number of nodes: ");
	scanf(" %d", &n);

	for (i = 0; i < n; i++)
	{
		root = createNew((rand() % (upper - lower - 1) + lower + 1), root);
	}

	printInOrder(root);

	return 0;
}
stablo insert(stablo current, stablo new)
{
	if (NULL == current)
	{
		return new;
	}
	else if (new->number < current->number)
	{
		current->right = insert(current->right, new);
	}
	else 
	{
		current->left = insert(current->left, new);
	}

	return current;
}

stablo createNew(int number, stablo current)
{
	stablo new = NULL;

	new = (stablo)malloc(sizeof(cvor));
	if (!new)
	{
		perror("Failed allocation!");
		return NULL;
	}

	new->number = number;
	new->left = NULL;
	new->right = NULL;

	new = insert(current, new);

	return new;
}
int printInOrder(stablo current)
{
	if (!current)
	{
		return 0;
	}

	printInOrder(current->left);
	printf("%d ", current->number);
	printInOrder(current->right);

	return 0;
}
int replace(stablo current)
{
	int sum = 0;
	int temp = 0;

	if (NULL != current)
	{
		sum = replace(current->left);
		sum += replace(current->right);

		temp = current->number;
		current->number = sum;
		sum += temp;
	}
	return sum;

}
int DeleteAll(stablo current)
{
	if (current == NULL)
	{
		return 0;
	}

	DeleteAll(current->left);
	DeleteAll(current->right);
	

	free(current);

	return 0;
}
int PopStog(position head)
{
	if (!head->next)
	{
		return 0;
	}

	position toDelete = head->next;
	head->next = toDelete->next;
	free(toDelete);

	return 0;
}
int PushStog(position head, int element)
{
	position new = NULL;
	new = (position)malloc(sizeof(stog));
	if (!new)
	{
		perror("Failed allocation!\n");
		return -1;
	}

	new->el = element;
	new->next = head->next;
	head->next = new;

	return 0;
}
int addToStog(position head, stablo current)
{
	if (NULL == current)
	{
		return 0;
	}

	addToStog(head, current->right);

	PushStog(head, current->number);

	addToStog(head, current->left);


	return 0;
}
int addToFile(position head, stablo root, char*name)
{
	FILE* pfile = NULL;

	pfile = fopen(name, "a");
	if (!pfile)
	{
		perror("Failed opening of the file!\n");
		return -1;
	}

	while (head->next)
	{
		fprintf(pfile, "%d ", head->next->el);
		PopStog(head);
	}

	fprintf(pfile, "\n");

	fclose(pfile);

	return 0;
}


