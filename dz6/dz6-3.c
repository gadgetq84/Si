
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

void to_bin(int num1)
{
	int remainder;
	int count=0;
	    while (num1!=0) 
    {
        remainder = num1%2; 
        num1 = num1/2; 
        printf("%d",remainder);
        if(remainder==1)
        {
			count++;
		}
    }
    printf("\n%d",count);
	

}
int main(int argc, char **argv)
{
	setlocale( LC_ALL,"Rus" );
	
	int a;
	printf("Введите Натуральное число: ");
	scanf("%d",&a);
	to_bin(a);
	return 0;
}

