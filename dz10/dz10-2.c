
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

char * myTrim(int count,char string[count])
{
	char * res;
	res= malloc (sizeof (char) * count);
	int i = 0,position_beg =0,res_count=0;
	while (string[i]!='\0')
	{
		if ((string[i]==' ' && i==0) || (string[i]==' ' && position_beg==i-1) )
		{
			position_beg = i;
		}else
		{
			res[res_count++] = string[i];
			if ( string[i]==' ')
			{
				position_beg = i;
			}
		}
		i++;
	}
	if(res[res_count-1]==' ')
		res = realloc(res,(res_count-1)*sizeof(char));
	return res;
}

int main(int argc, char **argv)
{
	char * input_fn="in2.txt";
	FILE* fd;
	char c;
	
	int line_width,count;
	setlocale( LC_ALL,"Rus" );

	if((fd = fopen(input_fn,"r+"))==NULL)
	{
		perror("Error");
		return 1;
	}
	
	line_width = get_filesize(fd);
	
	char line[line_width];
	count = 0;
	
	while(((c = fgetc(fd))!=EOF) && (c!='\n') && count<line_width)
	{
		line[count++] = c;
	}
   
	line[count] = '\0';
	
	char * res= myTrim(count,line);
	
	int i=0;
	fprintf(fd,"\n");
	
	while (res[i]!='\0')
	{
		fprintf(fd,"%c",res[i]);
		i++;
	}
	
	fclose(fd);
	free(res);
	return 0;
}

