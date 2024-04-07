
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <malloc.h>


typedef struct array_int_t
{
	int res_count;
	int* res_array;
} array_int_t;

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


int getPenultimateZero(int digit)
{
	int ldig = (digit%100)/10;
	return ldig;
}

array_int_t getPzdig(int *array,int count)
{
	int cn=0;
	array_int_t dynamic_array;
	dynamic_array.res_array = (int*)malloc(count * sizeof(int));
    for (int i = 0; i < count; i++)
    { 
            if (getPenultimateZero(array[i])==0)
            { 
				//printf("%d ",array[i]);
				dynamic_array.res_array[cn]=array[i];
				cn++;
			}
    }
    dynamic_array.res_array = realloc(dynamic_array.res_array,(cn-1)*sizeof(int));
	dynamic_array.res_count = cn;
	return dynamic_array;
}

int main(int argc, char **argv)
{
	int arr[10];
	int size = sizeof(arr) / sizeof(arr[0]);
	setlocale( LC_ALL,"Rus" );
	printf("¬ведите %d целых чисел через пробел: ",size);
	fill_array(arr,size);
	print_array(arr,size);
	array_int_t ar_out;
	ar_out = getPzdig(arr,size);
	print_array(ar_out.res_array,ar_out.res_count);
	free(ar_out.res_array);
	return 0;
}

