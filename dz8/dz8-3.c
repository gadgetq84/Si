
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

//int fill_array(int* array)
//{
	//int count=0;
	
	//while(scanf("%d", &array[count])==1)
	//{
		//count++;
	//}
	
	//array = realloc(array,(count)*sizeof(int));
	//return count;
//}

//void print_array(int count,int* array)
//{
	//for(int i=0;i<count;i++)
		//printf("%d ",array[i]);
	//printf("\n");
}

int find_max_array(int size, int a[])
{
	int max;
	   for (int i = 0; i < size; ++i) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}

//int main(int argc, char **argv)
//{
	//int* arr;
	//arr = (int*)malloc(250 * sizeof(int));
	//setlocale( LC_ALL,"Rus" );
	//printf("¬ведите целые числа через пробел в конце\\0 enter или enter и ctrl+z(): ");
	//int len =fill_array(arr);
	//int res = find_max_array(len, arr);
	//printf("%d\n",res);
	//free(arr);
	//return 0;
//}

