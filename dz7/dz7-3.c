
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>


void fill_array(int* array,int count)
{
	for(int i=0;i<count;i++)
		scanf("%d",&array[i]);
}

void print_array(int* array,int count)
{
	for(int i=0;i<count;i++)
		printf("%d ",array[i]);
	printf("\n");
}

void shift_array(int *array,int count,int ch_count)
{
	while(ch_count>0)
	{
		int temp=array[count-1];
		for(int i=count-1;i>=0;i--) 
		{
			array[i] = array[i-1];
		}
		array[0] = temp;
		ch_count--;
	}
}

int main(int argc, char **argv)
{
	int arr[12];
	int size = sizeof(arr) / sizeof(arr[0]);
	setlocale( LC_ALL,"Rus" );
	printf("¬ведите %d целых чисел через пробел: ",size);
	fill_array(arr,size);
	print_array(arr,size);
	shift_array(arr,size,4);
	print_array(arr,size);
	return 0;
}

