#include <stdio.h>
#include <locale.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

int main(int argc, char **argv)
{
	setlocale( LC_ALL,"rus" );
	uint32_t count=0;
	uint32_t dig;
	uint32_t result=0;
	uint32_t index=0;
	// � ������ ������� ������ �������� ����� N
	printf("������� ������ ������������������ N: ");
	scanf("%d",&count);
	if(count<2000000000)
	{
		//����� �� ������ ����� � ������ �������� N ����������� �����
		while(index<count)
		{
			printf("������� ����� %d: ",index);
			scanf("%d",&dig);
			result^=dig;
			index++;
		}
	}else
		printf("����� N �� ����� 2000000000!!! ");
	printf("��� ����� - %d",result);	
	return 0;
}

