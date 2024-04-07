
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

char * ch_ext(int count,char string[count])
{
	char * res;
	const char* curpos;
	const char* temp;
	temp = strchr(string,'/');
	while(temp !=NULL)
	{
		temp = strchr(++temp,'/');
		if (temp)
		{
			curpos = temp;
		}
	}
	int slash_pos =(curpos-string+1);
	
	curpos = NULL;
	temp = strchr(string,'.');
	curpos=temp;
	while(temp !=NULL)
	{
		temp = strchr(++temp,'.');
		
		if (temp!=NULL)
		{
			curpos = temp;
		}
	}
	
	int dot_pos;
	if(curpos!=NULL)
		dot_pos=(curpos-string);
	else
		dot_pos=-1;
	
	char * ext = ".html";
	if(slash_pos>dot_pos || dot_pos==-1)
	{
		res= malloc (sizeof (char) * count);
		strncpy(res,string,count);
		strcat(res,ext);
		
	}
	
	if(slash_pos<dot_pos)
	{
		res= malloc (sizeof (char) * dot_pos);
		strncpy(res,string,dot_pos);
		strcat(res,ext);
		
	}
	return res;
}

int main(int argc, char **argv)
{
	char * input_fn="in3.txt";
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
	
	char * res= ch_ext(count,line);
	
	int i=0;
	fprintf(fd,"\n");
	
	while (res[i]!='\0')
	{
		printf("%c",res[i]);
		fprintf(fd,"%c",res[i]);
		i++;
	}
	
	fclose(fd);
	free(res);
	return 0;
}

