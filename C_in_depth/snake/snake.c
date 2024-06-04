#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <ncurses/ncurses.h>
#define MIN_Y 2

enum {LEFT, UP, RIGHT, DOWN, STOP_GAME=KEY_F(10),NEW_GAME=KEY_F(2) ,END_GAME='q'};
enum {CONTROLS=3,MAX_TAIL_SIZE=100, START_TAIL_SIZE=3, MAX_FOOD_SIZE=2,FOOD_EXPIRE_SECONDS=10};
//структура еды struct food
struct food
{
	int x;
	int y;
	time_t put_time;
	char point;
	uint8_t enable;
} food[MAX_FOOD_SIZE];


// Здесь храним коды управления змейкой
struct control_buttons
{
int down;
int up;
int left;
int right;
}control_buttons;

struct control_buttons default_controls[] = {{KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT},{'S','W','A','D'},{'s','w','a','d'}};
/*
Голова змейки содержит в себе
x,y - координаты текущей позиции
direction - направление движения
tsize - размер хвоста
*tail - ссылка на хвост
*/
typedef struct snake_t
{
	int x;
	int y;
	int direction;
	size_t tsize;
	struct tail_t *tail;
	struct control_buttons *controls;
} snake_t;

/*
Хвост это массив состоящий из координат
x,y
*/
typedef struct tail_t
{
	int x;
	int y;
} tail_t;

void initFood(struct food f[], size_t size)
{
	struct food init = {0,0,0,0,0};
	int max_y=0, max_x=0;
	getmaxyx(stdscr, max_y, max_x);
	for(size_t i=0; i<size; i++)
	{
		f[i] = init;
	}
}

void initTail(struct tail_t t[], size_t size)
{
	struct tail_t init_t={0,0};
	for(size_t i=0; i<size; i++)
	{
		t[i]=init_t;
	}
}

void initHead(struct snake_t *head, int x, int y)
{
	head->x = x;
	head->y = y;
	head->direction = RIGHT;
}

void initSnake(snake_t *head, size_t size, int x, int y)
{
	tail_t* tail = (tail_t*)malloc(MAX_TAIL_SIZE*sizeof(tail_t));
	initTail(tail, MAX_TAIL_SIZE);
	initHead(head, x, y);
	head->tail = tail; // прикрепляем к	голове хвост
	head->tsize = size+1;
	head->controls =  default_controls;
}

/*
Обновить/разместить текущее зерно на поле
*/
void putFoodSeed(struct food *fp)
{
	int max_x=0, max_y=0;
	char spoint[2] = {0};
	getmaxyx(stdscr, max_y, max_x);
	mvprintw(fp->y, fp->x, " ");
	fp->x = rand() % (max_x - 1);
	fp->y = rand() % (max_y - 2) + 1; //Не занимаем верхнюю строку
	fp->put_time = time(NULL);
	fp->point = '$';
	fp->enable = 1;
	spoint[0] = fp->point;
	mvprintw(fp->y, fp->x, "%s", spoint);
}

/*
Разместить еду на поле
*/
void putFood(struct food f[], size_t number_seeds)
{
	for(size_t i=0; i<number_seeds; i++)
	{
		putFoodSeed(&f[i]);
	}
}

void refreshFood(struct food f[], int nfood)
{
	int max_x=0, max_y=0;
	char spoint[2] = {0};
	getmaxyx(stdscr, max_y, max_x);
	for(size_t i=0; i<nfood; i++)
	{
		if( f[i].put_time )
		{
			if( f[i].enable && (time(NULL) - f[i].put_time) > FOOD_EXPIRE_SECONDS )
			{
				putFoodSeed(&f[i]);
			}
		}
	}
}

_Bool haveEat(struct snake_t *head, struct food f[])
{
	for(size_t i=0; i<MAX_FOOD_SIZE; i++)
	if( f[i].enable && head->x == f[i].x && head->y == f[i].y )
	{
		f[i].enable = 0;
		return 1;
	}
	return 0;
}

int getFoodsCount(struct food f[])
{
	int count=0;
	for(size_t i=0; i<MAX_FOOD_SIZE; i++)
	if( !f[i].enable)
	{
		count ++;
	}
	return count;
}

