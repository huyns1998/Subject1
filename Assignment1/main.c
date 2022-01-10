#include<stdio.h>
#include"common.h"
#include<stdbool.h>
#include<math.h>
int main()
{	
	char c;	
	do
	{
		giaima_tamgiac();
		printf("Ban co muon tiep tuc?y/n: ");
		getchar();
		scanf("%c", &c);
		printf("-------------------------------------------\n");
	} while (c != 110);
	return 0;
}