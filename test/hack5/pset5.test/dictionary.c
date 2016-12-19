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
#include "dictionary.h"
#include <string.h>
char* array[WORDS];

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
	for (int i = 0; i < WORDS; i++)
	{
		if (strcmp(word,array[i]) ==0)
		{
			return true;
			break;

		}
	} 
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */

bool load(const char* dictionary)
{
    // TODO
    FILE* diction = fopen(dictionary,"r");
    if (diction == NULL)
    {
		printf("cant not open file %s",dictionary);
		return false;
	}
	int counter = 0;
	while (!feof(diction))
	{
		array[counter] = malloc(sizeof(char)*(LENGTH+1));
		fgets(array[counter], LENGTH+1, diction);
		int n = strlen(array[counter]);
		array[counter][n-1] = (char) NULL;
		counter = counter + 1;
	}
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}
