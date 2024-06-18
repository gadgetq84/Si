#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <ncurses/ncurses.h>
#include "harvest.h"
#include "dbody.h"

int distanceHarvest(const dron_t dron, const harvests harvest);
void autoChangeDirection(dron_t *dron, harvests harvest[], int harvestSize,int index);
void go(dron_t *head);
void goCart(dron_t *head);
int checkDirection(dron_t *dron, int32_t key);
int isCrush(dron_t *head);
void changeDirection(dron_t *dron, const int32_t key);
void pause();
_Bool collectionOfUnits(dron_t *head, harvests f[]);
void update(dron_t *dron, harvests harvest[], int key_pressed, int i );
void setColor(int objectType);
