
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

void print_num(int num1,int delta)
{
	printf("%d ",num1);
	if(delta<0)
	{
		print_num(num1+1,delta+1);
	}
		if(delta>0)
	{
		print_num(num1-1,delta-1);
	}
}
int main(int argc, char **argv)
{
	setlocale( LC_ALL,"Rus" );
	
	int a,b;
	printf("¬ведите ƒва целых числа через пробел: ");
	scanf("%d%d",&a,&b);
	print_num(a,a-b);
	return 0;
}

