all: main.c libs/car.h libs/display.c libs/vroum.c libs/sort.c
	gcc libs/display.c -c
	gcc libs/sort.c -c
	gcc libs/vroum.c -c
	gcc main.c -lncurses display.o sort.o vroum.o -o main
clean:
	rm -f main
	rm -f display.o
	rm -f vroum.o
	rm -f sort.o
	rm -f circuit