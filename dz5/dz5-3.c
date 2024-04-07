
#include <stdio.h>
#include <locale.h>
#include <math.h>

int is_happy_number(int n)
{
	int suma = 0;
    int mult = 1;
    int digit;
    while (n>0)
    {
		digit = n % 10;
		suma = suma + digit;
		mult = mult * digit;
		n = n/10;
	}
	if (suma == mult)
	return 1;
	else
	return 0;
}

int main(int argc, char **argv)
{
	setlocale( LC_ALL,"Rus" );
	
	int a;
	printf("¬ведите ÷елое не отрицательное число: ");
	scanf("%d",&a);
	if (is_happy_number(a))
		printf("YES\n");
		else
		printf("NO\n");
	return 0;
}

