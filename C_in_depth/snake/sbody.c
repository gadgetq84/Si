#include "sbody.h"

struct control_buttons default_controls1[] = {{KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT},{KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT}};
struct control_buttons default_controls2[] = {{'S','W','A','D'},{'s','w','a','d'}};

void initHead(struct snake_t *head, int x, int y)
{
	head->x = x;
	head->y = y;
	head->direction = RIGHT;
}


void initTail(struct tail_t t[], size_t size)
{
	struct tail_t init_t={0,0};
	for(size_t i=0; i<size; i++)
	{
		t[i]=init_t;
	}
}


void initSnake(snake_t *head[], size_t size, int x, int y, int i)
{
	head[i] = (snake_t*)malloc(sizeof(snake_t));
	tail_t* tail = (tail_t*)malloc(MAX_TAIL_SIZE*sizeof(tail_t));
	initTail(tail, MAX_TAIL_SIZE);
	initHead(head[i], x, y);
	head[i]->color = 3;//default белый цвет
	head[i]->autopilot = 1;//default белый цвет
	head[i]->tail = tail; // прикрепляем к	голове хвост
	head[i]->tsize = size+1;
	if (i==0)
		head[i]->controls =  default_controls1;
	else
		head[i]->controls =  default_controls2;
}

/*
Увеличение хвоста на 1 элемент
*/
void addTail(struct snake_t *head)
{
	if(head == NULL || head->tsize>MAX_TAIL_SIZE)
	{
		mvprintw(0, 0, "Can't add tail");
		return;
	}
	head->tsize++;
}
/*
сброс длины хвоста хвоста
*/
void resetTail(struct snake_t *head)
{
	if(head == NULL)
	{
		mvprintw(0, 0, "Can't reset tail");
		return;
	}else
	{
		for(size_t i=START_TAIL_SIZE; i<head->tsize; i++)
		{
			mvprintw(head->tail[i].y, head->tail[i].x, " ");
		}
		head->tsize=START_TAIL_SIZE+1;
	}
}
