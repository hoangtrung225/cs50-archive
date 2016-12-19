/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdint.h>
#include "bmp.h"


int main(void)
{
	// ensure proper use
    
	
	char* infile = "card.raw";
	
	// open file
	FILE* input = fopen(infile,"r");
	if (input ==NULL)
	{
		printf("can not open the file %s",infile);
		return 2;
	}
	
	// read from file
	BYTE array[512];
	int one = '0';
	int ten = '0';
	int hund = '0';
	FILE* fileout = fopen("/dev/null","w");

	while (!feof(input))
	{
		fread(array,sizeof(BYTE),512,input);
		
		if ((array[0] == 0xff) && (array[1] == 0xd8) && (array[2] == 0xff) && ((array[3] == 0xe0) || (array[3] == 0xe1)))
		{
			// write name the fileout
			char name[] ={(char) hund,(char) ten,(char) one, '.','j','p','g',(char) NULL};
			
			fclose(fileout);
			fileout = fopen(name,"w");
			one= one+1;
			if ((int)one > (int)'9')
			{
				ten = ten + 1;
				one = '0';
			}
			if ((int)ten > (int) '9')
			{
				hund = hund +1;
			}
		}
		fwrite(array,sizeof(BYTE),512,fileout);
	}
	fclose(input);
	fclose(fileout);
	return 0;
}		
			
