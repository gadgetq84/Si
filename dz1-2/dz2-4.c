#include <stdio.h>
#include <locale.h>

int main(int argc, char **argv)
{
	setlocale( LC_ALL,"Rus" );
	
	unsigned int dig, count, temp;
	float sum, average;
	printf("������� ����� ��� �������������� ����� ������������� �����: ");
	scanf("%u",&dig);
	
	count=0;
	sum=0;
	temp = dig;
	while(temp>1)
	{
		temp = dig/10;
		sum+=(dig-temp*10);
		dig = temp;
		count++;
	}
	average = sum/count;
	printf(" %.2f\n",average);
	return 0;
}

