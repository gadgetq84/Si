#include "menu.h"
#include <ncurses/ncurses.h>

void printDronScore(dron_t *head,int i, int x,int y)
{
	int score = head->tsize-1 -START_CART_SIZE;
	mvprintw(x, y,"the dron %d score %d  ",i,score);
}

void printHarvestScore(int count)
{
	mvprintw(0, 40,"a total of %d harvests have been collected ",count);
}

void printLevel(dron_t *head,int x,int y)
{
	int level = head->tsize-1 -START_CART_SIZE;
	mvprintw(x, y,"Lvl %d ",level);
}

int printEndScoreBox(int count)
{
	int height, width, start_y,start_x, max_y, max_x;
	int resultout = 0;
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
	touchwin(win);
	mvwprintw(win,1,2,"A %d harvests have been collected ",count);

	char *choices1[] = {
                        "Start harvesting",
                        "Exit",
                  };
	int choice=0;
	int curpos=0;
	while (1)
	{
		
		for(int i=0;i<2;i++)
		{
			if(i==curpos)
				wattron(win, A_REVERSE);
			mvwprintw(win, i+4, 10, choices1[i]);
            if(i==curpos)
				wattroff(win, A_REVERSE);
		
		}
		choice = wgetch(win);
		switch(choice)
		{
			case KEY_UP:
				curpos--;
				if(curpos==-1)
					curpos=1;
					
				break;
			case KEY_DOWN:
				curpos++;
				if(curpos==2)
					curpos=0;
				break;
			default:
				break;
		}
		if(choice ==10)
			break;
	}
	switch(curpos)
	{
		case 0:
			wclear(win);
			wborder(win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
			wrefresh(win);
			delwin(win);
			resultout = 1;
			break;
		case 1:
			wclear(win);
			wborder(win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
			wrefresh(win);
			delwin(win);
			resultout = 2;
			break;
	}
	return resultout;
}

void mainMenu(startsettings *menusettings)
{
	char *choices1[] = {
                        "Start harvesting",
                        "Drons count",
                        "Drons autopilot",
                        "Exit",
                  };
    
	int height, width, start_y,start_x, max_y, max_x;
	height = 12;
	width = 40;
	getmaxyx(stdscr, max_y, max_x);
	start_x = (max_x/2)-width/2;
	start_y = (max_y/2)-height/2;
	
	WINDOW * mainwin = newwin(height,width,start_y,start_x);
	char c = '*';
	char c1 = '*';
	box(mainwin,(int)c,(int)c1);
	refresh();
	raw(); // Откдючаем line buffering
	noecho(); // Отключаем echo() режим при вызове getch
	wrefresh(mainwin);
	keypad(mainwin, TRUE);
	mvwprintw(mainwin, 1, 8, "DRON MENU");
	
	int choice=0;
	int curpos=0;
	
	while (1)
	{
		
		for(int i=0;i<4;i++)
		{
			if(i==curpos)
				wattron(mainwin, A_REVERSE);
			mvwprintw(mainwin, i+3, 10, choices1[i]);
            if(i==curpos)
				wattroff(mainwin, A_REVERSE);
		
		}
		choice = wgetch(mainwin);
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
	switch(curpos)
	{
		case 3:
			wclear(mainwin);
			wborder(mainwin, ' ', ' ', ' ',' ',' ',' ',' ',' ');
			wrefresh(mainwin);
			delwin(mainwin);
			menusettings->menuchoice = 333;
			break;
		case 0:
			wclear(mainwin);
			wborder(mainwin, ' ', ' ', ' ',' ',' ',' ',' ',' ');
			wrefresh(mainwin);
			delwin(mainwin);
			menusettings->menuchoice = 0;
			break;
		case 1:
			dron_countsubmenu(mainwin,menusettings);
				mainMenu(menusettings);
			break;
		case 2:
			dron_autopilotsubmenu(mainwin,menusettings,0);
				mainMenu(menusettings);
			break;
	}

}

void dron_countsubmenu(WINDOW * win,startsettings *menusettings)
{	
	char c = '*';
	char c1 = '*';
	int choice=0;
	int curpos=0;
	int dron_count = menusettings->droncount;
	int flag=1;
	
	char *dron_menu[] = {
                        "1",
                        "2",
                        "3",
                        "4",
                        "5",
                        "Exit"
                  };
		wclear(win);
		mvwprintw(win, 2, 8, "DRON COUNT %d",(menusettings->droncount));
		box(win,(int)c,(int)c1);

		while (flag)
		{
		for(int i=0;i<6;i++)
		{
			if(i==curpos)
				wattron(win, A_REVERSE);
			mvwprintw(win, i+4, 10, dron_menu[i]);
			if(i==curpos)
				wattroff(win, A_REVERSE);
		}
		choice = wgetch(win);
		switch(choice)
		{
			case KEY_UP:
				curpos--;
				if(curpos==-1)
					curpos=5;
				break;
			case KEY_DOWN:
				curpos++;
				if(curpos==6)
				curpos=0;
				break;
			default:
				break;
		}
		if(choice ==10)
			break;
		}
		
		switch(curpos)
		{
			case 0:
				dron_count = curpos+1;
				break;
			case 1:
				dron_count = curpos+1;
				break;
			case 2:
				dron_count = curpos+1;
				break;
			case 3:
				dron_count = curpos+1;
				break;
			case 4:
				dron_count = curpos+1;
				break;
			case 5:
				dron_count = menusettings->droncount;
				break;
		}
		menusettings->droncount=dron_count;
		menusettings->autopilot = (int*) calloc(menusettings->droncount, sizeof(int));
	//возвращаемся в главное меню
	
}



void dron_autopilotsubmenu(WINDOW * win,startsettings *menusettings,int index)
{	
	char c = '*';
	char c1 = '*';
	int choice=0;
	int curpos=index;
	int flag=1;

	wclear(win);
	box(win,(int)c,(int)c1);
	mvwprintw(win, 1, 8, "SNAKE CONTROL MENU");

    char *snake_menu[] = {
                       "1",
                       "2",
                       "3",
                       "4",
                       "5"
                  };
	while (flag)
	{
		for(int i=0;i<menusettings->droncount;i++)
		{
			if(i==curpos)
				wattron(win, A_REVERSE);
			mvwprintw(win, i+3, 10, snake_menu[i]);
			if(i==curpos)
				wattroff(win, A_REVERSE);
		}
		if(menusettings->droncount==curpos)
			wattron(win, A_REVERSE);
		mvwprintw(win, menusettings->droncount+3, 10, "Exit");
		if(menusettings->droncount==curpos)
			wattroff(win, A_REVERSE);
		
		choice = wgetch(win);
		switch(choice)
		{
			case KEY_UP:
				curpos--;
				if(curpos==-1)
					curpos=menusettings->droncount;
				break;
			case KEY_DOWN:
				curpos++;
				if(curpos==menusettings->droncount+1)
				curpos=0;
				break;
			default:
				break;
		}
		//mvwprintw(win,2, 10, "%d  %d",menusettings->autopilot[curpos],curpos);
		if(choice ==10)
			break;
		}
		
		if(curpos<menusettings->droncount)
		{
			dron_selectsubmenu(win,menusettings,curpos);
		    //возвращаемся в главное меню
		    dron_autopilotsubmenu(win,menusettings,curpos);
		}

}

void dron_selectsubmenu(WINDOW * win,startsettings *menusettings,int index)
{	
	char c = '*';
	char c1 = '*';
	int choice=0;
	int curpos=0;
	int flag=1;

	wclear(win);
	box(win,(int)c,(int)c1);
	curpos=0;
	mvwprintw(win, 1, 8, "SNAKE CONTROL MENU number #%d",index+1);
    char *snake_menu[] = {
                       "manual",
                       "auto"
                  };
	while (flag)
	{
		for(int i=0;i<2;i++)
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
					curpos=1;
				break;
			case KEY_DOWN:
				curpos++;
				if(curpos==2)
				curpos=0;
				break;
			default:
				break;
		}
		if(choice ==10)
			break;
		}
	if(curpos==0)
		menusettings->autopilot[index]=0;
	if(curpos==1)
		menusettings->autopilot[index]=1;
	
}
