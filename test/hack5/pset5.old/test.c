#include <stdio.h>

int main(void)
{
char counter = 0;
for (int i = 0; i < 255; i++)
{
printf("%d    	%c\n",(int)i,(char)i);
}
return 0;
}
