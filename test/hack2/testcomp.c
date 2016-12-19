#include <stdio.h>
#include "trunglib.h"
#include <cs50.h>
int main(void)
{
	printf("please input the string1");
	char* Str1 = GetString(); 
	printf("please in put the secornd");
	char* Str2 = GetString();
	int result = compstr(Str1,Str2);
	if (result == 1)
	{
		printf("those string is the same");
		return 0;
	}
	else if (result == 0)
	{
		printf("those strings are differen");
		return 0;
	}
	else printf("some error occo");
return 0;
}
