#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <ncurses/ncurses.h>
#include "food.h"
#include "sbody.h"

int distance(const snake_t snake, const struct foods food);
void autoChangeDirection(snake_t *snake, struct foods food[], int foodSize,int index);
void go(struct snake_t *head);
void goTail(struct snake_t *head);
int checkDirection(snake_t* snake, int32_t key);
int the_snake_ate_itself(snake_t *head);
void changeDirection(snake_t* snake, const int32_t key);
void pause();
_Bool haveEat(struct snake_t *head, struct foods f[]);
void update(snake_t *snake, struct foods foodss[], int key_pressed, int i, double *delay );
void setColor(int objectType);
