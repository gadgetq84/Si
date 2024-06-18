#include <inttypes.h>


//структура еды struct food

// food.h
#ifndef HARVEST_H
#define HARVEST_H

enum {MAX_HARVEST_SIZE=10,HARVEST_EXPIRE_SECONDS=10};
typedef struct harvests
{
	int x;
	int y;
	time_t put_time;
	char point;
	uint8_t enable;
	int st;
}harvests;

void initHarvest( harvests f[], size_t size);
void putHarvestSeed( harvests *fp);
void putHarvest(harvests f[], size_t number_seeds);
void refreshHarvest(harvests f[], int nfood);
int getHarvestsCount(harvests f[]);

#endif // HARVEST_H
