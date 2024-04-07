
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <malloc.h>
int* res_array;

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

int count_numbarray(int *array,int count)
{
	int i,j,dig,max_count;
	dig = 1;
	max_count = 0;
	for(i = 0;i<count;i++)
	{
		int frequent = 0; 
		for(j = 0;j<count;j++)
		{
			if (array[i] == array[j])
			{
				frequent++;
			}
		}
		if(frequent>max_count)
		{
			max_count =  frequent;
			dig = array[i];
		}

	}
	return dig;
}

int main(int argc, char **argv)
{
	int arr[10];
	int size = sizeof(arr) / sizeof(arr[0]);
	setlocale( LC_ALL,"Rus" );
	printf("¬ведите %d целых чисел через пробел: ",size);
	fill_array(arr,size);
	print_array(arr,size);
	printf("%d\n", count_numbarray(arr,size));
	return 0;
}

