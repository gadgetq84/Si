#include <stdio.h>
#include <locale.h>
#define ENG 26

int main(int argc, char **argv)
{
	setlocale( LC_ALL,"rus" );
	int key;
	char symbol;
	printf("¬ведите ключь: ");
	scanf("%d", &key);
	printf("¬ведите сообщение на англецком использу€ 'a'...'z','A'...'Z' и пробел: ");
	while((symbol=getchar())!='.')
	{
		if(symbol >= 'a' && symbol <= 'z')
		{
			symbol = symbol + (key% ENG);
			if(symbol > 'z')
			{
				symbol = symbol - 'z' + 'a' - 1;
			}
		}
		else if(symbol >= 'A' && symbol <= 'Z')
		{
			symbol = symbol + (key% ENG);
			if(symbol > 'Z')
			{
				symbol = symbol - 'Z' + 'A' - 1;
			}
		}
		printf("%c", symbol);
	}
	printf(".\n");
	
	return 0;
}

