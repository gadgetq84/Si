#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <ncurses/ncurses.h>
#include "food.h"
#include "sbody.h"
#include "control.h"
#include "menu.h"
#define MIN_Y 2
#define PLAYERS 2

int main()
{
	WINDOW *my_win;
	int menuchoice=0;
	int endgame=0;
	int selfdestruction = 0;
	snake_t* snake[PLAYERS];
	
	struct foods* foodss = (struct foods*) malloc(sizeof(struct foods)*MAX_FOOD_SIZE);
	
	for (int i = 0; i < PLAYERS; i++)
	{
		initSnake(snake,START_TAIL_SIZE,40+i*10,10+i*10,i);
	}
	initFood(foodss,MAX_FOOD_SIZE);
	
	initscr();
	cbreak();
	
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	menuchoice = startMenu(snake,2);
	keypad(stdscr, TRUE); // Включаем F1, F2,стрелки и т.д.
	raw(); // Откдючаем line buffering
	noecho(); // Отключаем echo() режим при вызове getch
	curs_set(FALSE); //Отключаем курсор
	
	setColor(2);
	mvprintw(0, 1," Press'q' for end GAME");
	
	timeout(0); //Отключаем таймаут после нажатия клавиши в цикле
	int key_pressed=0;

	setColor(1);
	putFood(foodss,MAX_FOOD_SIZE);

	for (int i = 0; i < PLAYERS; i++)
	{
		printSnakeScore(snake[i],i,0,40+i*30);
		printLevel(snake[i],1,40+i*30);
	}
	
	refresh();
	double DELAY = 0.15;
	while( key_pressed != STOP_GAME && menuchoice!=3) 
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
		
		for (int i = 0; i < PLAYERS; i++)
		{
			
			update(snake[i],foodss,key_pressed,i,&DELAY);
							
			selfdestruction = the_snake_ate_itself(snake[i]);
		}
		
		//слопали всю еду пора показывать наш результат 
		if(getFoodsCount(foodss)== MAX_FOOD_SIZE || endgame==1 || selfdestruction==1)
		{
			my_win = printEndScoreBox(getFoodsCount(foodss));
			//если нажали f2  и запустили игру заново
			if(key_pressed == NEW_GAME)
			{
				DELAY =0.1;
				//расставляем еду
				putFood(foodss,MAX_FOOD_SIZE);
				//сбрасываем размер хвоста
				for (int i = 0; i < PLAYERS; i++)
				{
					resetTail(snake[i]);
				}
				//clrtoeol();
				wclear(my_win);
				wborder(my_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
				wrefresh(my_win);
				delwin(my_win);
				endgame=0;
				selfdestruction=0;
				
				
				// цветные красатульки
				for (int i = 0; i < PLAYERS; i++)
				{
					setColor(1);
					printSnakeScore(snake[i],i,0,40+i*30);
					setColor(1);
					printLevel(snake[i],1,40+i*30);
				}
			}
		}
		while ((double)(clock() - begin)/CLOCKS_PER_SEC<DELAY)
		{}
	}
	
	for (int i = 0; i < PLAYERS; i++)
	{	
		free(snake[i]->tail);
		free(snake[i]);
	}
	endwin(); // Завершаем режим curses mod
	
	return 0;
}

