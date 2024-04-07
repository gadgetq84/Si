
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
	
	while(((c = fgetc(fd))!=EOF) && (c!='\n') && count<line_width)
	{
		switch (c)
		{
			case 'A': 
			    line[count++] = 'B';
				break;
			case 'a': 
			    line[count++] = 'b';
				break;
			case 'B': 
				line[count++] = 'A';
				break;
			case 'b': 
				line[count++] = 'a';
				break;
			default:
				line[count++] = c;
		}
	}
	line[count] = '\0';
	
	int i=0;
	fseek(fd, 0,SEEK_SET);
	while (line[i]!='\0')
	{
		//if(i)
			//fprintf(fd," ");
		fprintf(fd,"%c",line[i]);
		i++;
	}
	
	fclose(fd);
	
	return 0;
}

