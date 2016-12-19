/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dictionary.h"

typedef struct node
{
	bool check;
	struct node* charray[28];
}
node;

int killnode(node* nodeptr);

node* root=NULL;
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    int len = strlen(word);
    node* nodeptr = root;
    int strptr = 0;
    int tmp;
    while(true)
    {
		tmp = word[strptr];
		
		if (word[strptr] == '\'')
		{
			nodeptr = nodeptr->charray[26];
			strptr++;
		}
		else if ('a' <= tmp && tmp <= 'z')
		{
			tmp = word[strptr] - 'a';
			nodeptr = nodeptr->charray[tmp];
			strptr++;
		}
		else if ('A' <= tmp && tmp <= 'Z')
		{
			tmp = word[strptr] - 'A';
			nodeptr = nodeptr->charray[tmp];
			strptr++;
		}
		else if(word[strptr] == '\0')
		{
			nodeptr = nodeptr->charray[27];
			strptr++;
		}
		if (nodeptr == NULL)
		{
			return false;
		}
		else if (strptr == len+1 && (nodeptr->check == false) && word[strptr-1] == '\0')
		{
			return true;
		}
	}
	
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    // try to open dictionary
    FILE* file = fopen(dictionary,"r");
    if (file == NULL)
    {
		printf("can not open file %s",dictionary);
		return false;
	}
	// init pointer, variable
	root = malloc(sizeof(node));
	char* wordholder = malloc(46*sizeof(char));
	int tmp, strptr;
	node* nodeptr = NULL;
	root->check = true;
	for (int i = 0; i < 28; i++)
	{
		root->charray[i] = NULL;
	}
	while(!feof(file))
	{
		// get the word 
		fgets(wordholder,46,file);
		if (wordholder == NULL)
		{
			break;
		}
		strptr = 0;
		nodeptr = root;
		// get character
		while (wordholder[strptr] != '\0')
		{
			if (wordholder[strptr] == '\n')
			{
				if(nodeptr->charray[27] == NULL)
				{
					nodeptr->charray[27] = malloc(sizeof(node));
					nodeptr = nodeptr->charray[27];
					nodeptr->check = false;
					for (int i = 0; i < 28; i++)
					{
						nodeptr->charray[i] = NULL;
					}
					break;
				}
				else 
				{
					printf("something happen");
				}
				strptr++;
			}
			else if (wordholder[strptr] == '\'')
			{
				if (nodeptr->charray[26] == NULL)
				{
					nodeptr->charray[26] = malloc(sizeof(node));
					nodeptr = nodeptr->charray[26];
					for (int i = 0; i < 28; i++)
					{
						nodeptr->charray[i] = NULL;
					}
				}	
				else
				{
					nodeptr = nodeptr->charray[26];
				}
				nodeptr->check = true;
				strptr++;
			}
			else if (wordholder[strptr] <= 'z' && wordholder[strptr] >= 'a') 
			{
				tmp =(int) wordholder[strptr] - 'a';
				if (nodeptr->charray[tmp] == NULL)
				{
					nodeptr->charray[tmp] = malloc(sizeof(node));
					nodeptr = nodeptr->charray[tmp];
					for (int i = 0; i < 27; i++)
					{
						nodeptr->charray[i] = NULL;
					}
				}
				else 
				{
					nodeptr=nodeptr->charray[tmp];
				}
				nodeptr->check = true;
				strptr++;
			}
			else 
			{
				printf("something wrong");
				break;
			}
		}
	}
	free(wordholder);			
    fclose(file);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(char* dictionary)
{
    // TODO
    char* wordholder = malloc(sizeof(char)*46);
    int counter = 0;
    FILE* file = fopen(dictionary,"r");
    while(!feof(file))
    {
		fgets(wordholder,46,file);
		counter++;
	}
	free(wordholder);
	fclose(file);
    return counter;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */

bool unload(void)
{
    // TODO
    
	killnode(root);

    return true;
}

int killnode(node* nodeptr)
{
	node* pointer = NULL;
	node* subpointer = NULL;
	pointer = nodeptr;
	for (int i = 0; i < 28; i++)
	{
		subpointer = pointer->charray[i];
		if (subpointer != NULL)
		{
			killnode(subpointer);
		}
	}
	
	free(pointer);
	return 0;
}
