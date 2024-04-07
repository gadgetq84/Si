
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>


int recurs_power(int n, int p)
{
        if (n == 1 || n == 0) 
        return n;
        if (p > 1) 
        return n * recurs_power(n, --p);
        if (p < 1) 
        return 1;
	return n;
}
int main(int argc, char **argv)
{
	int n,m;
	setlocale( LC_ALL,"Rus" );
	printf("ƒва целых числа -100 >= n >= 100 и 0 >= p >= 100 '.' : ");
	scanf("%d%d",&n,&m);
	
	printf("%d",recurs_power(n,m));
	return 0;
}

