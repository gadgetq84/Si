all: snake.exe

snake.exe: snake.o food.o sbody.o control.o menu.o
	gcc -o snake snake.o food.o sbody.o control.o menu.o -lncurses -DNCURSES_STATIC

snake.o: snake.c
	gcc -c --std=c99  -o snake.o snake.c  -lncurses -DNCURSES_STATIC

food.o: food.c
	gcc -c --std=c99  -o food.o  food.c  -lncurses -DNCURSES_STATIC

sbody.o: sbody.c
	gcc -c --std=c99  -o sbody.o  sbody.c  -lncurses -DNCURSES_STATIC
	
control.o: control.c
	gcc -c --std=c99  -o control.o  control.c  -lncurses -DNCURSES_STATIC

menu.o: menu.c
	gcc -c --std=c99  -o menu.o  menu.c  -lncurses -DNCURSES_STATIC
clean: 
	del *.o
	del snake.exe
