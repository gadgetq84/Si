
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>


typedef struct array_char
{
	char string1[100];
	char string2[100];
	
} array_char;

char* get_char_count(array_char str)
{
	char* res;
	res = malloc (sizeof (char) * 100);
	const char* curpos; 
	int n =0;
	int count;
	int rescount=0;
	while(str.string2[n]!='\0')
	{
		count = 0;
		curpos = strchr(str.string1,str.string2[n]);
		while(curpos !=NULL)
		{
			curpos = strchr(++curpos,str.string2[n]);
			count++;
		}
		if(count == 1)
		{
			res[rescount++]=str.string2[n];
		}
		n++;
	}
	qsort(res, rescount, sizeof(char), (int (*)(const void *,const  void *)) strcmp);
	res[rescount] = 0;
	return res;
}



int main(int argc, char **argv)
{
	char * input_fn="in.txt";
	char * out_fn="out.txt";
	FILE* fd;
	setlocale( LC_ALL,"Rus" );

	if((fd = fopen(input_fn,"r"))==NULL)
	{
		perror("Error");
		return 1;
	}
	array_char struc;
	fscanf(fd,"%s%s",struc.string1,struc.string2);
	char* result = get_char_count(struc);
	fclose(fd);
	
	if((fd = fopen(out_fn,"w"))==NULL)
	{
		perror("Error");
		return 1;
	}
	int i=0;
	while (result[i]!='\0')
	{
		if(i)
			fprintf(fd," ");
		fprintf(fd,"%c",result[i]);
		i++;
	}
	fclose(fd);
	
	free(result);
	return 0;
}

