#include <stdio.h>
#include <cs50.h>
int subsrc(int key, int array[], int min, int max);
int tmp;
bool search(int value, int array[], int n)
{
	return subsrc(value, array, 0, n-1);
}
int subsrc(int key, int array[], int min, int max)

{
	int pointer = (min + max)/2;
	if ((key == array[pointer]) || (key == array[min]) || (key == array[max]))
		tmp = 1;
	else if (min > max)
		tmp = 0;

	else if (key < array[pointer])
	{
		max = pointer - 1;
		min = min +1;
		subsrc(key,&array[min],min,max);
	}
	else if (key > array[pointer])
	{
		max = max -1;
		min = pointer +1;
		subsrc(key,&array[min],min,max);
	}
	return tmp;
}
