
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
unsigned long long degree(int n)
{
	unsigned long long result = pow(2, n-1);
	return result;
}

int main(int argc, char **argv)
{
	setlocale( LC_ALL,"Rus" );
	
	short n;
	printf("¬ведите ÷елое число от 1 до 64: ");
	scanf("%hi",&n);
		printf(" %llu\n", degree(n));
	
	
	return 0;
}

