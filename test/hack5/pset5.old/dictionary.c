/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"
#define DICTIONARY "dictionaries/large"
typedef struct node
{
	char* word;
	struct node* nextword;
}node;

node* first = NULL;
node* pointer; 

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    node * pointer;
    pointer = first;
    int len = strlen(word);
    int i;
    while (pointer != NULL)
    {
		for (i = 0; i < len+1; i++)
		{
			// compare the next word
			if ((word[i] != pointer->word[i]) && (word[i] != toupper(pointer->word[i])))
			{
				break;
			}
			// terminate at the end
			if (word[i] == (char)NULL)
			{
				return true;
			}
		}
		pointer = pointer->nextword;
	}
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    FILE* file = fopen(dictionary,"r");
    
    // check for dictionary usable
    if (file == NULL)
    {
		printf("cant not open %s",dictionary);
		return false;
	}
	pointer = first;
	

	while (!feof(file))
	{
		// generate the word
		char* tmpword = malloc(sizeof(char)*46);
		if (tmpword == NULL)
		{
			break;
		}
		
		// open file read word
		fgets(tmpword,45,file);
		
		//terminate the \n
		int len = strlen(tmpword);
		tmpword[len-1] = (char)NULL;
		
		// generate the pointer to word
		node* newword = malloc(sizeof(node));
		if (newword == NULL)
		{
			break;
		}
		newword->word = tmpword;
		newword->nextword = NULL;
		
		// the first of wordlist 
		if (pointer == NULL)
		{
			first = newword;
			pointer = first;
		}
		
		// appeal the word to linked words
		else 
		{
			pointer->nextword = newword;
			pointer = newword;
		}
	}
	fclose(file);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(const char* dictionary)
{
    // TODO
    int counter = 0;
    FILE* file = fopen(dictionary,"r");
    if (file == NULL)
    {
		printf("cant open %s",dictionary);
	}
    char* wordholder = malloc(46*sizeof(char));
    while (!feof(file))
    {
		fgets(wordholder,46,file);
		counter++;
	}
	printf("%d",counter);
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
    node* prepointer = NULL;
    pointer = first;
    while (pointer != NULL)
    {
		prepointer = pointer;
		pointer = pointer->nextword;
		free(prepointer->word);
		free(prepointer);
	}
    return true;
}
