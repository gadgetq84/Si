
#include <stdio.h>
#include <locale.h>
#include <math.h>

int main(int argc, char **argv)
{
	setlocale( LC_ALL,"Rus" );
	
	int a,b,sum;
	printf("������� ��� ����� ����� a � b(a <= b) �� ������ �� ������ 100 : ");
	scanf("%d%d",&a,&b);
	a= abs(a);
	b = abs(b);
	sum =0;
    if(a<=b )
	{
		for(;a<=b;a++)
		{
			sum +=a*a; 
		}
		printf("sum = %d\n",sum);
	}else
    {
	   printf("a>b\n");
	}
return 0;
}
