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
	// в первой входной строке вводится число N
	printf("Введите размер последовательности N: ");
	scanf("%d",&count);
	if(count<2000000000)
	{
		//затем по одному числу в строке вводятся N натуральных чисел
		while(index<count)
		{
			printf("Введите число %d: ",index);
			scanf("%d",&dig);
			result^=dig;
			index++;
		}
	}else
		printf("Нужно N не более 2000000000!!! ");
	printf("Это цифра - %d",result);	
	return 0;
}

