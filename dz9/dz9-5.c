
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>


int get_filesize(FILE* fd)
{
	fseek(fd, 0, SEEK_END);
	int res = ftell(fd);
	fseek(fd, 0,SEEK_SET);
	return res;
}

int main(int argc, char **argv)
{
	char * input_fn="in5.txt";
	FILE* fd;

	//счетчики 
	int line_width;
	setlocale( LC_ALL,"Rus" );
	//открываем на чтение и запись
	if((fd = fopen(input_fn,"r+"))==NULL)
	{
		perror("Error");
		return 1;
	}
	//сюда  будут записаны считанные данные
	char * scan;
	char * res_str;
	//кол-во байт в файле 
	line_width = get_filesize(fd);


	//выделяем память 
	scan=(char*)malloc(line_width);
	res_str=(char*)malloc(line_width);
	int max=0;
	// пробегаемся по файлику
	while(fscanf(fd,"%s",scan)==1)
	{
		if(max<strlen(scan))
		{
			max=strlen(scan);
			strcpy(res_str,scan);
		}
	}
	free(scan);
	//printf("%s",res_str);
	
	int i=0;
	fprintf(fd,"\n");
	
	//записываем обратно все в файл
	while (i<max)
	{
		fprintf(fd,"%c",res_str[i]);
		i++;
	}
	
	fclose(fd);
	free(res_str);
	return 0;
}

