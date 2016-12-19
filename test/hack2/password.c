#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>

	int compstr(char string1[30], char string2[30])
	{
		int len1 = strlen(string1), len2 = strlen(string2), result;
		if (len1 != len2) {return 0;}
		for (int i = 0; i < len1; i++)
		{
			if (string1[i] != string2[i])
			{
				result = 0;
				break;
			
			}
			else   result = 1;
		}
		return result;
		
	
	}
	int regestr(int len,int str[],char* strin)
	{
		str[len] = (int)NULL;
		for (int i = 0; i < len; i++)
		{
			strin[i] = str[i];
		}
		return 0;
	}

int main(int argc, char *argv[])
{
	if (argc > 2)
	{
		printf("warn* argument may contain space or special character");
	}
	//get the salt
	char salt[] = {argv[1][0], argv[1][1], (int) NULL};
	
	//brutal attack
	int prostr[10] ;
	char* stringin = malloc(15 * sizeof(char));
	char* stringout = malloc(25 * sizeof(char));
	int done = 0;

		
			//one character
			for(prostr[0] = 32; (prostr[0] < 127) && (done == 0); prostr[0]++)
			{
				regestr(1,prostr,stringin);
				stringout = crypt(stringin,salt);
				int result = compstr(stringout,argv[1]);
				printf("%s\n",stringin);
				if (result == 1)
				{
					printf("we fucking got it%s\n",stringin);
					done = 1;
				}
			}
			//two character
			for(prostr[0] = 32; (prostr[0] < 127) && (done == 0); prostr[0]++)
			{
				for(prostr[1] = 32; (prostr[1] < 127) && (done == 0); prostr[1]++)
				{
					regestr(2,prostr,stringin);
					stringout = crypt(stringin,salt);
					int result = compstr(stringout,argv[1]);
					printf("%s \n",stringin);
					if (result == 1)
					{
						printf("we fucking got it%s\n",stringin);
						done = 1;
					}
					
				}
				
			}
			//three character
			for(prostr[0] = 32; (prostr[0] < 127) && (done == 0); prostr[0]++)
			{
				for(prostr[1] = 32; (prostr[1] < 127) && (done == 0); prostr[1]++)
				{
					for(prostr[2] = 32; (prostr[2] < 127) && (done == 0); prostr[2]++)
						{
							regestr(3,prostr,stringin);
							stringout = crypt(stringin,salt);
							int result = compstr(stringout,argv[1]);
							printf("%s \n",stringin);
							if (result == 1)
							{
							printf("%s we fucking got it\n",stringin);
							done = 1;

							}
						}
				}	
			}
			//four character
			for(prostr[0] = 32; (prostr[0] < 127) && (done == 0); prostr[0]++)
			{
				for(prostr[1] = 32; (prostr[1] < 127) && (done == 0); prostr[1]++)
				{
					for(prostr[2] = 32; (prostr[2] < 127) && (done == 0); prostr[2]++)
						{
							for(prostr[3] = 32; (prostr[3] < 127) && (done == 0); prostr[3]++)
							{	regestr(4,prostr,stringin);
								stringout = crypt(stringin,salt);
								int result = compstr(stringout,argv[1]);
								printf("%s \n",stringin);
								if (result == 1)
								{
								printf("%s we fucking got it\n",stringin);
								done = 1;
								}

							}
						}
				}	
			}
}
	
