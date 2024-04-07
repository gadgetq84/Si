
#include <stdio.h>
#include <locale.h>
#include <math.h>

int nod(int a,int b)
{
		while(a!=0 && b!=0)
	{
		if(a>b)
		{
			a=a%b;
		}else
		{
			b= b%a;
		}
	
	}
	return a+b;
}

int main(int argc, char **argv)
{
	setlocale( LC_ALL,"Rus" );
	
	int a,b;
	printf("¬ведите ƒва целых положительных числа: ");
	scanf("%d%d",&a,&b);
		printf(" %d\n", nod(a,b));
	return 0;
}

