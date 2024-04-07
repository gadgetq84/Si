
#include <stdio.h>
#include <locale.h>
#include <math.h>

int main(int argc, char **argv)
{
	setlocale( LC_ALL,"Rus" );
	int a, dig_count;
	printf("Ввести целое трехзначное число");
	scanf("%d",&a);
	dig_count =0;
	while (a>1)
	{
		a=a/10;
		dig_count++;
	}
	if(dig_count==2)
	{
		printf("YES\n");
	}else
	{
		printf("NO\n");
	}
return 0;
}
