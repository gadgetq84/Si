#include <stdio.h>
#include <stdint.h>
#include "dbody.h"

#include <string.h>

#ifndef MENU_H
#define MENU_H
typedef struct startsettings
{
int menuchoice;
int droncount;
int *autopilot;
}startsettings;

void printDronScore(dron_t *head,int i, int x,int y);
void printHarvestScore(int count);
void printExit(dron_t *head);
void printLevel(dron_t *head,int x,int y);
int printEndScoreBox(int count);
void mainMenu(startsettings *menusettings);
void dron_autopilotsubmenu(WINDOW * win,startsettings *menusettings,int index);
void dron_selectsubmenu(WINDOW * win,startsettings *menusettings,int index);
void dron_countsubmenu(WINDOW * win,startsettings *menusettings);
#endif // MENU_H
