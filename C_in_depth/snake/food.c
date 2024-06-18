#include "food.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <ncurses/ncurses.h>
#include <time.h>


 
//struct foods food[MAX_FOOD_SIZE];

void initFood(struct foods f[], size_t size)
{
	struct foods init = {0,0,0,0,0};
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
void putFoodSeed(struct foods *fp)
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
	spoint[0] = fp->point;
	mvprintw(fp->y, fp->x, "%s", spoint);
}

/*
Разместить еду на поле
*/
void putFood(struct foods f[], size_t number_seeds)
{
	for(size_t i=0; i<number_seeds; i++)
	{
		putFoodSeed(&f[i]);
	}
}

void refreshFood(struct foods f[], int nfood)
{
	int max_x=0, max_y=0;
	char spoint[2] = {0};
	getmaxyx(stdscr, max_y, max_x);
	for(size_t i=0; i<nfood; i++)
	{
		if( f[i].put_time )
		{
			if( f[i].enable && (time(NULL) - f[i].put_time) > FOOD_EXPIRE_SECONDS )
			{
				putFoodSeed(&f[i]);
			}
		}
	}
}

int getFoodsCount(struct foods f[])
{
	int count=0;
	for(size_t i=0; i<MAX_FOOD_SIZE; i++)
	if( !f[i].enable)
	{
		count ++;
	}
	return count;
}
