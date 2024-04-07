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
	char * input_fn="in1.txt";
	FILE* fd;
	char c;
	
	char temp;
	int position;
	int space_count;
	
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
	space_count=0;
	
	while(((c = fgetc(fd))!=EOF) && (c!='\n') && count<line_width)
	{
		line[count] = c;
		if (temp && c!=' ' && (count+1-space_count)%2==0)
		{
			line[position] = c;
			line[count] = temp;
		}
		if(c!=' ')
		{
			temp = c;
			position = count;
		}else
		{
			space_count++;
		}
		count++;
	}
	line[count] = '\0';
	int i=0;
	fprintf(fd,"\n");
	
	while (line[i]!='\0')
	{
		printf("%c",line[i]);
		////if(i)
			////fprintf(fd," ");
		fprintf(fd,"%c",line[i]);
		i++;
	}
	
	fclose(fd);
	
	return 0;
}

