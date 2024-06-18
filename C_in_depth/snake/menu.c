#include "menu.h"

void printSnakeScore(snake_t *head,int i, int x,int y)
{
	int score = head->tsize-1 -START_TAIL_SIZE;
	mvprintw(x, y,"the snake %d score %d  ",i,score);
}

//  при достижении конца показывается менюшка 
void printExit(snake_t *head)
{
	//вместо printExit(snake_t *head) 
	// WINDOW * printEndScoreBox(int count)
}

//не совсем понятно как связать уровень с структурой змеи если только по длине хвоста
// ... проще и логичнее отслеживать слопанные символы и поднимать уровень с каждым
void printLevel(snake_t *head,int x,int y)
{
	int level = head->tsize-1 -START_TAIL_SIZE;
	mvprintw(x, y,"Lvl %d ",level);
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
	mvwprintw(win,1,2,"The snakes scored %d points",count);
	mvwprintw(win,2,2,"Press'F2' for new START");
	mvwprintw(win,3,2,"Press'F10' for EXIT");
	touchwin(win);
	wrefresh(win);
	return win;
}

int startMenu(snake_t *head[],int count)
{
	char *choices1[] = {
                        "New game",
                        "Snake1 color",
                        "Snake2 color",
                        "Exit",
                  };
                 
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
	refresh();
	
	raw(); // Откдючаем line buffering
	noecho(); // Отключаем echo() режим при вызове getch
	wrefresh(win);
	keypad(win, TRUE);
	mvwprintw(win, 1, 8, "SNAKE GAME MENU");
	int choice=0;
	int curpos=0;
	int flag=1;
	while (flag)
	{
		for(int i=0;i<4;i++)
		{
			if(i==curpos)
				wattron(win, A_REVERSE);
			mvwprintw(win, i+3, 10, choices1[i]);
            if(i==curpos)
				wattroff(win, A_REVERSE);
		}
		choice = wgetch(win);
		switch(choice)
		{
			case KEY_UP:
				curpos--;
				if(curpos==-1)
					curpos=3;
				break;
			case KEY_DOWN:
				curpos++;
				if(curpos==4)
					curpos=0;
				break;
			default:
				break;
		}
		if(choice ==10)
			break;

	}
	if(curpos ==3 || curpos ==0)
	{
		wclear(win);
		wborder(win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
		wrefresh(win);
		delwin(win);
	}
	//если жмакаем выбр цвета проваливаемся в субменю 
	if(curpos ==1 || curpos ==2)
	{
		snake_submenu(win,head,curpos,curpos);
	}
return curpos;
}

void snake_submenu(WINDOW * win,snake_t *head[],int count,int index)
{	
	char c = '*';
	char c1 = '*';
	int choice=0;
	int curpos=0;
	int flag=1;
	mvwprintw(win, 1, 8, "SNAKE COLOR MENU");
	char *snake_menu[] = {
                        "Color red",
                        "Color blue",
                        "Exit",
                  };
		wclear(win);
		box(win,(int)c,(int)c1);
		curpos=0;
		while (flag)
		{
		for(int i=0;i<3;i++)
		{
			if(i==curpos)
				wattron(win, A_REVERSE);
			mvwprintw(win, i+3, 10, snake_menu[i]);
			if(i==curpos)
				wattroff(win, A_REVERSE);
		}
		choice = wgetch(win);
		switch(choice)
		{
			case KEY_UP:
				curpos--;
				if(curpos==-1)
					curpos=2;
				break;
			case KEY_DOWN:
				curpos++;
				if(curpos==3)
				curpos=0;
				break;
			default:
				break;
		}
		if(choice ==10)
			break;
		}
	if(curpos==0)
		head[index-1]->color=2;
	if(curpos==1)
		head[index-1]->color=4;
	//возвращаемся в главное меню
	startMenu(head,count);
	
}
