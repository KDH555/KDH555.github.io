#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	char name[10];
	struct Node * link;
} Node;

int add(Node ** head, char * str)
{
	Node * node = (Node*)malloc(sizeof(Node));
	strcpy(node->name, str);

	if (*head == NULL)
	{
		*head = node;
		node->link = NULL;
	}
	else
	{
		Node * current = *head;
		while (current->link != NULL)
		{
			current = current->link;
		}
		current->link = node;
		node->link = NULL;
	}
	return 0;
}

void print(Node * head)
{
	Node * current = head;
	while (current != NULL)
	{
		printf("%s, ", current->name);
		current = current->link;
	}
	printf("\n");
	return;
}

void clear(Node ** head)
{
	Node * current = *head;
	while (current != NULL)
	{
		Node * link = current->link;
		free(current);
		current = link;
	}
	*head = NULL;
}

int insert(Node ** head, int index, char * str)
{
	Node * node = (Node*)malloc(sizeof(Node));
	strcpy(node->name, str);

	if (*head == NULL)
	{
		*head = node;
		node->link = NULL;
	}
	else if (index == 0)
	{
		node->link = (*head)->link;
		*head = node;
	}
	else
	{
		Node * current = *head;
		Node * prev = NULL;
		for (int i=0; i<index; i++)
		{
			if (current == NULL)
			{
				free(node);
				return -1;
			}
			prev = current;
			current = current->link;
		}
		node->link = prev->link;
		prev->link = node;
	}
	return 0;
}

int delete(Node ** head, int index)
{
	if (*head == NULL)
	{
		return -1;
	}
	else if (index == 0)
	{
		Node * node = *head;
		*head = node->link;
		free(node);
	}
	else
	{
		Node * current = *head;
		Node * prev = NULL;
		for (int i=0; i<index; i++);
		{
			if(current == NULL)
			{
				return -1;
			}
			prev = current;
			current = current->link;
		}
		prev->link = current->link;
		free(current);
	}
	return 0;
}

int main()
{
	Node * head = NULL;

    add(&head, "Mon"); //NULL이 있는 공간을 수정하기 위한 주소를 보내줌(&)
	add(&head, "Fri");
	add(&head, "Sun");
	print(head); //출력만을 위해 &를 쓰지않음

	insert(&head, 1, "Thu");
	print(head);

    delete(&head, 2);
	print(head);

    clear(&head);
	print(head);

	return 0;
}
