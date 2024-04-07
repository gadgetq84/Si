
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

void noteven(void)
{
	int num;
	scanf("%d",&num);
	if(num%2!=0)
	printf("%d ",num);
	
	if (num!=0)
		noteven();
	else
		return;
}
int main(int argc, char **argv)
{
	setlocale( LC_ALL,"Rus" );
	printf("Введите Последовательность ненулевых целых чисел. В конце число 0: ");
	noteven();
	return 0;
}

