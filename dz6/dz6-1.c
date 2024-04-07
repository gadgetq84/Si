
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

void print_num(int num)
{
	if(num>0)
	{
		print_num(num/10);
		printf("%d ",num%10);	
	}
}
int main(int argc, char **argv)
{
	setlocale( LC_ALL,"Rus" );
	
	int n;
	printf("¬ведите ќдно целое неотрицательное число: ");
	scanf("%d",&n);
	print_num(n);
	return 0;
}

