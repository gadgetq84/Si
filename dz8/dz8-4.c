
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

int is_two_same(int size, int a[])
{
int i , j;
    for(i=0; i<size; i++)
       for(j=i+1; j<size; j++)
          if (a[i]==a[j]) return 1;
   return 0;
}

int main(int argc, char **argv)
{
	int* arr;
	arr = (int*)malloc(250 * sizeof(int));
	setlocale( LC_ALL,"Rus" );
	printf("¬ведите целые числа через пробел в конце\\0 enter или enter и ctrl+z(): ");
	int len =fill_array(arr);
	int res = is_two_same(len, arr);
	printf("%d\n",res);
	free(arr);
	return 0;
}

