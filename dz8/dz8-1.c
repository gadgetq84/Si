
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
}

//void print_array(int count,int* array)
//{
	//for(int i=0;i<count;i++)
		//printf("%d ",array[i]);
	//printf("\n");
}

void sort_array(int size, int a[])
{
	int temp,i, j, min_idx;
	
	for (i = 0; i < size - 1; i++) {
		min_idx = i;
		
		for (j = i + 1; j < size; j++) 
			if (a[j] < a[min_idx])
				min_idx = j; 
		
		temp = a[min_idx];
		a[min_idx] = a[i]; 
		a[i] = temp; 
    } 
}

//int main(int argc, char **argv)
//{
	//int* arr;
	//arr = (int*)malloc(250 * sizeof(int));
	//setlocale( LC_ALL,"Rus" );
	//printf("¬ведите целые числа через пробел в конце\\0: ");
	//int len =fill_array(arr);
	////print_array(len,arr);
	////printf("%d \n",len);
	//sort_array(len, arr);
	//print_array(len,arr);
	//return 0;
}

