
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
//}

void sort_even_odd(int n, int a[])
{
    int i =0;
    int j =0;
    int temp;
    int even_count=0;
    int odd_count = 0;
    while (i < n && n>even_count+odd_count) {
        if (a[i] % 2 != 0  ) {
			temp=a[i];
			for(j=i;j<n-1;j++) 
			{
				a[j] = a[j+1];
			}
			odd_count++;
			a[n-1] = temp;
        }
        if (a[i] % 2 == 0)
        {
			even_count++;
		}
        i++;
	} 
}

//int main(int argc, char **argv)
//{
	//int* arr;
	//arr = (int*)malloc(250 * sizeof(int));
	//setlocale( LC_ALL,"Rus" );
	//printf("¬ведите целые числа через пробел в конце\\0 enter или enter и ctrl+z(): ");
	//int len =fill_array(arr);
	//sort_even_odd(len, arr);
	//print_array(len,arr);
	//free(arr);
	//return 0;
//}

