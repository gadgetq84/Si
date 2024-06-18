#include <ncurses/ncurses.h>
#include <stdlib.h>

// sbody.h
#ifndef dBODY_H
#define dBODY_H


enum {CONTROLS=2,MAX_CART_SIZE=100, START_CART_SIZE=0};
enum {LEFT, UP, RIGHT, DOWN, STOP_GAME=KEY_F(10),NEW_GAME=KEY_F(2) ,END_GAME='q'};

// Здесь храним коды управления змейкой

struct control_buttons
{
int down;
int up;
int left;
int right;
};

/*
тележеки это массив состоящий из координат
x,y
*/
typedef struct cart_t
{
	int x;
	int y;
} cart_t;
/*
Дрон содержит в себе
x,y - координаты текущей позиции
direction - направление движения
tsize - кол-во тележек
*tail - ссылка на тележку
*/
typedef struct dron_t
{
	int id;
	int x;
	int y;
	int direction;
	size_t tsize;
	int color;
	int autopilot;
	struct cart_t *cart;
	struct control_buttons *controls;
} dron_t;

void initHead(dron_t *head, int x, int y);
void initCart(cart_t t[], size_t size);
void initDron(dron_t *head[], size_t size, int x, int y, int i,int autop);
void addCart(struct dron_t *head);
void resetCart(struct dron_t *head);
#endif // dBODY_H

