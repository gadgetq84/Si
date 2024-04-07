
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>


void fill_array(int* array)
{
	scanf("%d%d%d%d%d",&array[0],&array[1],&array[2],&array[3],&array[4]);
}
float average(int *array,int count)
{
	int sum=0;
	for(int i=0;i<count;i++) 
    {
		sum += array[i];
	}
	return (float)sum/(float)count;
}
int main(int argc, char **argv)
{
	int arr[5];
	int size = sizeof(arr) / sizeof(arr[0]);
	setlocale( LC_ALL,"Rus" );
	printf("¬ведите %d целых ненулевых чисел через пробел: ",size);
	fill_array(arr);
	printf("%.3f\n",average(arr,size));
	return 0;
}

