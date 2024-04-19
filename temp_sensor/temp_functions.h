#include <stdint.h>
#include <stdio.h>
typedef struct sensor {
	uint8_t minute;
	uint8_t hour;
	uint8_t day;
	uint8_t month;
	uint16_t year;
	int8_t t;
}sensor;

typedef struct sensorview {
	uint8_t month;
	uint16_t year;
	int8_t t;
	int8_t t_min;
	int8_t t_max;
}sensorview;

void SortByT(sensor* info,int n);
void SortByDate( sensor* info,int n);
void print( sensor* info,int number);
void print_view(sensorview* info,int number);
int AddInfo( sensor* info);
FILE* openfile(char * filename);
int getfilesize(FILE* file);
int loadDataFromFile(FILE * file, sensor* info);
int m_temper_view(int number, sensor* info, sensorview* out, int mnth);
int y_temper_view(int number, sensor* info, sensorview* out);
void showHelp();
