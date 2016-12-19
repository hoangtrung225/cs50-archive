#include <stdio.h>
//bubble sort
int swap(int* x, int* y);
int count = 0;
int bubbsort(int array[], int n)
{
	if (n == 1)
	{
		return 0;
	}
	else 
	{
		for (int i = 0; i < n -1; i++)
		{
			count++;
			if (array[i] > array[i+1])
			{
				swap(&array[i],&array[i+1]);
			}
		}
		n = n-1;
		bubbsort(array, n); 
	}
	return count;
}
int swap(int* x, int* y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
	return 0;
}
//sellection sort
int selecsort(int array[],int n)
{
	int k = n;
	int startpoint = 0;
	int subsort(int array[], int n, int startpoint)
	{
		if (n == 1)
			return 0;
		else
		{
			int min = 0;
			for (int i = 1; i < n; i++)
			{
				if (array[i] < array[min])
					min = i;
				count++;
			}
			swap(&array[0],&array[min]);
			k = k - 1;
			startpoint++;
			subsort(&array[n-k],k,startpoint);
		}
	}
	subsort(array,n,startpoint);
	return count ;
}
