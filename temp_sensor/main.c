#include <stdio.h>
#include "temp_functions.h"
#include "color.h"
#include <stdlib.h>
#include <unistd.h>
#define SIZE 20


int main(int argc, char **argv)
{
	int rez_param =0;
	char filename[256]={0};
	char singlemonth[2]={0};
	int help=0;
	opterr = 0;
	//обработка аргументов командной строки
	while ((rez_param = getopt(argc,argv,"hf:m:"))!=-1)
	{
		switch(rez_param)
		{
			case 'h': 
				help =1; 
				
				break;
			case 'f': 
				if(strlen(optarg)<257)
					strcpy(filename,optarg); 
				else
					{
						redcolor();
						printf("maximum path size 256 characters \n",optarg);
						resetcolor();
						return 1;
					}
				break;
			case 'm':
				if(atoi(optarg)>=1 && atoi(optarg)<=12)
					strcpy(singlemonth,optarg); 
				else
					{
						redcolor();
						printf("enter a month value between 1 and 12 \n",optarg);
						resetcolor();
						return 1;
					}
				break;
			case '?': 
				printf("Error argument found!!!\n"); 
				return 1;
				break;
		}
	}
	//если нет аргументов выводим help
	if((singlemonth[0]!='\0' || filename[0]!='\0') && help !=1)
	{
		FILE* mFile;
		//задаем имя файла по умолчанию 
		char defaultfilename[] = "temperature_big.csv";
		//если -f присутствует открываем файл что указан в аргументе
		if(filename[0]!='\0')
			mFile = openfile(filename);
		else
			mFile = openfile(defaultfilename);
			
		if (mFile!=NULL)
		{
			int mnth=0;
			int filesize = getfilesize(mFile);
			sensor* info = (sensor*) calloc(filesize/sizeof(sensor),sizeof(sensor));
			int number  = loadDataFromFile(mFile,info);
			fclose(mFile);
			greencolor();
			printf("%d lines loaded.\n",number);
			resetcolor();
			
			greencolor();
			printf("\nAverage temperature per month\n");
			resetcolor();
			sensorview average_m[SIZE];
			int res_countm = 0;
			
			//..если указан параметр -m
			if(singlemonth[0]!='\0')
			{
				mnth = atoi(singlemonth);
				res_countm = m_temper_view(number,info,average_m,mnth);
				print_view(average_m,res_countm);
			}
			//если не указан параметр -m
			else
			{
				res_countm = m_temper_view(number,info,average_m,mnth);
				print_view(average_m,res_countm);
				
				greencolor();
				printf("\nAverage temperature for the year\n");
				resetcolor();
				sensorview average_y[SIZE];
				int res_county = y_temper_view(number,info,average_y);
				print_view(average_y,res_county);
			}
			free(info);
		}
	}else
	{
		showHelp();
	}
	return 0;
}

