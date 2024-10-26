#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct Node{
	int data;
	struct Node* next;
};

struct Node *makeNode(int data)
{
	struct Node *node = calloc(1, sizeof(struct Node));
	node->data = data;
	node->next = NULL;
	return node;
}

void insert(struct Node** head, int data){
	struct Node* node = makeNode(data);
	if((*head) == NULL){
		(*head) = node;
	}else{
		struct Node* current = *head;
		struct Node* maxNode = *head;
		while(current->next!=NULL){
			if(maxNode->data < current->data){
				maxNode = current;
			}
			current = current->next;
		}
		current = maxNode->next;
		maxNode->next = node;
		node->next = current;
	}
}

void delete(struct Node **head)
{
	if ((*head) == NULL)
	{
		return;
	}
	else
	{
		struct Node *current = *head;
		struct Node *maxNode = *head;
		struct Node *prev = NULL;
		struct Node *maxprev = NULL;
		while (current->next != NULL)
		{
			if (maxNode->data < current->data)
			{
				maxNode = current;
				maxprev = prev;
			}
			prev = current;
			current = current->next;
		}
		current = maxNode->next;
		maxNode = NULL;
		maxprev->next = current;
	}
}

void print(struct Node **head){
	int length = 1;
	struct Node* current = *head;
	while(current->next!=NULL){
		length++;
		current = current->next;
	}
	printf("Print linked list: \n");
	current = *head;
	for(int i=0;i<length/2;i++){
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
	for (int i = length / 2; i < length; i++)
	{
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
}

int main()
{
	struct Node* node = NULL;
	struct Node** head = &node;

	//Make list
	srand(time(NULL));
	int A[50];
	for (int i = 0; i < 50; i++)
	{
		int dup = 0;
		int randn;
		do
		{
			dup = 0;
			randn = rand() % 1000;
			for (int j = 0; j < i; j++)
			{
				if (A[j] == randn)
				{
					dup = 1;
					break;
				}
			}
			if (!dup)
				A[i] = randn;
		} while (dup);
	}
	for(int i=0;i<50;i++){
		insert(head, A[i]);
	}


	// 2)
	delete(head);
	// 3)
	print(head);

	// 2)
	delete (head);
	// 3)
	print(head);

	// 2)
	delete (head);
	// 3)
	print(head);

	// 2)
	delete (head);
	// 3)
	print(head);

	return 0;
}