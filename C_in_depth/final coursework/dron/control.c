#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <ncurses/ncurses.h>
#include "control.h"
#include "menu.h"
#include "harvest.h"

int distanceHarvest(const dron_t dron, const harvests harvest) { // вычисляет количество ходов до еды
	return (abs(dron.x - harvest.x) + abs(dron.y - harvest.y));
}

void autoChangeDirection(dron_t *dron, harvests harvest[], int harvestSize,int index)
{
	int pointer = 0;
	int temppoint = 0;
	//если дрон выбрал цель то помечаем ее чтобы все остальные на нее не смотрели.... 
	for (int i = 0; i < harvestSize; i++)
		if(harvest[i].enable==1 && harvest[i].st ==0)
		{
			pointer=i;
			harvest[i].st = dron->id;
			break;
		}else
		{
			if(harvest[i].enable==1 && harvest[i].st ==dron->id)
				pointer=i;
		}

	//for (int i = 0; i < harvestSize; i++) { // ищем видимую еду		

		//if(harvest[i].enable==1)
		//{
			//temppoint = distanceHarvest(*dron, harvest[i]);
			//pointer = (temppoint <  distanceHarvest(*dron, harvest[pointer])) ? i : pointer;
		//}
	
	//}
	
	//mvprintw(2+index, 1,"%d %d %d",dron->id ,pointer, distanceHarvest(*dron, harvest[pointer]));
	if ((dron->direction == RIGHT || dron->direction == LEFT) && (dron->y != harvest[pointer].y)) { // горизонтальное движение
		dron->direction = (harvest[pointer].y > dron->y) ? DOWN : UP;
	} else if ((dron->direction == DOWN || dron->direction == UP) && (dron->x != harvest[pointer].x)) { // вертикальное движение
		dron->direction = (harvest[pointer].x > dron->x) ? RIGHT : LEFT;
	}
}

/*
Движение головы с учетом текущего направления движения
*/
void go(dron_t *head)
{
	char ch = 'X';
	int max_x=0, max_y=0;
	getmaxyx(stdscr, max_y, max_x); // macro - размер терминала
	mvprintw(head->y, head->x, " "); // очищаем один символ
	switch (head->direction)
	{
		case LEFT:
			if(head->x <= 0)
				// Циклическое движение, чтобы не уходить за пределы экрана
				head->x = max_x;
			mvprintw(head->y, --(head->x), "%c", ch);
		break;
		case RIGHT:
			if(head->x >=max_x )
				head->x = 0;
			mvprintw(head->y, ++(head->x), "%c", ch);
		break;
		case UP:
			if(head->y <=2)
				// Циклическое движение, чтобы не уходить за пределы экрана
				head->y = max_y;		
			mvprintw(--(head->y), head->x, "%c", ch);
		break;
		case DOWN:
			if(head->y >=max_y )
				head->y = 2;
		mvprintw(++(head->y), head->x, "%c", ch);
		break;
		default:
		break;
	}
refresh();
}

/*
Движение хвоста с учетом движения головы
*/
void goCart(dron_t *head)
{
	char ch = 'O';
	mvprintw(head->cart[head->tsize-1].y, head->cart[head->tsize-1].x, " ");
	for(size_t i = head->tsize-1; i>0; i--)
	{
		head->cart[i] = head->cart[i-1];
		if( i==1 )
		  mvprintw(head->cart[i].y, head->cart[i].x, "%c", ch);
	}
	head->cart[0].x = head->x;
	head->cart[0].y = head->y;
}

int checkDirection(dron_t* dron, int32_t key)
{
	for (int i=0;i<CONTROLS;i++)
	{
	if (dron->direction == DOWN && key ==dron->controls[i].up)
		return 0;
	else if (dron->direction == UP && key ==dron->controls[i].down)
		return 0;
	else if (dron->direction == LEFT && key ==dron->controls[i].right)
		return 0;
	else if (dron->direction == RIGHT && key ==dron->controls[i].left)
		return 0;
	}
	return 1;
}

int isCrush(dron_t *head)
{
	int ret = 0;
	
	for(size_t i = head->tsize-1; i>0; i--)
	{
      if(head->x == (head->cart[i].x) && head->y == (head->cart[i].y))
       ret = 1;
	}
	return ret;
}

//Для изменения направления движения используется функция:
void changeDirection(dron_t* dron, const int32_t key)
{
	for (int i=0;i<CONTROLS;i++)
	{
		if(checkDirection(dron,key))
		{
			if (key == dron->controls[i].down)
				dron->direction = DOWN;
			else if (key == dron->controls[i].up)
				dron->direction = UP;
			else if (key == dron->controls[i].right)
				dron->direction = RIGHT;
			else if (key == dron->controls[i].left)
				dron->direction = LEFT;
		}
	}
}

// придумал такую функцию  постановки на паузу 
// холостой цикл
void pause()
{
	int flag = 1;
	int key_pressed=0; 
	//ПЕЧАТАЕМ АТЕШН
	mvprintw(7, 50,"Press'p' for continuation");
	while (flag)
	{
		key_pressed = getch(); // Считываем клавишу
		if(key_pressed == 'p' || key_pressed == 'P')
		{
			flag=0;
		}
	}
	//ЗАТИРАЕМ АТЕНШН ДРУГОГо способа не придумал
	mvprintw(7, 50,"                                ");
}

_Bool collectionOfUnits(dron_t *head, harvests f[])
{
	for(size_t i=0; i<MAX_HARVEST_SIZE; i++)
	if( f[i].enable && head->x == f[i].x && head->y == f[i].y )
	{
		f[i].enable = 0;
		return 1;
	}
	return 0;
}


void setColor(int objectType)
{
	attroff(COLOR_PAIR(1));
	attroff(COLOR_PAIR(2));
	attroff(COLOR_PAIR(3));
	attroff(COLOR_PAIR(4));
	switch(objectType)
	{
		case 2: //snake manual control
			attron(COLOR_PAIR(2));
			break;
		case 4: //snake  autopilot
			attron(COLOR_PAIR(4));
			break;
		case 1: //harvest
			attron(COLOR_PAIR(1));
			break;
		case 3: //default
			attron(COLOR_PAIR(3));
			break;
	}
}

void update(dron_t *dron, harvests hrvsts[], int key_pressed, int i)
{
	if (dron->autopilot == 1)
		autoChangeDirection(dron,hrvsts,MAX_HARVEST_SIZE,i);
	
	setColor(dron->color);
	go(dron);
	goCart(dron);
	setColor(1);
	refreshHarvest(hrvsts, MAX_HARVEST_SIZE);// Обновляем еду
	changeDirection(dron, key_pressed);
	
	if (collectionOfUnits(dron,hrvsts)) 
	{
		// увеличение хвоста 
		addCart(dron);
		// цветные красатульки
		
		// цветные красатульки
		setColor(1);
		printHarvestScore(getHarvestsCount(hrvsts));
	}	
	
}
