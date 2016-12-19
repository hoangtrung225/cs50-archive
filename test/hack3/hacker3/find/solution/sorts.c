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
// insetion sort
int insertsort(int array[], int n)
{
	int tmp[n];
	void subsort(int key, int arrayin[], int size)
	{
		if(key <= arrayin[0])
			{
				for (int i = size; i > 0; i--)
					arrayin[i] = arrayin[i-1];
				arrayin[0] = key;
			}
		else if(key >= arrayin[size -1])  
			arrayin[size] = key;
		else
		{
			for (int point = 0; point < size; point++)
			{
				if ((key > arrayin[point]) && (key < arrayin[point+1]))
				{
					for (int i = size; i > point+1; i--)
						arrayin[i]=arrayin[i-1];
					arrayin[point+1] = key;
				}
		
			}
		}
		count++;
	 }
	if (array[0] < array[1])
	{
		tmp[0] = array[0];
		tmp[1] = array[1];
	}
	else
	{ 
		tmp[0] = array[1];
		tmp[1] = array[0];
	}
	for (int i = 2; i < n; i++)
	subsort(array[i], tmp, i);
	for (int i = 0; i < n; i++)
	array[i] = tmp[i]; 
	return count;
}
