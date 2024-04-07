
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
	char * input_fn="in6.txt";
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
	int count=0;
	// пробегаемся по файлику
	while(fscanf(fd,"%s",scan)==1)
	{
		if(scan[strlen(scan)-1]=='a')
		{
			count++;
		}
	}
	free(scan);
	printf("%s",res_str);
	
	fprintf(fd,"\n");
	
	//записываем обратно все в файл
		fprintf(fd,"%d",count);
	
	fclose(fd);
	free(res_str);
	return 0;
}

