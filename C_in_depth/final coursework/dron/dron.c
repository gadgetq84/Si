#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <ncurses/ncurses.h>
#include "harvest.h"
#include "dbody.h"
#include "control.h"
#include "menu.h"
#define MIN_Y 2
#define PLAYERS 1

int main()
{
	int endgame=0;
	int selfdestruction = 0;
	int itsfull=0;
	int endchoice=0;
	startsettings menusettings={0,PLAYERS,0};
	menusettings.autopilot = (int*) calloc(menusettings.droncount, sizeof(int));
	
		
	initscr();
	cbreak();
	
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
		
	keypad(stdscr, TRUE); // Включаем F1, F2,стрелки и т.д.
	raw(); // Откдючаем line buffering
	noecho(); // Отключаем echo() режим при вызове getch
	curs_set(FALSE); //Отключаем курсор
	//начальное меню
	mainMenu(&menusettings);
	
	dron_t  *dron[menusettings.droncount];
	harvests* harvest = (harvests *) malloc(sizeof(harvests)*MAX_HARVEST_SIZE);
		
	for (int i = 0; i < menusettings.droncount; i++)
	{
		initDron(dron,START_CART_SIZE,40+i,10+i,i,menusettings.autopilot[i]);
	}
	initHarvest(harvest,MAX_HARVEST_SIZE);
	
	setColor(2);
	mvprintw(0, 1," Press'q' for end GAME");
	
	timeout(0); //Отключаем таймаут после нажатия клавиши в цикле
	int key_pressed=0;

	setColor(1);
	putHarvest(harvest,MAX_HARVEST_SIZE);
	printHarvestScore(getHarvestsCount(harvest));
		
	refresh();
	double DELAY = 0.15;
	while( key_pressed != STOP_GAME && menusettings.menuchoice!=333) 
	{
		clock_t begin = clock();
		key_pressed = getch(); // Считываем клавишу
		if(key_pressed == 'p' || key_pressed == 'P')
		{
			 pause();
		}	
		if(key_pressed == END_GAME)
		{
			endgame=1;
		}
		if(getHarvestsCount(harvest)== MAX_HARVEST_SIZE)
		{
			itsfull = 1;
		}
		
		for (int i = 0; i < menusettings.droncount; i++)
		{
			
			update(dron[i],harvest,key_pressed,i);
			selfdestruction = isCrush(dron[i]);
		}
		
		//слопали все тыквы пора показывать наш результат 
		if(itsfull==1 || endgame==1 || selfdestruction==1)
		{
			if(selfdestruction==1)
				endchoice = printEndScoreBox("Collision over cart!!!",getHarvestsCount(harvest));
			else
				endchoice = printEndScoreBox("",getHarvestsCount(harvest));
			if(endchoice==1)
			{
				//расставляем тыквы
				putHarvest(harvest,MAX_HARVEST_SIZE);
				//сбрасываем размер 
				for (int i = 0; i < menusettings.droncount; i++)
				{
					resetCart(dron[i]);
				}
				endchoice =0;
				itsfull = 0;
				endgame=0;
				selfdestruction=0;
				printHarvestScore(getHarvestsCount(harvest));
			}
			if(endchoice==2)
			{
				key_pressed = STOP_GAME;
			}
		}
		while ((double)(clock() - begin)/CLOCKS_PER_SEC<DELAY)
		{}
	}
	
	for (int i = 0; i < menusettings.droncount; i++)
	{	
		free((dron[i])->cart);
		free(dron[i]);
		free(menusettings.autopilot);
	}
	endwin(); // Завершаем режим curses mod
	
	return 0;
}

