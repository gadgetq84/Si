
#include <stdio.h>
#include <locale.h>
#include <math.h>

int main(int argc, char **argv)
{
	setlocale( LC_ALL,"Rus" );
	
	int dig, temp, number, inverted;
	printf("¬ведите любое целое положительное число: ");
	scanf("%u",&dig);
	temp = dig;
	inverted =0;
	while(temp>0)
	{
		temp = dig/10;
		number=(dig-temp*10);
		dig = temp;
		inverted=inverted*10+number; 
	}
		printf(" %d \n", inverted);
	
	return 0;
}

