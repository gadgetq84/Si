all: dron.exe

dron.exe: dron.o harvest.o dbody.o control.o menu.o
	gcc -o dron dron.o harvest.o dbody.o control.o menu.o -lncurses -DNCURSES_STATIC

dron.o: dron.c
	gcc -c --std=c99  -o dron.o dron.c  -lncurses -DNCURSES_STATIC

harvest.o: harvest.c
	gcc -c --std=c99  -o harvest.o  harvest.c  -lncurses -DNCURSES_STATIC

dbody.o: dbody.c
	gcc -c --std=c99  -o dbody.o  dbody.c  -lncurses -DNCURSES_STATIC
	
control.o: control.c
	gcc -c --std=c99  -o control.o  control.c  -lncurses -DNCURSES_STATIC

menu.o: menu.c
	gcc -c --std=c99  -o menu.o  menu.c  -lncurses -DNCURSES_STATIC
clean: 
	del *.o
	del dron.exe
