
#include <stdio.h>
#include <locale.h>

int main(int argc, char **argv)
{
	setlocale( LC_ALL,"Rus" );
	
	int a;
	printf("¬ведите целое число от 1 до 12 - номер мес€ца : ");
	scanf("%d",&a);
    if((0<a && a<3) || a==12 )
	{
		printf("winter\n");
	}
    if(2<a && a<6)
    {
	   printf("spring\n");
	}
	if(5<a && a<9)
    {
	   printf("summer\n");
	}
	if(8<a && a<12)
    {
	   printf("autumn\n");
	}
return 0;
}
