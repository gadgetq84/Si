
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>


int acounter(void)
{
	char sym;
	int count=0;
	scanf("%c",&sym);
	if (sym!='.')
	{
		if(sym=='a')
			count++;
		count+=acounter();
	}
	return count;
}
int main(int argc, char **argv)
{
	setlocale( LC_ALL,"Rus" );
	printf("������ ��������� �� ���������� ����, �������� � ������ ����������. � ����� ������ ������ '.' : ");
	printf("%d",acounter());
	return 0;
}

