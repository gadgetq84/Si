
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int fill_array(int* array)
{
	int count=0;
	
	while(scanf("%d", &array[count])==1)
	{
		count++;
	}
	
	array = realloc(array,(count)*sizeof(int));
	return count;
}

void print_array(int count,int* array)
{
	for(int i=0;i<count;i++)
		printf("%d ",array[i]);
	printf("\n");
}

void change_max_min(int size, int a[])
{
	int maxI = 0, minI = 0;
    for (int i = 0; i < size; i++)
    {
            if (a[maxI] < a[i])
            {
                maxI = i;
            }
 
            if (a[minI] > a[i])
            {
                minI = i;
            }
    }
    int tmp = a[maxI];
    a[maxI] = a[minI];
    a[minI] = tmp;
}

int main(int argc, char **argv)
{
	int* arr;
	arr = (int*)malloc(250 * sizeof(int));
	setlocale( LC_ALL,"Rus" );
	printf("¬ведите целые числа через пробел в конце\\0 enter или enter и ctrl+z(): ");
	int len =fill_array(arr);
	change_max_min(len, arr);
	print_array(len, arr);
	free(arr);
	return 0;
}

