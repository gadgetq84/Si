#include "harvest.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <ncurses/ncurses.h>
#include <time.h>


void initHarvest(harvests f[], size_t size)
{
	harvests init = {0,0,0,0,0,0};
	int max_y=0, max_x=0;
	getmaxyx(stdscr, max_y, max_x);
	for(size_t i=0; i<size; i++)
	{
		f[i] = init;
	}
}

/*
Обновить/разместить текущее зерно на поле
*/
void putHarvestSeed(harvests *fp)
{
	int max_x=0, max_y=0;
	char spoint[2] = {0};
	getmaxyx(stdscr, max_y, max_x);
	mvprintw(fp->y, fp->x, " ");
	fp->x = rand() % (max_x - 1);
	fp->y = rand() % (max_y - 2) + 1; //Не занимаем верхнюю строку
	fp->put_time = time(NULL);
	fp->point = 'O';
	fp->enable = 1;
	fp->st= 0;
	spoint[0] = fp->point;
	mvprintw(fp->y, fp->x, "%s", spoint);
}

/*
Разместить еду на поле
*/
void putHarvest(harvests f[], size_t number_seeds)
{
	for(size_t i=0; i<number_seeds; i++)
	{
		putHarvestSeed(&f[i]);
	}
}

void refreshHarvest(harvests f[], int nhr)
{
	int max_x=0, max_y=0;
	//char spoint[2] = {0};
	getmaxyx(stdscr, max_y, max_x);
	for(size_t i=0; i<nhr; i++)
	{
		if( f[i].put_time )
		{
			if( f[i].enable && (time(NULL) - f[i].put_time) > HARVEST_EXPIRE_SECONDS )
			{
				putHarvestSeed(&f[i]);
			}
		}
	}
}

int getHarvestsCount(harvests f[])
{
	int count=0;
	for(size_t i=0; i<MAX_HARVEST_SIZE; i++)
	if( !f[i].enable)
	{
		count ++;
	}
	return count;
}
