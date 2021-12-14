#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAX_SIZE 128
#define MAX_LINE 1024

struct _cvor;
typedef struct _cvor* position;
typedef struct _cvor
{
	int number;
	position left;
	position right;
}cvor;

int menu(position root);
position insert(position current, position q);
position CreateNew(int number, position root);
int printInOrder(position current);
int printPostOrder(position current);
int printPreOrder(position current);
position DeleteElement(int number, position root);
position FindElement(int number, position current);
position FindMin(position current);
int DeleteAll(position current);

int main()
{
	position root = NULL;

	menu(root);

	return 0;
}
int menu(position root){
	int choice, NumOfElements, i, number;

	printf("Odaberite:\n"
		"1-za dodavanje elemenata u stablo\n"
		"2-za brisanje trazenog\n"
		"3-za trazenje elementa\n"
		"4-za IN ORDER ispis\n"
		"5-za POST ORDER ispis\n"
		"6-za PRE ORDER ispis\n"
		"7-za kraj programa\n"
		"\nVas izbor: ");
	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		printf("Unesite koliko zelite elemenata unijeti u binarno stablo: ");
		scanf("%d", &NumOfElements);
		for (i = 0; i < NumOfElements; i++)
		{
			printf("Unesite %d. element: ", i + 1);
			scanf("%d", &number);
			root = CreateNew(number, root);
		}
		menu(root);
		break;
	case 2:
		printf("Unesite koji element zelite izbrisati: ");
		scanf("%d", &number);
		printf("\n");
		root = DeleteElement(number, root);
		menu(root);
		break;
	case 3:
		printf("Unesite element koji zelite pronaci: ");
		scanf("%d", &number);

		FindElement(number, root);
		break;
	case 4:
		printInOrder(root);
		menu(root);
		break;
	case 5:
		printPostOrder(root);
		menu(root);
		break;
	case 6:
		printPreOrder(root);
		menu(root);
		break;
	case 7:
		DeleteAll(root);
		break;
	default:
		menu(root);
		break;
	}
	return 0;
}
position CreateNew(int number, position root)
{
	position new = NULL;

	new = (position)malloc(sizeof(cvor));
	if (!new)
	{
		perror("Failed allocation!\n");
		return NULL;
	}

	new->number = number;
	new->left = NULL;
	new->right = NULL;

	new = insert(root, new);
	return new;
}
position insert(position current, position q)
{
	if (current == NULL)
		return q;

	else if (current->number < q->number)
		current->right = insert(current->right, q);

	else if (current->number > q->number)
		current->left = insert(current->left, q);

	else
		free(q);

	return current;
}

int printInOrder(position current)
{
	if (current == NULL)
	{
		return 0;
	}

	printInOrder(current->left);
	printf("%d ", current->number);
	printInOrder(current->right);

	return 0;
}

int printPostOrder(position current)
{
	if (current == NULL)
	{
		return 0;
	}

	printPostOrder(current->left);
	printPostOrder(current->right);
	printf("%d ", current->number);

	return 0;
}

int printPreOrder(position current)
{
	if (current == NULL)
	{
		return 0;
	}

	printf("%d ", current->number);
	printPreOrder(current->left);
	printPreOrder(current->right);

	return 0;
}


position DeleteElement(int number, position current)
{
	if (NULL == current)
	{
		printf("There is no such element in binary tree!\n");
	}

	else if (number < current->number)
	{
		current->left = DeleteElement(number, current->left);
	}

	else if (number > current->number)
	{
		current->right = DeleteElement(number, current->right);
	}
	else
	{
		if (current->left != NULL && current->right != NULL)
		{
			position temp = FindMin(current->right);

			current->number = temp->number;

			current->right = DeleteElement(current->number, current->right);
		}
		else
		{
			position temp = current;

			if (NULL == current->left)
			{
				current = current->right;
			}
			else
			{
				current = current->left;
			}
			free(temp);
		}

	}
	return current;
}
position FindElement(int number, position current)
{
	if (NULL == current)
	{
		printf("There is no such element in binary tree!\n");
	}
	else
	{
		if (number < current->number)
		{
			return FindElement(number, current->left);
		}
		else if (number > current->number)
		{
			return  FindElement(number, current->right);
		}
		else
			return current;
	}
	return current;
}
position FindMin(position current)
{
	if (NULL == current)
	{
		return NULL;
	}
	else
	{
		if (NULL == current->left)
		{
			return current;
		}
		else 
		{
			return FindMin(current->left);
		}
	}
}
int DeleteAll(position current)
{
	if (current == NULL)
	{
		return 0;
	}
	DeleteAll(current->left);
	DeleteAll(current->right);

	printf("\n Deleting element: %d", current->number);
	free(current);

	return 0;
}