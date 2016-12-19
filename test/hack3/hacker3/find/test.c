#include <stdio.h>
#include <cs50.h>
#include "helpers.h"

int main(void)
{
	printf("iput value to searching for");
	int input = GetInt();
	printf("input the lengh of the array\n");
	int len = GetInt();
	int array[len];
	for (int i = 0; i < len; i++)
	{
		printf("input[%d]\n",i);
		array[i] = GetInt();
	}
	if (search(input,array,len))
	{
		printf("found");
	}
	else
		printf("not found");
}	
	