void printSnakeScore(int count)
{
	mvprintw(0, 60,"the snake scored %d points out of %d possible ",count,MAX_FOOD_SIZE);
}
/*
Увеличение хвоста на 1 элемент
*/
void addTail(struct snake_t *head)
{
	if(head == NULL || head->tsize>MAX_TAIL_SIZE)
	{
		mvprintw(0, 0, "Can't add tail");
		return;
	}
	head->tsize++;
}
/*
сброс длины хвоста хвоста
*/
void resetTail(struct snake_t *head)
{
	if(head == NULL)
	{
		mvprintw(0, 0, "Can't reset tail");
		return;
	}else
	{
		for(size_t i=START_TAIL_SIZE; i<head->tsize; i++)
		{
			mvprintw(head->tail[i].y, head->tail[i].x, " ");
		}
		head->tsize=START_TAIL_SIZE+1;
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
			if(head->y <= 2)
				// Циклическое движение, чтобы не уходить за пределы экрана
				head->y = max_y;		
			mvprintw(--(head->y), head->x, "%c", ch);
		break;
		case DOWN:
			if(head->y >=max_y )
				head->y = 0;
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

//  при достижении конца показывается менюшка 
void printExit(snake_t *head)
{
	//вместо printExit(snake_t *head) 
	// WINDOW * printEndScoreBox(int count)
}

//не совсем понятно как связать уровень с структурой змеи если только по длине хвоста
// ... проще и логичнее отслеживать слопанные символы и поднимать уровень с каждым
void printLevel(snake_t *head)
{
	int level = head->tsize-1 -START_TAIL_SIZE;
	mvprintw(1, 60,"Lvl %d ",level);
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

WINDOW * printEndScoreBox(int count)
{
	int height, width, start_y,start_x, max_y, max_x;
	height = 10;
	width = 40;
	getmaxyx(stdscr, max_y, max_x);
	start_x = (max_x/2)-width/2;
	start_y = (max_y/2)-height/2;
	WINDOW * win = newwin(height,width,start_y,start_x);
	
	char c = '*';
	char c1 = '*';
	box(win,(int)c,(int)c1);
	mvwprintw(win,1,2,"The snake scored %d points",count);
	mvwprintw(win,2,2,"Press'F2' for new START");
	mvwprintw(win,3,2,"Press'F10' for EXIT");
	touchwin(win);
	wrefresh(win);
	return win;
}


int main()
{
	WINDOW *my_win;
	int endgame=0;
	snake_t* snake = (snake_t*)malloc(sizeof(snake_t));
	struct food* foods = (struct food*) malloc(sizeof(struct food)*MAX_FOOD_SIZE);
	initSnake(snake,START_TAIL_SIZE,10,10);
	initFood(foods,MAX_FOOD_SIZE);
	initscr();
	start_color();
	cbreak();
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_BLACK);
	keypad(stdscr, TRUE); // Включаем F1, F2,стрелки и т.д.
	raw(); // Откдючаем line buffering
	noecho(); // Отключаем echo() режим при вызове getch
	curs_set(FALSE); //Отключаем курсор
	attron(COLOR_PAIR(2));
	mvprintw(0, 1,"Use arrows for control. Press'q' for end GAME");
	attron(COLOR_PAIR(3));
	timeout(0); //Отключаем таймаут после нажатия клавиши в цикле
	int key_pressed=0;
	
	putFood(foods,MAX_FOOD_SIZE);

	attron(COLOR_PAIR(1));
	printSnakeScore(getFoodsCount(foods));
	printLevel(snake);
	attron(COLOR_PAIR(3));
	refresh();
	double DELAY = 0.1;
	while( key_pressed != STOP_GAME) 
	{
		
		clock_t begin = clock();
		key_pressed = getch(); // Считываем клавишу
		go(snake);
		goTail(snake);
		if(key_pressed == 'p' || key_pressed == 'P')
		{
			 pause();
		}
		
		if(key_pressed == END_GAME)
		{
			endgame=1;
		}
		//timeout(50); // Задержка при отрисовке
		changeDirection(snake, key_pressed);
		refreshFood(foods, MAX_FOOD_SIZE);// Обновляем еду
		if (haveEat(snake,foods)) 
		{
			// цветные красатульки
			attron(COLOR_PAIR(1));
			// вывод текущего счета 
			printSnakeScore(getFoodsCount(foods));
			attron(COLOR_PAIR(3));
			// увеличение хвоста 
			addTail(snake);
			attron(COLOR_PAIR(1));
			//обновляем уровень 
			printLevel(snake);
			// увеличиваем скорость 
			DELAY = DELAY - 0.03;
			attron(COLOR_PAIR(3));
		}
		//слопали всю еду пора показывать наш результат 
		if(getFoodsCount(foods)== MAX_FOOD_SIZE || endgame==1)
		{
			
			my_win = printEndScoreBox(getFoodsCount(foods));
			
			//если нажали f2  и запустили игру заново
			if(key_pressed == NEW_GAME)
			{
				DELAY =0.1;
				//расставляем еду
				putFood(foods,MAX_FOOD_SIZE);
				//сбрасываем размер хвоста
				resetTail(snake);
				//clrtoeol();
				wclear(my_win);
				wborder(my_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
				wrefresh(my_win);
				delwin(my_win);
				endgame=0;
				// цветные красатульки
				attron(COLOR_PAIR(1));
				printSnakeScore(getFoodsCount(foods));
				printLevel(snake);
				// цветные красатульки
				attron(COLOR_PAIR(3));
			}
		}
		
		while ((double)(clock() - begin)/CLOCKS_PER_SEC<DELAY)
		{}
	}	
	free(snake->tail);
	free(snake);
	endwin(); // Завершаем режим curses mod
	
	return 0;
}

