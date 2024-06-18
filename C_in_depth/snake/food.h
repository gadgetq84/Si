#include <inttypes.h>


//структура еды struct food

// food.h
#ifndef FOOD_H
#define FOOD_H

enum {MAX_FOOD_SIZE=20,FOOD_EXPIRE_SECONDS=10};
struct foods
{
	int x;
	int y;
	time_t put_time;
	char point;
	uint8_t enable;
};

void initFood(struct foods f[], size_t size);
void putFoodSeed(struct foods *fp);
void putFood(struct foods f[], size_t number_seeds);
void refreshFood(struct foods f[], int nfood);
int getFoodsCount(struct foods f[]);

#endif // FOOD_H
