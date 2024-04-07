
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
	char * input_fn="in4.txt";
	FILE* fd;
	const char* curpos; 
	//�������� 
	int line_width,count,count2;
	setlocale( LC_ALL,"Rus" );
	//��������� �� ������ � ������
	if((fd = fopen(input_fn,"r+"))==NULL)
	{
		perror("Error");
		return 1;
	}
	//����  ����� �������� ��������� ������
	char * scan;
	char * res_str;
	//���-�� ���� � ����� 
	line_width = get_filesize(fd);


	//�������� ������ 
	scan=(char*)malloc(line_width);
	res_str=(char*)malloc(line_width);
	count=0;
	count2=0;
	// ����������� �� �������
	while(fscanf(fd,"%s",scan)==1)
	{
		int n=0;
	
		while(n<strlen(scan))
		{
			count = 0;
			curpos = strchr(res_str,scan[n]);
			
			while(curpos !=NULL)
			{
				curpos = strchr(++curpos,scan[n]);
				count++;
			}
			if(count==0)
			{
				res_str[count2++]=scan[n];
				
			}
		n++;
		}
	}
	free(scan);
	
	
	int i=0;
	fprintf(fd,"\n");
	
	//���������� ������� ��� � ����
	while (i<count2)
	{
		fprintf(fd,"%c",res_str[i]);
		i++;
	}
	
	fclose(fd);
	free(res_str);
	return 0;
}

