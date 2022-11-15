circuit: libs/car.h libs/vroum.c libs/vroum.h circuit.c
	gcc circuit.c libs/vroum.c -o circuit

main: main.c libs/car.h libs/display.c libs/display.h libs/vroum.c libs/vroum.h libs/sort.c libs/sort.h
	gcc libs/display.c -c
	gcc libs/sort.c -c
	gcc libs/vroum.c -c
	gcc main.c display.o sort.o vroum.o -o main
clean:
	rm -f main
	rm -f display.o
	rm -f vroum.o
	rm -f sort.o
	rm -f circuit