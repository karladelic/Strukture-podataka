#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


#define MAX_LINE 1024
#define MAX_SIZE 128

struct _element;
typedef struct _element* position;
typedef struct _element
{
	int coef;
	int exp;
	position next;
}element;

int EnterFileName(char *fileName);
int ReadFile(position head1, position head2, char fileName);
int FindPairs(char *buffer, position head);
position CreateNewElement(int exp, int coef, position head);
int SortedInput(position head, position newElement);
int Merge(position after, position newElement);
int InsertAfter(position after, position newElement);
int Add(position head1, position head2, position head3);
int Multiply(position head1, position head2, position head4);
int PrintPoly(position first);
int DeleteAfter(position el);
int FreeMemory(position head);

int main()
{
	element head1 = { .coef = 0,.exp = 0,.next = NULL };
	element head2 = { .coef = 0,.exp = 0,.next = NULL };
	element head3 = { .coef = 0,.exp = 0,.next = NULL };
	element head4 = { .coef = 0,.exp = 0,.next = NULL };
	char file[MAX_SIZE] = { 0 };

	EnterFileName(file);

	ReadFile(file, &head1, &head2);
	Add(&head1, &head2, &head3);
	Multiply(&head1, &head2, &head4);

	printf("Suma:\n");
	PrintPoly(head3.next);

	printf("\n");

	printf("Umnozak:\n");
	PrintPoly(head4.next);

	FreeMemory(&head1);
	FreeMemory(&head2);
	FreeMemory(&head3);
	FreeMemory(&head4);

	return 0;
}

int EnterFileName(char* fileName)
{
	printf("Enter name of file: \n"),
		scanf(" %s", fileName);
	
	return 0;

}

int ReadFile(position head1, position head2, char fileName)
{
	FILE *pdat = NULL;
	char buffer[MAX_LINE] = { 0 };
	int status = 0;

	if (!pdat)
	{
		perror("Greska pri otvaranju datoteke!\n");
		return -1;
	}

	fgets(buffer, MAX_LINE, pdat);

	status = FindPairs(buffer, head1);
	if (status != 0)
	{
		return -1;
	}

	fgets(buffer, MAX_LINE, pdat);

	status = FindPairs(buffer, head2);
	if (status != 0)
	{
		return -1;
	}

	fclose(pdat);

	return 0;
}

int FindPairs(char *buffer, position head)
{
	int status = 0, exp = 0, coef = 0, n = 0;
	position newElement = NULL;
	char * currentBuffer = buffer;

	while (strlen(currentBuffer) > 0)
	{
		status = sscanf(currentBuffer, " %d %d %n", &coef, &exp, &n);
		if (status != 2)
		{
			return -1;
		}

		newElement = CreateNewElement(exp, coef, head);
		if (!newElement)
		{
			return -1;
		}

		currentBuffer += n;
	}
	return 0;
}

position CreateNewElement(int exp, int coef, position head) {
	
	position newElement = NULL;
	newElement = (position)malloc(sizeof(element));

	if (!newElement)
	{
		perror("Neuspjesna alokacija memorije!\n");
		return NULL;
	}

	newElement->exp = exp;
	newElement->coef = coef;

	SortedInput(head, newElement);

	return newElement;
}

int SortedInput(position head, position newElement)
{
	position temp = head;
	
	while (temp->next != NULL && temp->next->exp > newElement->exp)
	{
		temp = temp->next;
	}

	Merge(temp, newElement);

	return 0;
}


int Merge(position after, position newElement)
{
	if (after->next == NULL || after->next->exp != newElement->exp)
	{
		InsertAfter(after, newElement);
	}
	else
	{
		int coef = after->next->coef + newElement->coef;
		if (coef == 0)
		{
			DeleteAfter(after);
		}
		else
		{
			after->next->coef = coef;
		}
		free(newElement);
	}
	return 0;
}

int InsertAfter(position after, position newElement)
{
	newElement->next = after->next;
	after->next = newElement;

	return 0;
}

int DeleteAfter(position el) 
{
	position toDelete = el->next;
	el->next = toDelete->next;
	free(toDelete);

	return 0;
}

int Add(position head1, position head2, position head3)
{
	position first = head1->next;
	position second = head2->next;
	position result = head3;
	position temp = NULL;
	position new = NULL;

	while (first != NULL && second != NULL)
	{
		if (first->exp == second->exp)
		{
			new = CreateNewElement(first->exp, first->coef + second->coef, result);
			if (!new)
			{
				return -1;
			}

			first = first->next;
			second = second->next;
		}
		else if (first->exp > second->exp)
		{
			new = CreateNewElement(second->exp, second->coef, result);

			second = second->next;
		}
		else
		{
			new = CreateNewElement(first->exp, first->coef, result);

			first = first->next;
		}
	}

	if (first == NULL)
	{
		temp = second;
	}

	if (second == NULL)
	{
		temp = first;
	}

	while (temp != NULL)
	{
		CreateNewElement(temp->exp, temp->coef, result);
		temp = temp->next;
	}

	return 0;
}

int Multiply(position head1, position head2, position head4)
{
	position first = NULL;
	position second = NULL;
	position result = head4;

	for (first = head1->next; first != NULL; first = first->next)
	{
		for (second = head2->next; second != NULL; second = second->next)
		{
			position newElement = CreateNewElement(first->exp + second->exp, first->coef * second->coef, result);
			if (!newElement)
			{
				return -1;
			}
		}
	}
	return 0;
	
}

int PrintPoly(position first)
{
	position temp = first;
	
	printf("f(x)= ");
	
	while (temp != NULL)
	{
		if (temp->next == NULL)
		{
			printf("%dx^(%d)", temp->coef, temp->exp);
		}
		else
		{
			printf("%dx^(%d)", temp->coef, temp->exp);
			printf("+");
		}
		temp = temp->next;
	}
	return 0;
}

int FreeMemory(position head)
{
	position temp = NULL;

	while (head->next != NULL)
	{
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	return 0;
}