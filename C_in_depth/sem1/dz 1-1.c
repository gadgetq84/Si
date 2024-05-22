#include <stdio.h>
#include <locale.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
// 6 1 2 3 2 0 3
int max_d(int a, int b)
{
	return a - ((a - b) & ((a - b) >> 31));
}

int main(int argc, char **argv)
{
	setlocale( LC_ALL,"Rus" );
	int count=-2;
	int index =0;
	int max_dig=INT_MIN;
	int dig;
	uint8_t flag=1;
	uint8_t max_count=0;
	printf("Введите размер и саму последовательность через пробел: ");
	while(flag ==1)
		{
			scanf("%d",&dig);
			if(index==count-1)
				flag=0;
			if(count==-2)
			{
				count = dig;
			}
			else
			{
				if(index==0)
					max_dig=dig;
				
				if(!(max_dig^dig))
				{
					max_count++;
				}	
				else
				{
					max_dig= max_d(max_dig,dig);
				}
				
				index++;
			}
		}
	printf("This sequence occurs at most: %d times",max_count);
	return 0;
}

