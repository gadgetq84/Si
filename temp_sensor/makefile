all: sensor.exe

sensor.exe: main.o temp_functions.o color.o
	gcc -o sensor temp_functions.o main.o color.o
main.o: main.c
	gcc -c --std=c99  -o main.o main.c
temp_functions.o: temp_functions.c
	gcc -c --std=c99  -o temp_functions.o  temp_functions.c
color.o: color.c
	gcc -c --std=c99  -o color.o color.c

clean: 
	del *.o
	del sensor.exe
