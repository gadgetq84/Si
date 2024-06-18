#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <ncurses/ncurses.h>
#include "control.h"
#include "menu.h"


int distance(const snake_t snake, const struct foods food) { // вычисляет количество ходов до еды
	return (abs(snake.x - food.x) + abs(snake.y - food.y));
}
void autoChangeDirection(snake_t *snake, struct foods food[], int foodSize,int index)
{
	int pointer = 0;
	int temppoint = 0;
	for (int i = 0; i < foodSize; i++) { // ищем ближайшую еду
		if(food[i].enable==1)
		{
			temppoint = distance(*snake, food[i]);
			pointer = (temppoint < distance(*snake, food[pointer])) ? i : pointer;
		}
	
	}
	mvprintw(2+index, 1,"%d %d",temppoint,distance(*snake, food[pointer]));
	if ((snake->direction == RIGHT || snake->direction == LEFT) && (snake->y != food[pointer].y)) { // горизонтальное движение
		snake->direction = (food[pointer].y > snake->y) ? DOWN : UP;
	} else if ((snake->direction == DOWN || snake->direction == UP) && (snake->x != food[pointer].x)) { // вертикальное движение
		snake->direction = (food[pointer].x > snake->x) ? RIGHT : LEFT;
	}
}

/*
Движение головы с учетом текущего направления движения
*/
void go(struct snake_t *head)
{
	char ch = '@';
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
void goTail(struct snake_t *head)
{
	char ch = '*';
	mvprintw(head->tail[head->tsize-1].y, head->tail[head->tsize-1].x, " ");
	for(size_t i = head->tsize-1; i>0; i--)
	{
		head->tail[i] = head->tail[i-1];
		if( i==1 )
		mvprintw(head->tail[i].y, head->tail[i].x, "%c", ch);
	}
	head->tail[0].x = head->x;
	head->tail[0].y = head->y;
}

int checkDirection(snake_t* snake, int32_t key)
{
	for (int i=0;i<CONTROLS;i++)
	{
	if (snake->direction == DOWN && key ==snake->controls[i].up)
		return 0;
	else if (snake->direction == UP && key ==snake->controls[i].down)
		return 0;
	else if (snake->direction == LEFT && key ==snake->controls[i].right)
		return 0;
	else if (snake->direction == RIGHT && key ==snake->controls[i].left)
		return 0;
	}
	return 1;
}

int the_snake_ate_itself(snake_t *head)
{
	int ret = 0;
	
	for(size_t i = head->tsize-1; i>0; i--)
	{
      if(head->x == (head->tail[i].x) && head->y == (head->tail[i].y))
       ret = 1;
	}
	return ret;
}

//Для изменения направления движения используется функция:
void changeDirection(snake_t* snake, const int32_t key)
{
	for (int i=0;i<CONTROLS;i++)
	{
		if(checkDirection(snake,key))
		{
			if (key == snake->controls[i].down)
				snake->direction = DOWN;
			else if (key == snake->controls[i].up)
				snake->direction = UP;
			else if (key == snake->controls[i].right)
				snake->direction = RIGHT;
			else if (key == snake->controls[i].left)
				snake->direction = LEFT;
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

_Bool haveEat(struct snake_t *head, struct foods f[])
{
	for(size_t i=0; i<MAX_FOOD_SIZE; i++)
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
		case 2: //snake 1
			attron(COLOR_PAIR(2));
			break;
		case 4: //snake 2
			attron(COLOR_PAIR(4));
			break;
		case 1: //food
			attron(COLOR_PAIR(1));
			break;
		case 3: //default
			attron(COLOR_PAIR(3));
			break;
	}
}

void update(snake_t *snake, struct foods foodss[], int key_pressed, int i, double *delay )
{
	if (snake->autopilot == 1)
		autoChangeDirection(snake,foodss,MAX_FOOD_SIZE,i);
	
	setColor(snake->color);
	go(snake);
	goTail(snake);
	setColor(1);
	refreshFood(foodss, MAX_FOOD_SIZE);// Обновляем еду
	changeDirection(snake, key_pressed);
	
	if (haveEat(snake,foodss)) 
	{
		// увеличение хвоста 
		addTail(snake);
		// цветные красатульки
		
		setColor(1);
		// вывод текущего счета 
		printSnakeScore(snake,i,0,40+i*30);
		
		setColor(1);
		//обновляем уровень 
		printLevel(snake,1,40+i*30);
		// увеличиваем скорость 
		
		*delay = *delay - 0.002;
	}	
	
}
