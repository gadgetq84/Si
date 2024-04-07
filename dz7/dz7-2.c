
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>


void fill_array(int* array)
{
	scanf("%d%d%d%d%d",&array[0],&array[1],&array[2],&array[3],&array[4]);
}
int arraymin(int *array,int count)
{
	int min=array[0];
	for(int i=1;i<count;i++) 
    {
		if(array[i]<min)
			min = array[i];
	}
	return min;
}
int main(int argc, char **argv)
{
	int arr[5];
	int size = sizeof(arr) / sizeof(arr[0]);
	setlocale( LC_ALL,"Rus" );
	printf("¬ведите %d целых ненулевых чисел через пробел: ",size);
	fill_array(arr);
	printf("%d\n",arraymin(arr,size));
	return 0;
}

