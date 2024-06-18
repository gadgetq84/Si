#include <ncurses/ncurses.h>
#include <stdio.h>
#include <stdint.h>
#include "sbody.h"

void printSnakeScore(snake_t *head,int i, int x,int y);
void printExit(snake_t *head);
void printLevel(snake_t *head,int x,int y);
WINDOW * printEndScoreBox(int count);
int startMenu(snake_t *head[],int count);
void snake_submenu(WINDOW * win,snake_t *head[],int count, int index);
