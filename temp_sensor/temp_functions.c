#include "temp_functions.h"
#include "color.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 6
#define MONTHS 12
#define DAYS 31

void showHelp()
{
	yellowcolor();
	printf(" This program processes data from a temperature sensor over a certain period of time from a file in csv format.\n\n");
	printf("  -h show help information\n");
	printf("  -f full path to the file\n");
	printf("  -m <month number> if this key is specified, then only statistics for the specified month are displayed\n\n\n");
	resetcolor();
}


void cgangeIJ( sensor* info,int i,int j)
{
	sensor temp;
	temp=info[i];
	info[i]=info[j];
	info[j]=temp;
}

//упорядочивающую его по температуре
void SortByT(sensor* info,int n)
{
	for(int i=0; i<n; ++i)
	for(int j=i; j<n; ++j)
	if(info[i].t>=info[j].t)
		cgangeIJ(info,i,j);
}

uint32_t DateToInt(sensor* info)
{
	return info->year << 16 | info->month << 8 |	info->day + (info->hour)/24+(info->minute)/1440 ;
}
//упорядочивающую его по дате
void SortByDate(sensor* info,int n)
{
	for(int i=0; i<n; ++i)
	{
		for(int j=i; j<n; ++j)
		{
			if(DateToInt(info+i)>=DateToInt(info+j))
				cgangeIJ(info,i,j);
		}
	}
}
void AddRecord(sensor* info,int number, uint16_t year,uint8_t month,uint8_t day, uint8_t hour, uint8_t minute ,int8_t t)
{
	info[number].year = year;
	info[number].month = month;
	info[number].day = day;
	info[number].hour = hour;
	info[number].minute = minute;
	info[number].t = t;
}

void AddRecordview(sensorview* info,int number, uint16_t year,uint8_t month,int8_t t,int8_t t_min,int8_t t_max)
{
	info[number].year = year;
	info[number].month = month;
	info[number].t = t;
	info[number].t_min = t_min;
	info[number].t_max = t_max;
}

int AddInfo(sensor* info)
{
	int counter=0;
	//AddRecord(info,counter++,2021,9,16,9);
	//AddRecord(info,counter++,2022,9,2,-9);
	//AddRecord(info,counter++,2021,1,7,8);
	//AddRecord(info,counter++,2021,9,5,1);
	return counter;
}
void print(sensor* info,int number)
{
	printf("===================================\n");
	for(int i=0;i<number;i++)
	printf("%04d-%02d-%02d %02d:%02d t=%3d\n",(info+i)->year, info[i].month, info[i].day,info[i].hour,info[i].minute,info[i].t );
}

void print_view(sensorview* info,int number)
{
	printf("===================================\n");
	for(int i=0;i<number;i++)
		if(info[i].month!=0)
			printf("%04d-%02d t-aver=%3d t-min=%3d t-max=%3d\n",info[i].year, info[i].month,info[i].t,info[i].t_min,info[i].t_max );
		else
			printf("%04d t-aver=%3d t-min=%3d t-max=%3d\n",info[i].year, info[i].t,info[i].t_min,info[i].t_max );
}

int getfilesize(FILE* file)
{
	fseek(file, 0, SEEK_END);
	int res = ftell(file);
	fseek(file, 0,SEEK_SET);
	return res;
}
FILE* openfile( char * filename)
{
	FILE* file = fopen(filename,"r");
	if (file==NULL)
	{	
		redcolor();
		printf("Error open file\n");
		resetcolor();
		return NULL;
	}
	return file;
}

int loadDataFromFile(FILE * file, sensor* info)
{
	int negative=1;
	int counter=0;
	int r_counter=0;
	int arr[N] = {0};
	char ch = 0;
	while((ch=fgetc(file))!=EOF)
	{
		
		if(ch==';')
		{
			counter++;
			negative =1;
			if(counter>N)
				counter =0;
		}
		else if(ch =='\n')
		{
			if(counter ==N-1)
			{
				AddRecord(info,r_counter++,arr[0],arr[1],arr[2],arr[3],arr[4],negative*arr[5]);
			}
			else
			{
				redcolor();
				printf("error load data from line %d = %d;%d;%d;%d;%d;%d;\n",r_counter+1,arr[0],arr[1],arr[2],arr[3],arr[4],arr[5]);
				resetcolor();
			}
			counter =0;
			negative =1;
			arr[0]=arr[1]=arr[2]=arr[3]=arr[4]=arr[5]=0;
		}
		else if(ch>='0' && ch<='9')
		{
			arr[counter] = arr[counter]*10 +ch -'0';
		}
		else if(ch=='-')
			negative = (-1);
		else if(ch !=0x0D && ch !=' ')
			counter = 0;
	}
	//сортировка такого обьема данных это зло
	//SortByDate(info,r_counter);
	return r_counter;
}

int m_temper_view(int number, sensor* info, sensorview* out, int mnth)
{
	int Y=0;
	int M =0;
	int sum;
	int count;
	int r_count=0;
	int t_min;
	int t_max;

	for(int i=0; i<number; i++)
	{ 
		sum = 0;
		count=0;
		
		if(mnth==0)
	    {
			Y=info[i].year;
			M=info[i].month;
		t_min = info[i].t;
		t_max = info[i].t;
		for(int j=i; j<number; j++)
		{		
			if( Y == info[j].year && M == info[j].month)
			{
				sum += info[j].t;
				count++;
				if(t_min>info[j].t)
				{
					t_min = info[j].t;
				}
				if(t_max<info[j].t)
				{
					t_max = info[j].t;
				}
			}
				
		}
			i += count-1;
		
			AddRecordview(out,r_count++,Y,M,sum/count,t_min,t_max);
		}
		else if(info[i].month==mnth)
		{
			Y=info[i].year;
			M=info[i].month;

		t_min = info[i].t;
		t_max = info[i].t;
		for(int j=i; j<number; j++)
		{		
			if( Y == info[j].year && M == info[j].month)
			{
				sum += info[j].t;
				count++;
				if(t_min>info[j].t)
				{
					t_min = info[j].t;
				}
				if(t_max<info[j].t)
				{
					t_max = info[j].t;
				}
			}
				
		}
		i += count-1;
		
		AddRecordview(out,r_count++,Y,M,sum/count,t_min,t_max);
		}
	}

	return r_count;
}

int y_temper_view(int number, sensor* info, sensorview* out)
{
	int Y=0;
	int sum;
	int count;
	int r_count=0;
	int t_min;
	int t_max;
		for(int i=0; i<number; i++)
		{ 
			Y=info[i].year;
			sum = 0;
			count=0;
			t_min = info[i].t;
			t_max = info[i].t;
			for(int j=i; j<number; j++)
			{		
				if( Y == info[j].year)
				{
					sum += info[j].t;
					count++;
					if(t_min>info[j].t)
					{
						t_min = info[j].t;
					}
					if(t_max<info[j].t)
					{
						t_max = info[j].t;
					}
				}
					
			}
			i += count-1;
			
			AddRecordview(out,r_count++,Y,0,sum/count,t_min,t_max);
		}
	return r_count;
}



