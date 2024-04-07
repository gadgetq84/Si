
#include <stdio.h>
#include <locale.h>

int main(int argc, char **argv)
{
	setlocale( LC_ALL,"Rus" );
	
	int a[4];
	int temp;
	printf("¬ведите 5 целых чисел разделенных пробелом : ");
	scanf("%d%d%d%d%d",&a[0],&a[1],&a[2],&a[3],&a[4]);
	temp = a[0];
	for(int i =1;i<5;i++)
	{
	  if(a[i]<temp)
	  {
		temp=a[i];  
	  }
	}

	printf(" %d\n",temp);
	return 0;
}
