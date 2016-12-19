#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
int insertsort(int array[], int n);
int main()
{
	const int MAX = 65536;
	int array[MAX];
	int size;
	for (size = 0; size < MAX; size++)
	{
		printf("input array[%d]",size+1);
		array[size]=GetInt();
		if (array[size] == INT_MAX) break;
	}
	int count = insertsort(array, size);
	printf("the sorted array\n");
	for (int i = 0; i < size; i++)
		printf("%d\n",array[i]);
	printf(" circle of run time : %d\n",count);
	return 0;
}
