#include <ncurses/ncurses.h>
#include <stdlib.h>

// sbody.h
#ifndef SBODY_H
#define SBODY_H


enum {CONTROLS=2,MAX_TAIL_SIZE=100, START_TAIL_SIZE=3};
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
Хвост это массив состоящий из координат
x,y
*/
typedef struct tail_t
{
	int x;
	int y;
} tail_t;
/*
Голова змейки содержит в себе
x,y - координаты текущей позиции
direction - направление движения
tsize - размер хвоста
*tail - ссылка на хвост
*/
typedef struct snake_t
{
	int x;
	int y;
	int direction;
	size_t tsize;
	int color;
	int autopilot;
	struct tail_t *tail;
	struct control_buttons *controls;
} snake_t;

void initHead(struct snake_t *head, int x, int y);
void initTail(struct tail_t t[], size_t size);
void initSnake(snake_t *head[], size_t size, int x, int y, int i);
void addTail(struct snake_t *head);
void resetTail(struct snake_t *head);
#endif // SBODY_H

