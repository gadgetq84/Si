
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
//для сравнения элементов массива
int compare( const void* a, const void* b)
{
     int int_a = * ( (int*) a );
     int int_b = * ( (int*) b );
     if ( int_a == int_b ) return 0;
     else if ( int_a < int_b ) return -1;
     else return 1;
}

int main(int argc, char **argv)
{
	char * input_fn="in3.txt";
	FILE* fd;
	//счетчики 
	int line_width,count,count2;
	setlocale( LC_ALL,"Rus" );
	//открываем на чтение и запись
	if((fd = fopen(input_fn,"r+"))==NULL)
	{
		perror("Error");
		return 1;
	}
	//сюда  будут записаны считанные данные
	char * scan;
	//сюда сложим все циферки
	char* dig;
	//кол-во байт в файле 
	line_width = get_filesize(fd);
	//сюда пишем наш массив из int 
	int line[line_width];
	int strl;
	//выделяем память 
	scan=(char*)malloc(line_width * sizeof(char));
	//сбрасываем счетчик
	count2=0;
	// пробегаемся по файлику
	while(fscanf(fd,"%s",scan)==1)
	{
		strl= strlen(scan);
		
		dig=(char*)malloc(strl * sizeof(int));
		count=0;
		
		for(int i=0;i<strl;i++)
		{
			//если циферки то складываем их временно в dig
			if(scan[i]>='0' && scan[i]<='9')
			{
				dig[count++] = scan[i];
			}
		}
		// если длина строки больше 0 значит можно число выгружать в интовый массив
		if(strlen(dig)>0)
		{
			line[count2]=atoi(dig);
			count2++;
		}
		free(dig);
	}
	free(scan);
	
	int i=0;
	fprintf(fd,"\n");
	//сортировка
	qsort( line, count2, sizeof(int), compare );
	//записываем обратно все в файл
	while (i<count2)
	{
		if(i)
			fprintf(fd," ");
		fprintf(fd,"%d",line[i]);
		
		i++;
	}
	;
	fclose(fd);
	
	return 0;
}

