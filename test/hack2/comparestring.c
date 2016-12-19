#include <stdio.h>
#include <string.h>
#include <cs50.h>
int compstr(char string1[30], char string2[30])
	{
		int len1 = strlen(string1), len2 = strlen(string2);
		if (len1 != len2) {return 0;}
		for (int i = 0; i < len1; i++)
		{
			if (string1[i] != string2[i])
			{
				return 0;
				break;
			
			}
			else   return 1;
		}
	
	}
