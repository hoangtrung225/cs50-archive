#include <stdio.h>
#include <cs50.h>
typedef struct node
{
	int idstudent;
	struct node* nextnode;
}node;
node * first;
void insert(void);
void through(void);

int main(void)
{
	int control;
	first = NULL;
	while(control != 4)
	{
		printf("\n1 : insert\n");
		printf("\n2 : delete\n");
		printf("\n3 : search\n");
		printf("\n4 : exit\n");
		control = GetInt();
		if (control == 1)
		{
			insert();
		}
		through();
	}
	return 0;

}
void insert(void)
{
	printf("input your student's id");
	int index = GetInt();
	node* newnode = malloc(sizeof(node));
	newnode->idstudent = index;
	newnode->nextnode = NULL;
	node* pointer = NULL;
	node* prepointer = NULL;
	pointer = first;
	while(true)
	{
	
		// case the first of node
		if (pointer == NULL)
		{
			newnode->nextnode = NULL;
			first = newnode;
			break;
		}
	
		// case end of the nodestring
		else  if (pointer->nextnode == NULL)
		{
			pointer->nextnode = newnode;
			break;
		}
		  
		// case head of the nodestring
		else if (first->idstudent > newnode->idstudent)
		{
			newnode->nextnode = first;
			first = newnode;
			break;
		}
	
		// case middle of the nodestring
		else if (pointer->idstudent > newnode->idstudent)
		{
			prepointer->nextnode = newnode;
			newnode->nextnode = pointer;
		}
		prepointer = pointer; 
		pointer = pointer->nextnode;

	}
}


void through(void)
{
	node* pointer = first;
	while (pointer != NULL)
	{
		printf("%d      ",pointer->idstudent);
		pointer = pointer->nextnode;
	}
}
	
