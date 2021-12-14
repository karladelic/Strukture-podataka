#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 128
#define MAX_LINE 1024

struct cvorStabla;
typedef struct cvorStabla* Stablo;
typedef struct cvorStabla
{
	char name[MAX_SIZE];
	Stablo sibling;
	Stablo child;
}cvor;

struct _stog;
typedef struct _stog* Position;
typedef struct _stog
{
	Stablo direktorij;
	Position next;
}stog;

Stablo CreateDirectory(char* name, Stablo current);
Stablo InsertDirectory(Stablo current, Stablo new);
int Push(Position head, Stablo direktorij);
int Pop(Position head);
Position FindLast(Position head);
Position FindBefore(Position head);
Stablo ChangeDirectory(Position head, Stablo current, char* name);
int DisplayInformation(Stablo current);
int PrintCurrentDirectories(Position head);
int Menu(Stablo current, Position head);

int main()
{
	cvor root;
	stog head;

	strcpy(root.name, "C:");
	root.child = NULL;
	root.sibling = NULL;

	head.direktorij = NULL;
	head.next = NULL;

	Push(&head, &root);
	Menu(&root, &head);

	return 0;

}

Stablo CreateDirectory(char* name, Stablo current)
{
	Stablo new = NULL;
	new = (Stablo)malloc(sizeof(cvor));
	if (!new)
	{
		perror("Failed allocation!\n");
		return NULL;
	}

	strcpy(new->name, name);
	new->child = NULL;
	new->sibling = NULL;

	current->child = InsertDirectory(current->child, new);

	return current;
}
Stablo InsertDirectory(Stablo current, Stablo new)
{
	if (current == NULL)
		return new;

	else if (strcmp(current->name, new->name) > 0)
	{
		new->sibling = current;
		return new;
	}
	else if (strcmp(current->name, new->name) < 0)
	{
		current->sibling = InsertDirectory(current->sibling, new);
	}
	else
	{
		printf("There is already direcotry with same name!\n");
		free(new);
	}
	return current;
}
int Push(Position head, Stablo direktorij)
{
	Position new = NULL;
	new = (Position)malloc(sizeof(stog));
	if (!new)
	{
		perror("Failed allocation of memmory!\n");
		return -1;
	}
	Position last = FindLast(head);

	new->next = last->next;
	last->next = new;
	new->direktorij = direktorij;

	return 0;
}
Position FindLast(Position head)
{
	Position temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}

	return temp;
}
Position FindBefore(Position head)
{
	Position temp = head;
	while (temp->next->next != NULL)
	{
		temp = temp->next;
	}

	return temp;
}

int Pop(Position head)
{
	if (!head->next)
		return 0;

	Position before = FindBefore(head);
	Position toDelete = NULL;

	toDelete = before->next;
	before->next = toDelete->next;
	free(toDelete);

	return 0;
}

Stablo ChangeDirectory(Position head, Stablo current, char* name)
{
	if (NULL == current->child)
	{
		printf("The system cannot find the path specified.\n");
		return current;
	}
	else
	{
		Stablo temp = current->child;
		while (temp != NULL && strcmp(temp->name, name) != 0)
			temp = temp->sibling;

		if (temp == NULL)
		{
			printf("The system cannot find the path specified.\n");
			return current;
		}
		else
		{
			Push(head, current->child);
			return current->child;
		}
	}
}

int DisplayInformation(Stablo current)
{
	if (NULL == current->child)
	{
		printf("Directory is empty.\n");
	}
	else
	{
		Stablo temp = current->child;
		while (temp != NULL)
		{
			printf("<DIR>\t\t %s\n", temp->name);
			temp = temp->sibling;
		}
	}

	return 0;
}
int Exit(Stablo current)
{

	if (current == NULL)
	{
		return 0;
	}

	Exit(current->sibling);
	Exit(current->child);
	Exit(current->sibling);

	free(current);

	return 0;
}
int PrintCurrentDirectories(Position head)
{
	Position temp = head->next;
	char line[MAX_LINE] = { 0 };

	while (temp != NULL)
	{
		strcat(line, temp->direktorij->name);
		strcat(line, "/");
		temp = temp->next;
	}
	strcat(line, ">");

	printf("%s ", line);

	return 0;
}
int Menu(Stablo current, Position head)
{
	Stablo first = current;
	char name[MAX_LINE] = { 0 };
	char command[MAX_LINE] = { 0 };
	char line[MAX_LINE] = { 0 };
	PrintCurrentDirectories(head);

	while (1)
	{
		fgets(line, MAX_LINE, stdin);
		sscanf(line, "%s %s", command, name);

		if (!strcmp(command, "md"))
		{
			current = CreateDirectory(name, current);
			PrintCurrentDirectories(head);
		}
		else if (!strcmp(command, "cd"))
		{
			current = ChangeDirectory(head, current, name);
			PrintCurrentDirectories(head);
		}
		else if (!strcmp(command, "cd.."))
		{
			Pop(head);
			PrintCurrentDirectories(head);
		}
		else if (!strcmp(command, "dir"))
		{
			DisplayInformation(current);
			PrintCurrentDirectories(head);
		}
		else if (!strcmp(command, "exit"))
		{
			break;
		}
		else
		{
			printf("'%s' is not recognized as an internal or external command, operable program or batch file.\n", command);
			PrintCurrentDirectories(head);
		}
	}
	return 0;
}