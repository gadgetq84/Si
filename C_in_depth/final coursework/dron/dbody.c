#include "dbody.h"

struct control_buttons default_controls1[] = {{KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT},{KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT}};
struct control_buttons default_controls2[] = {{'S','W','A','D'},{'s','w','a','d'}};

void initHead(struct dron_t *head, int x, int y)
{
	head->x = x;
	head->y = y;
	head->direction = RIGHT;
}


void initCart(cart_t t[], size_t size)
{
	struct cart_t init_t={0,0};
	for(size_t i=0; i<size; i++)
	{
		t[i]=init_t;
	}
}


void initDron(dron_t *head[], size_t size, int x, int y, int i,int autop)
{
	head[i] = (dron_t*)malloc(sizeof(dron_t));
	cart_t* cart = (cart_t*)malloc(MAX_CART_SIZE*sizeof(cart_t));
	initCart(cart, MAX_CART_SIZE);
	initHead(head[i], x, y);
	head[i]->color = 4;//default белый цвет
	head[i]->autopilot =autop;//default белый цвет
	head[i]->cart = cart; // прикрепляем к	голове хвост
	head[i]->tsize = size+1;
	head[i]->id = i+100;
	if (i==0)
		head[i]->controls =  default_controls1;
	else
		head[i]->controls =  default_controls2;
}

/*
Увеличение хвоста на 1 элемент
*/
void addCart(dron_t *head)
{
	if(head == NULL || head->tsize>MAX_CART_SIZE)
	{
		mvprintw(0, 0, "Can't add cart");
		return;
	}
	head->tsize++;
}
/*
сброс длины хвоста хвоста
*/
void resetCart(struct dron_t *head)
{
	if(head == NULL)
	{
		mvprintw(0, 0, "Can't reset cart");
		return;
	}else
	{
		for(size_t i=START_CART_SIZE; i<head->tsize; i++)
		{
			mvprintw(head->cart[i].y, head->cart[i].x, " ");
		}
		head->tsize=START_CART_SIZE+1;
	}
}
