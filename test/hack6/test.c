#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++)
	{
		printf("argv[%d]		=  		%s\n",i,argv[i]);
	}
	int opt;
	while ((opt = getopt(argc,argv,"n:a:b:c")) != -1)
	{
		switch(opt)
		{
			// n
			case 'n':
				printf("n		= 		%s\noptind		=		%d\n",argv[optind],optind);
				break;
			// -a
			case 'a':
				printf("-a		= 		%s\noptind		= 		%d\n",optarg,optind);
				break;
			// -b
			case 'b':
				printf("-b		= 		%s\noptind		= 		%d\n",optarg,optind);
				break;
		}

	}
	int number = optind;
	printf("c 		= 		%s\noptind		=		%d\n",argv[optind],optind);
	for (int i = 0; i < argc; i++)
	{
		printf("argv[%d]		=  		%s\n",i,argv[i]);
	}

	return 0;
}
