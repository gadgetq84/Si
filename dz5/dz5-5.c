
#include <stdio.h>
#include <locale.h>
#include <math.h>

int main(int argc, char **argv)
{
	setlocale( LC_ALL,"Rus" );
	int count1=0;
	int count2=0;
	char symbol;
	int stat = puts("На вход подается строка состоящая из символов (, ) заканчивающаяся символом .");
	while((symbol=getchar())!='.')
	{
		if(symbol=='(')
		count1++;
		if(symbol==')')
		count2++;
	}
	if(count1==count2)
		printf("YES\n");
	else
		printf("NO\n");

	return 0;
}

