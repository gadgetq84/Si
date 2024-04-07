
#include <stdio.h>
#include <locale.h>
#include <math.h>

int sum(int n)
{
	int summa = 0;
    summa = (n*(n + 1))/2;
	return summa ;
}

int main(int argc, char **argv)
{
	setlocale( LC_ALL,"Rus" );
	
	int a;
	printf("¬ведите ÷елое не отрицательное число: ");
	scanf("%d",&a);

		printf("%d \n", sum(a));

	return 0;
}

