
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

void swap(int* a, int* b) 
{ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 

int lastdigit(int digit)
{
	int ldig = digit%10;
	return ldig;
}

void sortlastdigit(int *array,int count)
{
	int i, j, min_idx; 

    for (i = 0; i < count - 1; i++) { 
        min_idx = i; 
        for (j = i + 1; j < count; j++) 
            if (lastdigit(array[j]) < lastdigit(array[min_idx])) 
                min_idx = j; 
        swap(&array[min_idx], &array[i]); 
    } 
}

int main(int argc, char **argv)
{
	int arr[10];
	int size = sizeof(arr) / sizeof(arr[0]);
	setlocale( LC_ALL,"Rus" );
	printf("¬ведите %d целых чисел через пробел: ",size);
	fill_array(arr,size);
	print_array(arr,size);
	sortlastdigit(arr,size);
	print_array(arr,size);
	return 0;
}

