
#include <stdio.h>
#include <locale.h>
#include <math.h>

int main(int argc, char **argv)
{
	setlocale( LC_ALL,"Rus" );
	
	unsigned int dig, even, temp, number, count;
	printf("¬ведите любое целое положительное число: ");
	scanf("%u",&dig);
	temp = dig;
	even=0;
	count=0;
	while(temp>0)
	{
		temp = dig/10;
		number=(dig-temp*10);
		dig = temp;
		if (number%2==0)
			even++;
		count++;
	}
	if(count == even)
	{
		printf(" YES\n");
	}else
	{
		printf(" NO\n");
	}
	
	return 0;
}

