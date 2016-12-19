/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include "helpers.h"
/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int array[], int n)
{
	int min = 0, max = n-1;
	int tmp = 0;
	int pointer = (min + max)/2;
	while (array[min] < array[max])
	{
		if (value == array[pointer] || value ==array[min] || value == array[max])
		{
			tmp = 1;
			break;
		}
		else if (value > array[pointer])
		{
			min = pointer + 1;
			max = max -1;
			pointer =(min + max)/2;
		}
		else if (value < array[pointer])
		{
			max = pointer - 1;
			min = min +1;
			pointer = (min + max)/2;
		}
	}
		
	return tmp;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n) sorting algorithm
    int protoray[65536];
    for (int i = 0; i < 65536; i++)
    {
		protoray[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		++protoray[values[i]];
	}
	int counter = 0;
	for (int i = 0; i < 65536; i++)
	{
		for ( ;protoray[i] > 0; protoray[i]--) 
		{
			values[counter] = i;
			counter++;
		}
	}
}

