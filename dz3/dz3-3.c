
#include <stdio.h>
#include <locale.h>

int main(int argc, char **argv)
{
	setlocale( LC_ALL,"Rus" );
	
	int a[2];
	printf("������� 3 ����� ����� ����������� �������� : ");
	scanf("%d%d%d",&a[0],&a[1],&a[2]);
    if(a[0]<a[1] && a[1]<a[2])
	{
		printf(" YES\n");
	}
    else
    {
	   printf(" NO\n");
	}
return 0;
}
